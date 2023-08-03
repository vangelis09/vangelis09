#include <string>
#include <list>

#pragma once
using namespace std;

class Client
{
private:
	list<string> name; //переменная-член класса Client
					   //представляет собой список с элементами типа string
public:
	Client(void);		//конструктор класса
	bool add_client(string client_name);	//функция добавления элемента в список

	list<string> get_client();		//функция получения доступа к списку
};

