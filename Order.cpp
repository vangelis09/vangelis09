#include "Order.h" //подключаем файл заголовка


Order::Order(void) //при вызове конструктора список очищается
{
	ticket.clear();
}

bool Order::add_order(string ticket_name) //функция добавления элемента в конец списка
{
	bool result = true; //переменная для проверки правильности выполнения функции
	
	//проверка на правильность ввода в формате времени "ЧЧ:ММ"
	if (ticket_name.length() > 5 || ticket_name[2] != ':'
		|| !isdigit(ticket_name[0]) || !isdigit(ticket_name[1])
		|| !isdigit(ticket_name[3]) || !isdigit(ticket_name[4])) result = false;

	else ticket.push_back(ticket_name); //push_back() - один из методов, в классе list

	return result;
}

list<string> Order::get_order() //получение доступа к списку заказов
{
	return (ticket); //возвращает список ticket (который в классе является private)
}

