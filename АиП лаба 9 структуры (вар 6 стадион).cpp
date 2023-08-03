#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool except = false; //переменная для обработки исключений

struct stadion
{
	string name = "empty";      //название стадиона
	string sport = "empty";     //вид спорта
	int year = 0;               //год постройки
	string country = "empty";   //страна
	string city = "empty";      //город
	string street = "empty";    //улица
	int adres = 0;              //адрес
	int colvo_mest = 0;         //вместимость(чел.)
	int ploshadki = 0;          //количество площадок
	string type_of_tab = "empty";//тип табло

	bool flag = 0; //флаговая переменная для поиска нужного элемента
};

stadion read_from_file(stadion* base, int size)
//функция чтения из файла
//принимает указатель на массив структур и размер массива
//возвращает указатель на заполненный массив структур
{
	ifstream fin("input.txt");
	if (!fin.is_open()) //проверка на открытие файла
	{
		cout << "Error opening file!";
		except = true; //исключение для остановки основной программы
	}
	else
	{
		while (!fin.eof()) //чтение массива структур из фойла
		{
			for (int i = 0; i < size; i++)
			{
				fin >> base[i].name;
				fin >> base[i].sport;
				fin >> base[i].year;
				fin >> base[i].country >> base[i].city >> base[i].street >> base[i].adres;
				fin >> base[i].colvo_mest;
				fin >> base[i].ploshadki;
				fin >> base[i].type_of_tab;
			}
		}
	}
	fin.close(); //закрытие файла
	return(*base);
}
void write_file(stadion* base, int size)
//функция для записи результатов в файл
//принимает указатель на массив структур и размер массива
//тип возвращаемого значения void(нет возвращаемого значения)
{
	string path = "output.txt";
	ofstream fout; //создаем файл с именем "output.txt"
	fout.open(path);//открываем файл
	for (int i = 0; i < size; i++)
	{
		fout << "Stadion: " << base[i].name << endl;
		fout << "Sports: " << base[i].sport << endl;
		fout << "Year: " << base[i].year << endl;
		fout << "Adress: " << base[i].country << " "
			<< base[i].city << " " << base[i].street << " " << base[i].adres << endl;
		fout << "Count of people: " << base[i].colvo_mest << endl;
		fout << "Count of places: " << base[i].ploshadki << endl;
		fout << "Type of the scoreboard: " << base[i].type_of_tab << endl;
		fout << endl;
	}
	fout.close();
}




stadion search(stadion* base, string city, int size)
//функция для поиска элемента в массиве
//принимает указатель на массив струтур,
//элемент, по которому производится поиск нужной структуры
//и размер массива
//возвращает массив с расставленными флажками
{
	bool flag2 = 0; //переменная для обработки исключения
	for (int i = 0; i < size; i++) //итерация массива структур
	{
		if (base[i].city == city)    //если город указанный в элементе массива
		{                            //совпадает с переданным в функция значением
			base[i].flag = 1;        //отмечаем данный элемент флажком
			flag2 = 1;               //flag2 = 1 сообщает нам, что существует искомый элемент
		}
		if (i == size - 1 && flag2 == 0) //если после прохождения массива элемент не найден
		{
			cout << "Not found" << endl; //выводится данное сообщение
		}
	}
	return(*base); //возвращаем массив с расставленными флажками
}

void print(stadion* base, int size)
//функция для вывода массива на экран
//принимает указатель на массив структур и размер массива
{
	for (int i = 0; i < size; i++)
	{
		cout << "Stadion: " << base[i].name << endl;
		cout << "Sports: " << base[i].sport << endl;
		cout << "Year: " << base[i].year << endl;
		if (base[i].country == "empty") //если в массиве пуст, 
		{
			cout << "Adress: " << base[i].country << endl;  // "empty" в поле "Adress: " выводится только один раз
															//т.к. адрес разделяется на 4 переменных
		}                                                    //(страна, город, улица, номер)
		else
		{
			cout << "Adress: " << base[i].country << " "
				<< base[i].city << " " << base[i].street << " " << base[i].adres << endl;
		}

		cout << "Count of people: " << base[i].colvo_mest << endl;
		cout << "Count of places: " << base[i].ploshadki << endl;
		cout << "Type of the scoreboard: " << base[i].type_of_tab << endl;
		cout << endl;
	}
}
void menu()
//функция для общения с пользователем
{
	cout << "Choose an action: " << endl;
	cout << "1. Show list;" << endl;
	cout << "2. Add information;" << endl;
	cout << "3. Search;" << endl;
	cout << "4. Save to the file;" << endl;
	cout << "5. Order the array;" << endl;
	cout << "6. Exit." << endl;
}

stadion* extendedArray(stadion* A, int arraySize, stadion newValue)
//функция для создания нового массива
//используется для добавления элемента в массив структур
//ПРИНИМАЕТ указатель на массив структур,
//размер массива и новый элемент
//ВОЗВРАЩАЕТ новый массив структур, размер которого
//больше размера старого массива на 1
{
	stadion* newArray = new stadion[arraySize + 1];
	for (int i = 0; i < arraySize; ++i)
	{
		newArray[i] = A[i];
	}
	newArray[arraySize] = newValue;
	return newArray;
}

int comp(const stadion* i, const stadion* j)
{
	//функция сравнения двух элементов
	//используется в функции qsort
	//принимает указатели на элементы массива структур
	//возвращает разность этих элементов

	int result;
	result = i->year - j->year;
	return result;

}

int main()
{
	int size; //размер массива
	cout << "Count of elements: ";
	cin >> size;
	stadion* base = new stadion[size]; //создаем основной массив структур
	stadion* tmp = 0;    //создаем указатель для временного массива
						//т.к. он будет использоваться при добавлении новых элементов

	read_from_file(base, size); //считываем данные из файла
	if (except == true)
	{
		return 0; //если файл не открылся, то выходим из программы
	}

	int a = 100; //переменная для работы с меню
				 //значение 100 - случайное, неравное 6

	do   //программа выполняется до тех пор,
	{                //пока пользователь не введет 6
					//для выхода из программы
		menu();             //вызываем меню
		cin >> a;         //выбираем один из пунктов меню

		switch (a)
		{
		case 1: //вывести на консоль массив структур
		{
			system("cls"); //функция очистки консоли
			print(base, size); //функция вывода массива на консоль
		}
		break;
		case 2: //добавление нового элемента
		{
			system("cls");
			//сперва создаем новый элемент
			stadion added;

			//вводим с клавиатуры параметры для нового элемента
			cout << "Info about the new stadion: " << endl;
			cout << "Name: ";
			cin >> added.name;

			cout << "Sports: ";
			cin >> added.sport;

			cout << "Year: ";
			cin >> added.year;

			cout << "Adress: ";
			cin >> added.country >> added.city >> added.street >> added.adres;

			cout << "Count of people: ";
			cin >> added.colvo_mest;

			cout << "Count of places: ";
			cin >> added.ploshadki;

			cout << "Type of the scoreboard: ";
			cin >> added.type_of_tab;

			system("cls");

			//создаем временный массив
			tmp = extendedArray(base, size, added);

			//очищаем старый массив
			delete[] base;

			//УКАЗАТЕЛЬ СТАРОГО МАССИВА УКАЗЫВАЕТ НА НОВЫЙ
			base = tmp;
			// удаляем временный массив
			tmp = 0;
			++size; //увеличиваем размер массива на 1
		}
		break;
		case 3: //поиск стадиона по городу, в котором он находится
		{
			system("cls");
			string city;
			//пользователь вводит нужный город
			cout << "Where is your stadion: ";
			cin >> city;
			cout << endl;

			//функция поиска
			search(base, city, size);
			for (int i = 0; i < size; i++) //итерация массива структур
			{
				//выводим только те элементы,
				//для которых функция search() установила flag=1
				if (base[i].flag == 1)
				{
					cout << "Stadion: " << base[i].name << endl;
					cout << "Sports: " << base[i].sport << endl;
					cout << "Year: " << base[i].year << endl;
					cout << "Adress: " << base[i].country << " "
						<< base[i].city << " " << base[i].street << " " << base[i].adres << endl;
					cout << "Count of people: " << base[i].colvo_mest << endl;
					cout << "Count of places: " << base[i].ploshadki << endl;
					cout << "Type of the scoreboard: " << base[i].type_of_tab << endl;
					cout << endl;
				}
			}
		}
		break;
		case 4:    //сохраняем массив в файл
		{
			system("cls");
			write_file(base, size); //функция записи в файл
		}
		break;
		case 5: //упорядочивание массива структур(сортировка)
		{
			system("cls");
			//сортируем массив по году постройки
			//от самого старого к самому новому
			qsort(base, size, sizeof(stadion), (int(*) (const void*, const void*)) comp);
			//выводим отсортированный массив
			print(base, size);
		}
		break;
		case 6: return 0; //нажата клавиша 6 для выхода

		default: 
		{
			cout << "ERROR!"; //при введении неверного значения выведется ошибка
			a = 0;
		}
		}
	}while (a != 6);

	delete[]base; //освобождаем выделенную память
	delete[]tmp;

	return 0;
}



