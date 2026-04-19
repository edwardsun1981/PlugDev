///////////////////////////////////////////////////////////////
//
// I_Tool.h
// Created at : 2007.3.23
// Description:
//
///////////////////////////////////////////////////////////////
#pragma once
#include <Plug\Plug.h>
//------------------------------------------------------------------------------------------------------------------
enum ProjectType
{
    Project_vc6 = 0,
    Project_vc7_1,
    Project_vc8,
    Project_vc9,
    Project_vc10,
    Project_vc11,
    Project_vc12,
    Project_vs2015,
    Project_vs2017,
    Project_vs2019,
    Project_vs2022,
    Project_bcb6,
    Project_bcb2006,
    Project_cb2009,
    Project_cb2010,
    Project_cbxe2,
    Project_cbxe10,
    Project_cb10_berlin,
    Project_cb11,
    Project_cb12,
    Project_xcode,
    Project_code_block,
    Project_vs2019_linux
};

struct I_Tool
{
    //Add interface here
    //创建一个工程
    //name工程名称，工程路径
    //type工程类型 ProjectType
    //支持main test
    //支持gui test
    //支持winmain test
    virtual bool __stdcall MakeProject(char* name, char* path, ProjectType type, bool main, bool winmain) = 0;
    virtual bool __stdcall setupVCpath() = 0;
};