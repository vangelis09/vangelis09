#include "Client.h"	//���������� ���� ���������

Client::Client(void) //����������� ������ 
{
	name.clear();	//��� ������ ������������ ������ ���������
}

bool Client::add_client(string client_name) //���������� ��������
{
	bool result = true;
	name.push_back(client_name);

	return result;
}

list<string> Client::get_client()	//��������� ������� � ���������� name
{
	return name;
}
