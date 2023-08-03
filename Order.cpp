#include "Order.h" //���������� ���� ���������


Order::Order(void) //��� ������ ������������ ������ ���������
{
	ticket.clear();
}

bool Order::add_order(string ticket_name) //������� ���������� �������� � ����� ������
{
	bool result = true; //���������� ��� �������� ������������ ���������� �������
	
	//�������� �� ������������ ����� � ������� ������� "��:��"
	if (ticket_name.length() > 5 || ticket_name[2] != ':'
		|| !isdigit(ticket_name[0]) || !isdigit(ticket_name[1])
		|| !isdigit(ticket_name[3]) || !isdigit(ticket_name[4])) result = false;

	else ticket.push_back(ticket_name); //push_back() - ���� �� �������, � ������ list

	return result;
}

list<string> Order::get_order() //��������� ������� � ������ �������
{
	return (ticket); //���������� ������ ticket (������� � ������ �������� private)
}

