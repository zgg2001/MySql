#ifndef MY_SQL_H
#define MY_SQL_H

#include<iostream>
#include<Windows.h>
#include<WinSock.h>
#include<mysql.h>

class DataBase
{
public:
	DataBase();
	~DataBase();
	//�������ݿ� ����Ϊip �û��� ���� ���ݿ��� �˿�
	bool Connect(const char* ip, const char* name, const char* cypher, const char* database_name, const int port);
	//��ȡ���ڵ��ֶ���
	int GetTableField(const char* table_name);
	//��ѯ�� ����Ϊ����
	bool Query(const char* table_name);
	

private:
	bool _state;//����״̬ trueΪ������
	MYSQL* _mysql;//mysql����  
	MYSQL_FIELD* _fd;//�ֶ�������  
	char _field[32][32];//���ֶ�����ά����  
	MYSQL_RES* _res;//����ṹ�������е�һ����ѯ�����  
	MYSQL_ROW _column;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
	char _query[150];//��ѯ���  
};

#endif // !MY_SQL_H

