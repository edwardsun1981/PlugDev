///////////////////////////////////////////////////////////////
// Plug.h
// 建立时间: 2011.4.29
// 作者: 孙华庆		SunHuaQing
// 版本:
///////////////////////////////////////////////////////////////
#pragma once
#ifndef	_PLUG_APP_H_
#define	_PLUG_APP_H_

#include "../platform/plug_platform.h"
#if _HAS_CXX17
#include <any>
#endif
#include <functional>

typedef std::function<void()>                   Func0;
typedef std::function<void(const char* arg)>    Func1;
namespace Plug
{
	struct I_App
	{
		std::function<void(Func0)> addFunc2WorkThr; //增加一个事件在工作线程执行
		std::function<void(const char* file, int line, int severity, const char* str)> logOut;//全局输出日志

        virtual void __stdcall delVal(const char* _name) = 0;
        virtual void __stdcall setVal(const char* name, const char* val) = 0;
        virtual const char* __stdcall getVal(const char* name) = 0;
        virtual void __stdcall setValPointer(const char* name, void* p) = 0;
        virtual void* __stdcall getValPointer(const char* name) = 0;
#if _HAS_CXX17
		virtual void __stdcall setValAny(const char* name, std::any a) = 0;
		virtual std::any __stdcall getValAny(const char* name) = 0;
#endif
	};

	template <typename T>
	class PlugVals
	{
	public:
		PlugVals() {}
	public:
		// 获得所需组件指针，失败返回nullpt
		void __stdcall get(const char* name, T& hr)
		{
			std::lock_guard<std::mutex> lock(_mutexPlugMap);
			auto it = _plugMap.find(name);
			if (it == _plugMap.end())
				return;
			hr = it->second;
		}

		// 约束，第二参数所指对象必须保证释放前delPlug
		void __stdcall add(const char* name, T val)
		{
			std::lock_guard<std::mutex> lock(_mutexPlugMap);
			_plugMap[name] = val;
		}
		void __stdcall del(const char* name)
		{
			std::lock_guard<std::mutex> lock(_mutexPlugMap);
			auto it = _plugMap.find(name);
			if (it != _plugMap.end())
				_plugMap.erase(it);
		}
	private:
		std::mutex _mutexPlugMap;
		std::unordered_map<std::string, T> _plugMap;
	};

	class MyApp : public I_App
	{
	public:
		MyApp() {};
		~MyApp() {};
	private:
		std::string m_str;
		Plug::PlugVals<std::string> m_vals;
		Plug::PlugVals<void*> m_Pointers;
#if _HAS_CXX17
		Plug::PlugVals<std::any> m_Any;
#endif
		void __stdcall delVal(const char* _name)
		{
			m_vals.del(_name);
			m_Pointers.del(_name);
#if _HAS_CXX17
			m_Any.del(_name);
#endif
		}
		void __stdcall setVal(const char* name, const char* val)
		{
			m_vals.add(name, val);
		}
		const char* __stdcall getVal(const char* name)
		{
			m_str = "";
			m_vals.get(name, m_str);
			return m_str.c_str();
		}

		void __stdcall setValPointer(const char* name, void* p)
		{
			m_Pointers.add(name, p);
		}
		void* __stdcall getValPointer(const char* name)
		{
			void* p = nullptr;
			m_Pointers.get(name, p);
			return p;
		}
#if _HAS_CXX17
		void __stdcall setValAny(const char* name, std::any a)
		{
			m_Any.add(name, a);
		}
		std::any __stdcall getValAny(const char* name)
		{
			std::any a;
			m_Any.get(name, a);
			return a;
		}
#endif

	};

	inline I_App* safeGetApp()
	{
		auto sd = GetShareData();
		if (!sd->app)
			sd->app = new MyApp();//写这里是为了解决debug/release 互相调用问
		return sd->app;
	}

	inline I_App* GetApp()
	{
		static I_App* app = nullptr;
		if (app)
			return app;
		app = safeGetApp();
		return app;
	}
#if _HAS_CXX17
	template <typename T>
	void setFunc(const char* name, std::function<T> func)
	{
		std::any a99 = func;
		Plug::GetApp()->setValAny(name, a99);
	}

	template <typename T>
	std::function<T> getFunc(const char* name)
	{
		std::any a99 = Plug::GetApp()->getValAny(name);
		if (a99.has_value())
			return std::any_cast<std::function<T>>(a99);
		std::function<T> b;
		return b;
	}

	inline void setFunc2(const char* name, Func1 func)
	{
		setFunc<void(const char* arg)>(name, func);
	}
	inline Func1 getFunc2(const char* name)
	{
		return getFunc<void(const char* arg)>(name);
	}

	inline void setMultiLan(std::function<const char* (const char*)> fun)
	{
		Plug::setFunc<const char* (const char*)>("Multilingual", fun);
	}
	inline const char* getMultiLan(const char* name)
	{
		static auto fun = Plug::getFunc<const char* (const char*)>("Multilingual");
		return fun(name);
	}

#endif
}

#endif	//_PLUG_APP_H_