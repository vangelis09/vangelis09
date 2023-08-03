#include <iostream>
//подключаем файлы заголовков
#include "Order.h"
#include "Client.h"
#include "Service.h"

using namespace std;

int main()
 {

	setlocale(LC_ALL, "rus"); //подключаем кириллицу

	//создаем элементы типа классов
	Order MyOrder;
	Client MyClient;
	Service MyService;

	//массив из логических переменных для проверки выполнения операций
	bool func_result[3] = { true, true, true };

	//вводим инфу о первом элементе
	func_result[0] = MyOrder.add_order("23:00");
	func_result[1] = MyClient.add_client("Василий");
	func_result[2] = MyService.add_service("услуга1");

	//проверка правильности ввода данных
	for (int i = 0; i < 3; i++)
	{
		if (func_result[i] == false)
		{
			cout << "Ошибка входных данных!" << endl;
			return 0;
		}
	}

	//о втором элементе
	func_result[0] = MyOrder.add_order("22:00");
	func_result[1] = MyClient.add_client("Алан");
	func_result[2] = MyService.add_service("услуга2");

	for (int i = 0; i < 3; i++)
	{
		if (func_result[i] == false)
		{
			cout << "Ошибка входных данных!" << endl;
			return 0;
		}
	}

	//о третьем элементе
	func_result[0] = MyOrder.add_order("22:00");
	func_result[1] = MyClient.add_client("Вика");
	func_result[2] = MyService.add_service("услуга2");

	for (int i = 0; i < 3; i++)
	{
		if (func_result[i] == false)
		{
			cout << "Ошибка входных данных!" << endl;
			return 0;
		}
	}

	//допустим мы ищем клиентов, заказавших "услуга2" с 19:00 по 22:30

	//создаем списки, чтобы получить доступ к спискам классов Order и Client
	list<string> Orders = MyOrder.get_order();
	list<string> Clients = MyClient.get_client();

	
	list<string> result; //переменная для вывода результата

	//в функцию передаем элементы типа классов, а также имя клиента и значение скидки
	result = MyService.get_client_by_serv_order("услуга2", "19:00", "22:30", Orders, Clients);

	//вывод результата на экран
	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << endl;
	}
	
	return 0;

}