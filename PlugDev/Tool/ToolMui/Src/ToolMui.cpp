#include "ToolMui.h"

PLUG_COMPONENT_AUTO_REG(ToolMui)//DO NOT EDIT THIS
//------------------------------------------------------------------------------------------------------------------
#include "Unit1.h"

ToolMui::ToolMui()
{
}

ToolMui::~ToolMui()
{
}

bool __stdcall ToolMui::test(HICON hicon)
{
    try
    {
        Application->Initialize();
		Application->CreateHandle();
		Application->Icon->Handle = hicon;
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();

        delete Form1;
    }
    catch (Exception& exception)
    {
        Application->ShowException(&exception);
    }
    catch (...)
    {
        try
        {
            throw Exception("Tofo Im Exception");
        }
        catch (Exception& exception)
        {
            Application->ShowException(&exception);
        }
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------------
