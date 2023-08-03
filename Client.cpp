#include "Client.h"	//подключаем файл заголовка

Client::Client(void) //конструктор класса 
{
	name.clear();	//при вызове конструктора список очищается
}

bool Client::add_client(string client_name) //добавление элемента
{
	bool result = true;
	name.push_back(client_name);

	return result;
}

list<string> Client::get_client()	//получение доступа к переменной name
{
	return name;
}
