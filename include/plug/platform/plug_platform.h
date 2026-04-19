///////////////////////////////////////////////////////////////
// 建立时间: 2005.12.27
// 此文件定义一些平台相关的东西
///////////////////////////////////////////////////////////////
#ifndef	_PLUG_PLATFORM_H_
#define	_PLUG_PLATFORM_H_

#if defined _WINDOWS_ || defined(WINDOWS) || defined(_WINDOWS) || defined(_CONSOLE)
#include "windows_plug_platform.h"
#else
#ifdef UE_GAME
#include "unreal_plug_platform.h"
#else
#include "linux_plug_platform.h" //linux, 安卓, macOS, IOS, unix , Emscripten一律走这个
#endif
#endif // compilers

#include <thread>
#include <sstream>

namespace Plug
{
	inline void sleep(int time)// time ms
	{
//		timeBeginPeriod(1); //提高sleep 的精确度。如果没有这个会有很小概率在少数系统上出现类似误差问题
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
//		timeEndPeriod(1);
	}
	inline __int64 high_resolution_clock()
	{
		auto tm = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());//steady_clock开机时间, system_clock 加日期时间
		return tm.time_since_epoch().count();
	}
	inline __int64 get_tick_count()
	{
		return high_resolution_clock();
	}
	inline std::string get_cur_thread_id()
	{
		std::ostringstream oss;
		oss << std::this_thread::get_id();
		return oss.str();
	}
	inline std::string GetCurrentPath()
	{
		return Plug::xGetCurrentPath();
	}
}

#endif //_PLUG_PLATFORM_H_
