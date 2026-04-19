//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout* About;
//---------------------------------------------------------------------------
__fastcall TAbout::TAbout(TComponent* Owner)
    : TForm(Owner)
{
    this->Icon->Handle = Application->Icon->Handle;
}
//---------------------------------------------------------------------------
void __fastcall TAbout::Button1Click(TObject* Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
