//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Memo1->Text = "";
	Memo2->Text = "";

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    IBQuery1->Close();
	IBQuery1->SQL->Clear();
	IBQuery1->SQL->Add("SELECT * FROM Clients");
	IBQuery1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    IBQuery1->Close();
	IBQuery1->SQL->Clear();
	IBQuery1->SQL->Add("SELECT * FROM Services");
	IBQuery1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	IBQuery1->Close();
	IBQuery1->SQL->Clear();
	IBQuery1->SQL->Add("SELECT * FROM History");
	IBQuery1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(Memo2->Text != "")
	{
		IBQuery1->Close();
		IBQuery1->SQL->Clear();
		IBQuery1->SQL->Add(Memo2->Text);
		IBQuery1->Open();
	}
	else ShowMessage("¬ведите запрос!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    IBQuery1->Close();
	IBQuery1->SQL->Clear();

	Memo2->Text = "SELECT * FROM History WHERE MONTH_USED = '";
	Memo2->Text += Memo1->Text;
	Memo2->Text += "';";
	IBQuery1->SQL->Add(Memo2->Text);
	IBQuery1->Open();
	code = DBGrid1->Fields[1]->Value;

	IBQuery1->Close();
	IBQuery1->SQL->Clear();

	Memo2->Text = "SELECT * FROM Services WHERE CODE = '";
	Memo2->Text += code;
	Memo2->Text += "';";
	IBQuery1->SQL->Add(Memo2->Text);
	IBQuery1->Open();

}

//---------------------------------------------------------------------------
