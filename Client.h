#include <string>
#include <list>

#pragma once
using namespace std;

class Client
{
private:
	list<string> name; //����������-���� ������ Client
					   //������������ ����� ������ � ���������� ���� string
public:
	Client(void);		//����������� ������
	bool add_client(string client_name);	//������� ���������� �������� � ������

	list<string> get_client();		//������� ��������� ������� � ������
};

