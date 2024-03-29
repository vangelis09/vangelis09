
#include "Service.h"  //���������� ���� ���������

Service::Service(void) //��� ������ ������������ ������ ���������
{
	serv.clear();
}

bool Service::add_service(string procent_count) //���������� ��������
//��������� ������, ������� ����� ��������
//���������� �������� true/false, ������� ������� �� ������������ ���������� ��������
{
	bool result = true; //���������� ��� �������� ������������ ���������� ��������

	serv.push_back(procent_count); //���������� ����������� �������� � ����� ������
	return result;
}

int Service::string_to_time(string time, bool h_or_m) //������� �������� ������ � ������ �������
//��������� ������, ������� ����� ���������, � ����� ������� ���������� h_or_m
//���� ��� ���������� ����� �������� true, �� ������� ���������� ����, ����� - ������
{
	string t = time; //�������� ������ � ����� ���������� ���� �������� �� ��������
	string tmp;		 //��������� ��������� ���������� ��� �������� string � int
	int res = 0;	 // ���������� ��� ������ ����������

	if (h_or_m == true)	//���� ����� �������� ����
	{
		for (int i = 0; i < 2; i++) //������ ������ ��� ������� ������
		{
			tmp += t[i]; //�������� �� �� ��������� ����������
		}
	}
	else	//���� ����� ������
	{
		for (int i = 3; i < 5; i++)	//������ ��������� ��� ������� ������ (����� ':')
		{
			tmp += t[i]; //�������� �� �� ��������� ����������
		}
	}
	res = stoi(tmp); //������� strind � int
	return res;		//���������� ���������� ��������
}

bool Service::time_check(string t_begin, string t_end, string t_moment) //�������� �������
//��������� ��� ������: ������� ���������� ���������� � ����� ��������� � ������
//���������� �� � ���������� true/false
//���� ����� ������ �������� � ���������� - true, ����� - false
{
	//��������� ���������� ��� ������ �������, �������� ���� � ������
	int h1, h2, h3;
	int m1, m2, m3;

	//��������� ������ � ���� � ������
	h1 = string_to_time(t_begin, true);
	h2 = string_to_time(t_end, true);
	h3 = string_to_time(t_moment, true);

	m1 = string_to_time(t_begin, false);
	m2 = string_to_time(t_end, false);
	m3 = string_to_time(t_moment, false);

	if (h1 > h3 || h2 < h3) // ���� ��� ������ �� �������� � ���������� �� ��������� false
	{
		return false;
	}
	if (h1 < h3 || h2 > h3) //���� ��� ������ �������� � ����������, �� ��������� true
	{
		return true;
	}

	if (h1 == h3)	//���� ��� ������ ����� ������ ������� ����������, ���������� ������
	{
		if (m1 <= m3) //���� ���-�� ����� �� ������� ������ ������, �� ���������� true
		{
			return true;
		}
		else return false; //����� - false
	}

	if (h3 == h2)	//���� ��� ������ ����� ������� ������� ����������, ���������� ������
	{
		if (m3 <= m2)	//���� ����� �� ������� ������ ������, �� ���������� true
		{
			return true;
		}
		else return false; //����� - false
	}
}

//������� ������ �������� �� ��������� ������ � ���������� ����������
list<string> Service::get_client_by_serv_order(string serv_name, string t1, string t2, list<string> orders, list<string> clients)
//��������� 3 ������ � 2 ������
//������: ������������ ������ � ������� ���������� ����������
//������: ������ ������� �� ������ Order � ������ �������� �� ������ Client
//���������� ������ ��������, ��������� ����� �� ��������� ������ � ��������� ���������� �������
{	
	
	
	list<string> Result;	//����� ������ ��� ������ ����������
	int index = 0;	//�������, ��� ������ � �������� ���������

	//��� ������� ������������ �������, ���-�� ��������� ����� ���-�� ��������� ���������������� ������ 
	bool* serv_temp = new bool[serv.size()+1];
	bool* time_tmp = new bool[orders.size()+1];

	for (int i = 0; i < serv.size(); i++) //�� ��������� ��� �������� ������� ������ ����� �������� false
	{
		serv_temp[i] = false;
		time_tmp[i] = false;
	}

	/*
	��� ������� ������� ������������ � �������� �������� �������� 
	� ����������� �������� �� ���� � ������ ����� ��, ������������
	������� ��������� � ���������� � ������� 
	��� ���������� ������ ��������, � �������� ������� ������� � ����� �� �������� ��������� �������� true
	*/

	for (auto j = serv.begin(); j != serv.end(); j++)
	{
		if (*j == serv_name)
		{
			serv_temp[index] = true;
		}
		index++;
	}
	index = 0; //�������� �������

	//���� �������� ���������� �����������, ������ �������� ������ ������� � �������� �� ��������� 
	//������� ������(�������� ������) � ��������� ���������� �������
	for (auto i = orders.begin(); i != orders.end(); i++)
	{
		bool check = time_check(t1, t2, *i); 
		if (check == true) 
		{
			time_tmp[index] = true;
		}
		index++;
	}
	index = 0;
	
	//������ �������� �� ������ ��������
	for (auto i = clients.begin(); i != clients.end(); i++)
	{
		//�������� ������������ ��� �������� �������
		//���� �������� � ���������� �������� � ��� ������������ ����� �������� true
		if (serv_temp[index] == true && time_tmp[index] == true)
		{
			Result.push_back(*i); //�� ��������� ���� ������� �� ������ �������� � �������������� ������
		}
		index++;
	}
	
	return Result; //���������� �������������� ������
}
