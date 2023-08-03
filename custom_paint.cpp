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
	clicked = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
//����� �����
	if(ColorDialog1->Execute()==1)
	Image1->Canvas->Pen->Color=ColorDialog1->Color;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	//������ "��������"
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//������� �����
	k= StrToIntDef(Edit1->Text,1);
	Image1->Canvas->Pen->Width = k;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	clicked = true;
	Image1->Canvas->MoveTo(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
    if (clicked == true)
	{
		Image1->Canvas->LineTo(X,Y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	clicked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	OpenPictureDialog1->DefaultExt=".bmp"; //���������� ����� �� ���������
	OpenPictureDialog1->Filter ="Bitmaps (*.bmp)|*.bmp";

	if (OpenPictureDialog1->Execute()) //�������� �� �����
	{
		Image1->Picture->Bitmap->LoadFromFile(OpenPictureDialog1->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	SavePictureDialog1->DefaultExt=".bmp"; //���������� ����� �� ���������
	SavePictureDialog1->Filter ="Bitmaps (*.bmp)|*.bmp";
	if (SavePictureDialog1->Execute()) //���������� � ����
	{
		Image1->Picture->Bitmap->SaveToFile(SavePictureDialog1->FileName);
	}
}
//---------------------------------------------------------------------------
