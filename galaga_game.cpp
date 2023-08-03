//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) //конструктор класса TForm
	: TForm(Owner)
{

	move = -1; //задаем по умолчанию значение, не равное 1, 2 или 3;
	N = 0;      //по умолчанию кол-во выпущенных астероидов = 0
	aster_speed = 1500;   //скорости по умолчанию соответствуют уровню "Новичок"
	user_speed = 30;
	speed = 100; //скорость астероида по умолчанию
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//кнопка "Начать"
	for(int i = 0; i < N; i++)
	{
		delete aster[i];
	}
	N = 0;
	strike = 0;
	move = -1;
	Image2->Left = 338;
	Timer1->Enabled = true;   //включаем таймер для движения корабля
	Timer2->Enabled = true;   //включаем таймер для создания астероидов
	Image2->Enabled = true;   //включаем Image2 чтобы корабль мог двигаться

	//создаем шкалу здоровья корабля
	int x = 850, y = 272;  //координаты первого элемента
	for(int i = 0; i < 6; i++)
	{
		Health[i] = new TShape(Form1);  //выделяем память под элемент класса
										//TShape
		Health[i]->Parent=Form1;        //Form1 содержит компонент Health[i]
		Health[i]->Shape= stRectangle;  //форма элемента - прямоугольник
		Health[i]->Top = y;             //задаем координаты элемента
		Health[i]->Left = x;
		Health[i]->Height=33;           //задаем размеры элемента
		Health[i]->Width =49;

		Health[i]->Brush->Color= clRed; //задаем цвет элемента - красный
		Health[i]->Visible=True;        //элемент становится видимым
		y += 37;                        //следующий элемент располагаем под предыдущим
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
//таймер контролирующий движения корабля
{
	Timer1->Interval = user_speed; //задаем интервал таймера(скорость движения корабля)

	if(move == 1 && Image2->Left > 0) //move == 1 означает что нажата клавиша A
									  //если нажата клавиша А и корабль не выходит
									  //за границу формы
	{
		Image2->Left -= 5; //сдвигаем корабль влево
	}
	if(move == 2 && Image2->Left + Image2->Width  <= 850)
	//если нажата клавиша D и корабль не доходит до шкалы здоровья
	{
		Image2->Left += 5;  //сдвигаем корабль вправо
	}
	if(move == 3)
	{
		//если нажата клавиша S - стоим на месте
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShortCut(TWMKey &Msg, bool &Handled)
//функция распознает, какая клавиша нажата на клавиатуре
{
    switch (Msg.CharCode)
	{
		case 65:  // код клавиши A - 65
		{
			move = 1;   			//move == 1 означает что нажата клавиша A
			Timer1->Enabled = true; //включаем таймер движения корабля
			Handled = true; 		//даем функции понять, что запрос обрабатывается
		}
		break;
		case 68:  // код клавиши D - 68
		{
			move = 2;
			Timer1->Enabled = true;
			Handled = true;
		}
		break;
		case 83:  // код клавиши S - 83
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
//кнопка "Пауза"
{
	Timer1->Enabled = false;  //останавливаем таймеры и отключаем Image2
	Timer2->Enabled = false;
	Image2->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)  //кнопка "Выход"
{
	Form1->Close();  //закрываем форму
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	Timer2->Interval = aster_speed; //устанавливаем скорость появления астероидов
	aster_fall->Click();            //программно нажимаем невидимую клавишу "астероид"
									//на VCL форме
}
 //---------------------------------------------------------------------------
 void __fastcall TForm1::Timer3Timer(TObject *Sender)
 //таймер регулирует полет каждого астероида
{

	for(int i=0; i<N; i++)
	if(Sender==ast_time[i])
	{
		int Y = aster[i]->Left; //запоминаем координаты текущего астероида
		int X = aster[i]->Top;
		if (H1[i] > 0) //пока не пройдено нужное расстояние
		{
			aster[i]->Top+= 30; //астероид двигается вниз
			H1[i]-=10;          //расстояние постепенно уменьшается

			//проверка на попадания
			if(X >= Image2->Top && X <= Image2->Top + Image2->Height &&
				Y >= Image2->Left && Y <= Image2->Left + Image2->Width && strike < 6)
			//если координаты астероида попадают на площадь корабля
			{
				Health[strike]->Brush->Color = clBlack;
				//окрашиваем пункт шкалы здоровья в черный цвет
				strike++; //увеличиваем счетчик попаданий

				if(strike == 5) //если набралось 6 попаданий (5 т.к. нумерация с 0)
				{
					lost = 1; //отмечаем проигрыш чтобы не создавать больше астероиды

					Timer1->Enabled = false;  //останавливаем движение корабля
					Timer2->Enabled = false;  //останавливаем астероиды
					Image2->Enabled = false;  //отключаем Image2(корабль)
					//выводим на экран информацию о поражении игрока в TImage result
					//result->Picture->LoadFromFile("LOSE.bmp");
					//размеры и координаты картинки "GAME OVER"
					//result->Top = 152;
					//result->Left = 248;
					//result->Height = 200;
					//result->Width = 490;

					break;   //принудительно выходим из цикла


				}


			}

		}

	}
	if(N == 100 && strike < 5)  //если астероиды закончились и кол-во попаданий
								//не достигло 6
	   {

			Timer1->Enabled = false;  //останавливаем движение корабля
			Timer2->Enabled = false;  //останавливаем астероиды
			Image2->Enabled = false;  //отключаем Image2(корабль)
			//выводим информацию о победе на экран
			//result->Picture->LoadFromFile("WIN.bmp");
			//размеры и координаты картинки "YOU WIN"
			//result->Top = 152;
			//result->Left = 248;
			//result->Height = 200;
			//result->Width = 490;
	   }
}
void __fastcall TForm1::aster_fallClick(TObject *Sender)
//кнопка для создания одного астероида
{

	int y = 0; 				//создаем в самой верхней части формы
	int x = rand() % 840;   //положение по оси Х вычисляется случаным образом
							//от левого края формы до шкалы здоровья

	if(N<100 && lost != 1)  //создаем элемент TImage aster[];
	{
		aster[N]=new TImage(Image1); //выделяем память
		aster[N]->Picture->LoadFromFile("asteroid.bmp"); //загружаем картинку
		aster[N]->Top = y;   //устанавливаем начальные координаты
		aster[N]->Left = x;
		aster[N]->Parent = Form1;  //указываем что Form1 содержит aster[N]
		aster[N]->Height=50;   //устанавливаем размеры астероида
		aster[N]->Width =50;

		aster[N]->Visible=True; //делаем элемент видимым

		//вычисляем расстояние, которое должен "пролететь" астероид
		H1[N] = ClientHeight - Image2->Top + Image2->Height - 10;

		//выделяем память под таймер для конкретного астероида
		ast_time[N]=new TTimer(this); //this означает указатель на текущий элемент
		ast_time[N]->Interval = speed;  //устанавливаем скорость астероида
		ast_time[N]->Enabled = true;    //подключаем таймер для текущего астероида

		ast_time[N]->OnTimer=Timer3Timer; 	//функция отклика для каждого астероида
											//Timer3Timer
		N++;  //увеличиваем счетчик созданных астероидов

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//добавляем уровни сложности в ComboBox1
	ComboBox1->Items->Add("Новичок");
	ComboBox1->Items->Add("Профи");
	ComboBox1->Items->Add("Мастер");
	ComboBox1->Items->Add("Безумец");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	//кнопка "Настройки"
	ComboBox1->Visible = true; //делаем видимыми ComboBox1 и кнопку "Сохранить"
	Button5->Visible = true;
	Button5->Enabled = true;  //включаем кнопку "Сохранить"
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	//кнопка "Сохранить"

	int var = ComboBox1->ItemIndex; //присваиваем переменной индекс выбранного
									//уровня сложности
	switch(var)
	{
		case 0:  //уровень "Новичок"
		{
			aster_speed = 1500;   //устанавливаем скорости движения корабля
			user_speed = 30;      //появления астероидов и скорости астероидов
			speed = 100;          //(интервалы таймеров)
		}
		case 1: //уровень "Профи"
		{
			aster_speed = 1100;
			user_speed = 20;
			speed = 90;
		}
		case 3: //уровень "Мастер"
		{
			aster_speed = 600;
			user_speed = 15;
			speed = 90;
		}
		case 4: //уровень "Безумец"
		{
			aster_speed = 200;
			user_speed = 10;
			speed = 80;
        }
	}
	ComboBox1->Visible = false; //делаем невидимыми ComboBox1 и кнопку "Сохранить"
	Button5->Visible = false;
	Button5->Enabled = false;   //отключаем кнопку "Сохранить"
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
//освобождаем выделенную память при закрытии приложения
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

