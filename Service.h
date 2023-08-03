//���������� ����������
#include <string>
#include <list>

#pragma once
using namespace std;

class Service	//����� ��� ������ �� ������� �����
{
private:
	list<string> serv; //���������-���� ������, ������������ �� ���� ������ � ���������� ���������� ����
public:
	Service(void);		//����������� ������
	bool add_service(string serv_name);		//������� ���������� ������ �������� � ������

	int string_to_time(string time, bool hour_or_minute);		//������� ��� �������� ���������� ������� � ������ �������
	bool time_check(string t_begin, string t_end, string t_moment); //������� �������� �� ��������� ������� ������ � ��������� ����������

	//������� ������ �������� �� ��������� ������� � ������� ������
	list<string> get_client_by_serv_order(string serv_name, string t1, string t2, list<string> orders, list<string> clients);
};