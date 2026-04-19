//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H

#include "..\Tool\I_Tool.H"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
    __published:	// IDE-managed Components
        TLabel* Label1;
        TLabel* Label2;
        TLabel* Label3;
        TEdit* Edit1;
        TEdit* Edit2;
        TButton* Button2;
        TLabel* Label4;
        TGroupBox* GroupBox1;
        TGroupBox* GroupBox2;
        TCheckBox* CheckBox1;
        TCheckBox* CheckBox2;
        TButton* Button1;
        TButton* Button3;
        TMemo* Memo1;
        TComboBox* ComboBox1;
	TButton *Button4;
        void __fastcall FormCreate(TObject* Sender);
        void __fastcall Button2Click(TObject* Sender);
        void __fastcall Button1Click(TObject* Sender);
        void __fastcall FormShow(TObject* Sender);
        void __fastcall Button3Click(TObject* Sender);
        void __fastcall Edit1KeyPress(TObject* Sender, char& Key);
	void __fastcall Button4Click(TObject *Sender);
    private:	// User declarations
        void make_project();
        bool SelectDir2(std::wstring Caption, std::string& Dir);
    public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------
#endif

