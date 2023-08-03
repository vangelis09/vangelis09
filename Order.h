
//необходимые библиотеки для работы используемых функций
#include <string>
#include <list>		

#pragma once			//директива прероцессора, означает что файл подключается только один раз

using namespace std;

class Order
{
private:
	list<string> ticket; //элемент класса list, 
					   //представляет из себя список, содержащий элементы типа string
public:
	Order(void);							//конструктор класса
	bool add_order(string ticket_name);		//добавление элемента
	list<string> get_order();				//получение доступа к списку

};
//остальные файлы заголовков описываются аналогично
