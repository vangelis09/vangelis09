
//����������� ���������� ��� ������ ������������ �������
#include <string>
#include <list>		

#pragma once			//��������� ������������, �������� ��� ���� ������������ ������ ���� ���

using namespace std;

class Order
{
private:
	list<string> ticket; //������� ������ list, 
					   //������������ �� ���� ������, ���������� �������� ���� string
public:
	Order(void);							//����������� ������
	bool add_order(string ticket_name);		//���������� ��������
	list<string> get_order();				//��������� ������� � ������

};
//��������� ����� ���������� ����������� ����������
