///////////////////////////////////////////////////////////////
//
// I_ToolMui.h
// Created at : 2005.11.25
// Description:
//
///////////////////////////////////////////////////////////////
#ifndef	_I_ToolMui_H_
#define	_I_ToolMui_H_

#include "Plug\Plug.h" //please run PlugTool.exe once when con't include.

//base interface
struct I_ToolMui
{
    //test Event allow NULL
    virtual bool __stdcall test(HICON hicon) = 0;
    //Add interface here
};

#endif //_I_ToolMui_H_
