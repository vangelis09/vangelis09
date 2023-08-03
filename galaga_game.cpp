//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) //����������� ������ TForm
	: TForm(Owner)
{

	move = -1; //������ �� ��������� ��������, �� ������ 1, 2 ��� 3;
	N = 0;      //�� ��������� ���-�� ���������� ���������� = 0
	aster_speed = 1500;   //�������� �� ��������� ������������� ������ "�������"
	user_speed = 30;
	speed = 100; //�������� ��������� �� ���������
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//������ "������"
	for(int i = 0; i < N; i++)
	{
		delete aster[i];
	}
	N = 0;
	strike = 0;
	move = -1;
	Image2->Left = 338;
	Timer1->Enabled = true;   //�������� ������ ��� �������� �������
	Timer2->Enabled = true;   //�������� ������ ��� �������� ����������
	Image2->Enabled = true;   //�������� Image2 ����� ������� ��� ���������

	//������� ����� �������� �������
	int x = 850, y = 272;  //���������� ������� ��������
	for(int i = 0; i < 6; i++)
	{
		Health[i] = new TShape(Form1);  //�������� ������ ��� ������� ������
										//TShape
		Health[i]->Parent=Form1;        //Form1 �������� ��������� Health[i]
		Health[i]->Shape= stRectangle;  //����� �������� - �������������
		Health[i]->Top = y;             //������ ���������� ��������
		Health[i]->Left = x;
		Health[i]->Height=33;           //������ ������� ��������
		Health[i]->Width =49;

		Health[i]->Brush->Color= clRed; //������ ���� �������� - �������
		Health[i]->Visible=True;        //������� ���������� �������
		y += 37;                        //��������� ������� ����������� ��� ����������
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
//������ �������������� �������� �������
{
	Timer1->Interval = user_speed; //������ �������� �������(�������� �������� �������)

	if(move == 1 && Image2->Left > 0) //move == 1 �������� ��� ������ ������� A
									  //���� ������ ������� � � ������� �� �������
									  //�� ������� �����
	{
		Image2->Left -= 5; //�������� ������� �����
	}
	if(move == 2 && Image2->Left + Image2->Width  <= 850)
	//���� ������ ������� D � ������� �� ������� �� ����� ��������
	{
		Image2->Left += 5;  //�������� ������� ������
	}
	if(move == 3)
	{
		//���� ������ ������� S - ����� �� �����
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShortCut(TWMKey &Msg, bool &Handled)
//������� ����������, ����� ������� ������ �� ����������
{
    switch (Msg.CharCode)
	{
		case 65:  // ��� ������� A - 65
		{
			move = 1;   			//move == 1 �������� ��� ������ ������� A
			Timer1->Enabled = true; //�������� ������ �������� �������
			Handled = true; 		//���� ������� ������, ��� ������ ��������������
		}
		break;
		case 68:  // ��� ������� D - 68
		{
			move = 2;
			Timer1->Enabled = true;
			Handled = true;
		}
		break;
		case 83:  // ��� ������� S - 83
		{
			move = 3;
			Timer1->Enabled = true;
			Handled = true;
		}
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
//������ "�����"
{
	Timer1->Enabled = false;  //������������� ������� � ��������� Image2
	Timer2->Enabled = false;
	Image2->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)  //������ "�����"
{
	Form1->Close();  //��������� �����
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	Timer2->Interval = aster_speed; //������������� �������� ��������� ����������
	aster_fall->Click();            //���������� �������� ��������� ������� "��������"
									//�� VCL �����
}
 //---------------------------------------------------------------------------
 void __fastcall TForm1::Timer3Timer(TObject *Sender)
 //������ ���������� ����� ������� ���������
{

	for(int i=0; i<N; i++)
	if(Sender==ast_time[i])
	{
		int Y = aster[i]->Left; //���������� ���������� �������� ���������
		int X = aster[i]->Top;
		if (H1[i] > 0) //���� �� �������� ������ ����������
		{
			aster[i]->Top+= 30; //�������� ��������� ����
			H1[i]-=10;          //���������� ���������� �����������

			//�������� �� ���������
			if(X >= Image2->Top && X <= Image2->Top + Image2->Height &&
				Y >= Image2->Left && Y <= Image2->Left + Image2->Width && strike < 6)
			//���� ���������� ��������� �������� �� ������� �������
			{
				Health[strike]->Brush->Color = clBlack;
				//���������� ����� ����� �������� � ������ ����
				strike++; //����������� ������� ���������

				if(strike == 5) //���� ��������� 6 ��������� (5 �.�. ��������� � 0)
				{
					lost = 1; //�������� �������� ����� �� ��������� ������ ���������

					Timer1->Enabled = false;  //������������� �������� �������
					Timer2->Enabled = false;  //������������� ���������
					Image2->Enabled = false;  //��������� Image2(�������)
					//������� �� ����� ���������� � ��������� ������ � TImage result
					//result->Picture->LoadFromFile("LOSE.bmp");
					//������� � ���������� �������� "GAME OVER"
					//result->Top = 152;
					//result->Left = 248;
					//result->Height = 200;
					//result->Width = 490;

					break;   //������������� ������� �� �����


				}


			}

		}

	}
	if(N == 100 && strike < 5)  //���� ��������� ����������� � ���-�� ���������
								//�� �������� 6
	   {

			Timer1->Enabled = false;  //������������� �������� �������
			Timer2->Enabled = false;  //������������� ���������
			Image2->Enabled = false;  //��������� Image2(�������)
			//������� ���������� � ������ �� �����
			//result->Picture->LoadFromFile("WIN.bmp");
			//������� � ���������� �������� "YOU WIN"
			//result->Top = 152;
			//result->Left = 248;
			//result->Height = 200;
			//result->Width = 490;
	   }
}
void __fastcall TForm1::aster_fallClick(TObject *Sender)
//������ ��� �������� ������ ���������
{

	int y = 0; 				//������� � ����� ������� ����� �����
	int x = rand() % 840;   //��������� �� ��� � ����������� �������� �������
							//�� ������ ���� ����� �� ����� ��������

	if(N<100 && lost != 1)  //������� ������� TImage aster[];
	{
		aster[N]=new TImage(Image1); //�������� ������
		aster[N]->Picture->LoadFromFile("asteroid.bmp"); //��������� ��������
		aster[N]->Top = y;   //������������� ��������� ����������
		aster[N]->Left = x;
		aster[N]->Parent = Form1;  //��������� ��� Form1 �������� aster[N]
		aster[N]->Height=50;   //������������� ������� ���������
		aster[N]->Width =50;

		aster[N]->Visible=True; //������ ������� �������

		//��������� ����������, ������� ������ "���������" ��������
		H1[N] = ClientHeight - Image2->Top + Image2->Height - 10;

		//�������� ������ ��� ������ ��� ����������� ���������
		ast_time[N]=new TTimer(this); //this �������� ��������� �� ������� �������
		ast_time[N]->Interval = speed;  //������������� �������� ���������
		ast_time[N]->Enabled = true;    //���������� ������ ��� �������� ���������

		ast_time[N]->OnTimer=Timer3Timer; 	//������� ������� ��� ������� ���������
											//Timer3Timer
		N++;  //����������� ������� ��������� ����������

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//��������� ������ ��������� � ComboBox1
	ComboBox1->Items->Add("�������");
	ComboBox1->Items->Add("�����");
	ComboBox1->Items->Add("������");
	ComboBox1->Items->Add("�������");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	//������ "���������"
	ComboBox1->Visible = true; //������ �������� ComboBox1 � ������ "���������"
	Button5->Visible = true;
	Button5->Enabled = true;  //�������� ������ "���������"
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	//������ "���������"

	int var = ComboBox1->ItemIndex; //����������� ���������� ������ ����������
									//������ ���������
	switch(var)
	{
		case 0:  //������� "�������"
		{
			aster_speed = 1500;   //������������� �������� �������� �������
			user_speed = 30;      //��������� ���������� � �������� ����������
			speed = 100;          //(��������� ��������)
		}
		case 1: //������� "�����"
		{
			aster_speed = 1100;
			user_speed = 20;
			speed = 90;
		}
		case 3: //������� "������"
		{
			aster_speed = 600;
			user_speed = 15;
			speed = 90;
		}
		case 4: //������� "�������"
		{
			aster_speed = 200;
			user_speed = 10;
			speed = 80;
        }
	}
	ComboBox1->Visible = false; //������ ���������� ComboBox1 � ������ "���������"
	Button5->Visible = false;
	Button5->Enabled = false;   //��������� ������ "���������"
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
//����������� ���������� ������ ��� �������� ����������
{
	for(int i=0; i<N; i++)
	{
		delete aster[i];
	}
	for(int i=0; i<N; i++)
	{
		delete ast_time[i];
	}

	for(int i = 0; i < 6; i++)
	{
		delete Health[i];
	}
}
//---------------------------------------------------------------------------

