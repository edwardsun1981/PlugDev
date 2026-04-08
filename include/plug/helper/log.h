///////////////////////////////////////////////////////////////
// Plug.h
// 建立时间: 2019.8.29
// 作者: 孙华庆		SunHuaQing
// 版本:
///////////////////////////////////////////////////////////////
#pragma once
#include "app.h"

#include <sstream>
#include <assert.h>

#include "is_utf8.h"
class LogStream : public std::ostringstream
{
public:
    LogStream(const char* file, int line, int severity)
    {
        m_file = file;
        m_line = line;
        m_severity = severity;
    }
    ~LogStream()
    {
        if (m_severity < 0)
            return;
        std::string str = this->str();
        auto logOut = Plug::GetApp()->logOut;
        assert(logOut);//如果要使用 LOG， 这个必须实现才能拿到日志
        if (logOut)
        {			
			if(is_utf8((unsigned char*)str.c_str(), (int)str.length()))
				logOut(m_file, m_line, m_severity, str.c_str());
			else
				logOut(m_file, m_line, m_severity, Plug::gbk2u8(str).c_str());
        }
            
    }
private:
    const char* m_file = nullptr;
    int m_line = 0;
    int m_severity = 0;
};

const int INFO = 0, WARNING = 1, ERROR2 = 2, FATAL = 3, OPTION = 4,  NUM_SEVERITIES = 5, I2 = 6;

#define LOG(severity) LogStream(__FILE__, __LINE__, severity)
#define _LOG LOG(INFO)

#ifdef _DEBUG
#define DLOG(severity) LOG(severity)
#else
#define DLOG(severity) LOG(-1)
#endif // _DEBUG

//---------只打印前N次的log
#define LOG_EVERY_N_VARNAME_CONCAT2(base, line) base ## line
#define LOG_EVERY_N_VARNAME2(base, line) LOG_EVERY_N_VARNAME_CONCAT2(base, line)
#define LOG_OCCURRENCES LOG_EVERY_N_VARNAME2(occurrences_, __LINE__)

#define DLOG_FIRST_N(severity, n) \
  static int LOG_OCCURRENCES = 0; \
  if (LOG_OCCURRENCES <= n) \
    ++LOG_OCCURRENCES; \
  if (LOG_OCCURRENCES <= n) \
    DLOG(severity)

#define LOG_FIRST_N(severity, n) \
  static int LOG_OCCURRENCES = 0; \
  if (LOG_OCCURRENCES <= n) \
    ++LOG_OCCURRENCES; \
  if (LOG_OCCURRENCES <= n) \
    LOG(severity)

// 每第N次打一回LOG
#define LOG_EVERY_N(severity, n) \
  static int LOG_OCCURRENCES = -1; \
  LOG_OCCURRENCES++;  \
  if ((LOG_OCCURRENCES % n) == 0) \
      LOG(severity)

#define LOG_IF(severity, condition) \
  if (condition) LOG(severity)
//---------只打印前N次的log ------end

//---------- 打印函数执行用时----------
class ExecTimeTest
{
public:
    ExecTimeTest(const char* fn)
    {
        tm = Plug::high_resolution_clock();
        fnName = fn;
        lv = 0;
    }

    ExecTimeTest(const char* fn, long long _lv)
    {
        tm = Plug::high_resolution_clock();
        fnName = fn;
        lv = _lv;
    }

    ~ExecTimeTest()
    {
        auto cost = Plug::high_resolution_clock() - tm;
        if (cost >= lv) LOG(INFO) << " function: " << fnName << "  exec time: " << cost << "ms";
    }
private:
    long long tm = 0;
    long long lv = 0;
    std::string fnName;
};

#define exectime(fn) ExecTimeTest __test_exec_time(fn)
#define exectime_gt(fn, lv) ExecTimeTest __test_exec_time_2(fn, lv)

//---------- 打印函数执行用时---------- end