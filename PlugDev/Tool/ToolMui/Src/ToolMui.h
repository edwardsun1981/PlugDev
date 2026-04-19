#pragma once
#include "..\I_ToolMui.H"

class ToolMui : public I_ToolMui
{
    public:
        ToolMui();
        ~ToolMui();
    private:
        bool __stdcall test(HICON hicon);
        //---------------------------------------------

};