//подключаем библиотеки
#include <string>
#include <list>

#pragma once
using namespace std;

class Service	//класс для работы со списком услуг
{
private:
	list<string> serv; //переенная-член класса, представляет из себя список с элементами строкового типа
public:
	Service(void);		//конструктор класса
	bool add_service(string serv_name);		//функция добавления нового элемента в список

	int string_to_time(string time, bool hour_or_minute);		//функция для перевода строкового формата в формат времени
	bool time_check(string t_begin, string t_end, string t_moment); //функция проверки на вхождение времени заказа в указанный промежуток

	//функция поиска клиентов по указанным услугам и времени заказа
	list<string> get_client_by_serv_order(string serv_name, string t1, string t2, list<string> orders, list<string> clients);
};