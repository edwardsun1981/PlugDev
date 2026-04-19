//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TAbout : public TForm
{
    __published:	// IDE-managed Components
        TLabel* Label1;
        TLabel* Label2;
        TLabel* Label3;
        TButton* Button1;
        void __fastcall Button1Click(TObject* Sender);
    private:	// User declarations
    public:		// User declarations
        __fastcall TAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout* About;
//---------------------------------------------------------------------------
#endif
