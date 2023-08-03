#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>;

using namespace std;

int flag = 0;//эта переменная используется только в обработке исключений

struct A
{
    string name;      //Фамилия владельцa
    string marka;     //Марка автомобиля
    string id;        //Регистрационный номер
    string year;      //Год выпуска
};
struct List
{
    A a;        //элемент типа структуры А
    List* next; //указатель на следующий элемент

};

void First_Init(List** begin) //файловый ввод элемента
{

    ifstream data("data.txt"); //открываем файл для чтения
    if (!data.is_open())        //проверка на открытие файла
    {
        flag = -1;
        //флаг возвращает -1, и при вызове функции в главной программе 
        //выведется сообщение об ошибке открытия файла
    }


    *begin = new List; //выделяем память под новый элемент
    A a; //создаем этот элемент

    //читаем из файла построчно информацию об элементе
    getline(data, (*begin)->a.name);
    getline(data, (*begin)->a.marka);
    getline(data, (*begin)->a.id);
    getline(data, (*begin)->a.year);


    (*begin)->next = NULL; //указатель на следующий элемент

    List* end = *begin; //указатель на конец списка совпадает с указателем на начало, значит в списке 1 элемент

}
void Print(List* b) //вывод в консоль
{
    List* print = b; //дублируем указатель чтобы случайно не изменить указатель, переданный в функцию

    while (print) //пока print не указывает на NULL
    {
        //выводим в консоль строки
        cout << "Owner's name: " << print->a.name << endl;
        cout << "Car model: " << print->a.marka << endl;
        cout << "Registration number: " << print->a.id << endl;
        cout << "Year of issue: " << print->a.year << endl;
        cout << "-------------------------" << endl;

        print = print->next; //меняем адрес указателя на следующий
    }

}
void File_Print(List* b)
//функция вывода списка в файл
{
    List* print = b;                 //дублируем указатель
    ofstream list("data_base.txt");  //открываем файл для записи

    if (!list.is_open())             //проверка открытия файла
    {
        flag = 5;
        return;
    }
    //----------------------------------------------------------
    while (print)
    {

        list << "Owner's name: " << print->a.name << endl;
        list << "Car model: " << print->a.marka << endl;
        list << "Registration number: " << print->a.id << endl;
        list << "Year of issue: " << print->a.year << endl;
        list << "-------------------------" << endl;

        print = print->next;
    }
}
void Delete(List** begin, string a) //удаление элементов(в видео подробно)
{
    if (*begin == NULL) // если указатель на первый элемент равен нулю,
                        // значит элементов нет, изменяем флаг и выходим из функции
    {
        flag = 1;
        return;
    }
    List* t = *begin; //создаем указатель равный указателю на начало списка
    if (t->a.name == a) //удаляем элемент, имя которого совпадает c введенным из консоли
                        //если он является первым или единственным элементом в списке
    {
        *begin = t->next;
        delete t;
        return;
    }
    else flag = 2;
    List* t1 = t->next; //t1 - указатель, который постоянно указывает на элемент,
                        // идущий после текущего

    while (t1) // С помощью цикла находим нужный элемент и удаляем его
    {
        if (t1->a.name == a) //проверяем совпадает ли элемент с нужным
        {
            t->next = t1->next;
            delete t1;
            return;
        }
        else flag = 2;//если не нашли то изменяем флаг
        t = t1;       //и переходим к следующему
        t1 = t1->next;
    }
}
void Insert(List** begin, string a, string b, string c, string d)
//функция вставки элемента в конец списка
{
    List* ins = new List; //создаем новый элемент 

    //заполняем элемент значениями, переданными в функцию
    ins->a.name = a;
    ins->a.marka = b;
    ins->a.id = c;
    ins->a.year = d;

    //создаем указатели типа List
    List* t = *begin;       //первому присваиваем адрес начала списка
    List* t1 = t->next;     //второй указывает на элемент, находящийся следующим после t

    //находим конец списка
    while (t1) //пока указатель на следующий элемент не указывает на NULL
    {
        t = t1;          //меняем адрес для указателя на адрес следующего элемента 
        t1 = t1->next;   //а адрес указателя на следующий элемент на адрес идущего после него
    }

    //теперь t указывает на конец списка
    t->next = ins;      //указатель на следующий элемент после конца теперь указывает на ins
    ins->next = NULL;   //указатель на следующий после ins указывает на NULL, что означает новый конец списка
}
void Add_begin(List** begin, string a, string b, string c, string d)
//функция вставки элемента в начало списка
{
    List* t = new List;


    t->a.name = a;
    t->a.marka = b;
    t->a.id = c;
    t->a.year = d;



    t->next = *begin;
    *begin = t;
}
void menu()
//функция меню, общение с пользователем
{
    cout << "Choose an action : \n";
    cout << "1.Display the database;" << endl;
    cout << "2.Add an element to the beginning of the list;" << endl;
    cout << "3.Add an element to the end of the list;" << endl;
    cout << "4.Delete item;" << endl;
    cout << "5.Output list to file;" << endl;
    cout << "6.Exit." << endl;
}
void Free(List** begin) //освобождение выделенной памяти
{
    if (*begin == NULL) return;
    List* p = *begin;
    List* t;

    while (p)
    {
        t = p;
        p = p->next;
        delete t;
    }
    *begin = NULL;
}

int main()
{
    List* begin = NULL;    //создаем указатель на начало списка, присваиваем ему адрес NULL
    First_Init(&begin);    //вызываем функцию, для прочтения первого элемента из файла


    if (flag != 0) //обработка исключения при ошибке открытия файла
    {
        cout << "Error opening file!\n\n";
        return 0;
    }

    char c; //переменная для работы с оператором выбора switch
    do //используем цикл do-while, чтобы он выполнился как минимум 1 раз
    {
        menu();         //вызываем меню
        cin >> c;       //пользователь вводит номер выбранной операции

        switch (c) //оператор множественного выбора
        {
        case '1': //отображение списка
        {
            system("cls"); //очищаем консоль
            Print(begin);         //вызываем функцию, выводящую список на консоль
        }
        break;

        case '2':   //ввод в начало
        {
            system("cls");    //очищаем консоль
            string name1, marka1, id_1, year1;  //переменные для записи параметров: ФИО, марка машины м тд

            //по очереди вводим 
            cout << "Owner's name: ";
            cin >> name1;

            cout << endl;

            cout << "Car model: ";
            cin >> marka1;
            cout << endl;

            cout << "Registration number: ";
            cin >> id_1;
            cout << endl;

            cout << "Year of issue: ";
            cin >> year1;
            cout << endl;

            //передаем адрес начала списка и введенные строки в функцию
            Add_begin(&begin, name1, marka1, id_1, year1); //добавляем элемент в начало списка

        }
        break;

        case '3':    //ввод в конец
        {
            //точно так же как в предыдущем пункте, только
            //функция вставляет элемент в конец списка

            system("cls");
            string name1, marka1, id_1, year1;

            cout << "Owner's name: ";
            cin >> name1;

            cout << endl;

            cout << "Car model: ";
            cin >> marka1;
            cout << endl;

            cout << "Registration number: ";
            cin >> id_1;
            cout << endl;

            cout << "Year of issue: ";
            cin >> year1;
            cout << endl;

            Insert(&begin, name1, marka1, id_1, year1);
        }
        break;

        case '4':   //удаление элемента
        {
            string name_out; //переменная для вода строки с клавиатуры
            system("cls");  //очищаем консоль

            //проверяем, не пуст ли список
            if (begin == NULL) //если пуст, выводим сообщение и завершаем итерацию цикла
            {
                cout << "No items to remove!" << endl;
                break;
            }

            Print(begin); //выводим весь список на экран
            cout << endl;

            //просим пользователя ввести имя владельца машины, запись о которой хоти удалить
            cout << "Enter the name of the owner of the element to be deleted: \n" << endl << endl;
            cin >> name_out;

            system("cls"); //очищаем консоль
            flag = 0;             //возвращаем значение 0 переменной для обработки исключений
                                  //чтобы результат выполнения других функций не повлиял на работу функции удаления
            Delete(&begin, name_out); //функция удаления, передаем адрес начала списка и введенную строку
            cout << endl;

            //если в функции поменялось значение переменной обработки исключений
            // значит элемент не найден
            if (flag == 2)
            {
                cout << "There is no such element!" << endl;  //выводим соответствующее сообщение
                flag = 0;   //восстанавливаем первоначальное значение пременной flag
            }
            else cout << "Deleted successfully!" << endl; //иначе - сообщение об успешном удалении

        }
        case '5':   //вывод в файл
        {
            system("cls"); //очищаем консоль

            File_Print(begin); //вызываем функию записи в файл
            if (flag == 5) cout << "Error writing to file!" << endl; //если флаг изменился - ошибка записи в файл
            else cout << "Success!" << endl << endl; //иначе - успешная запись

        }
        case '6':   //выход

            break;

        default: cout << "Wrong item! \n \n"; //если пользователь ввел номер, которого нет в списке действий
        }
    } while (c != '6'); //программа работает до тех пор, пока пользователь не выберет "6.Exit" - выход


    Free(&begin); //освобождаем всю выделенную память

    return 0;
}