#include"mysql.h"

int main()
{
	DataBase* d1 = new DataBase;
	//����
	d1->Connect("localhost", "root", "123456", "test", 0);
	printf("\n");
	//��ѯ��
	d1->Query("t_student");
	printf("\n");
	//�������
	d1->Implement("insert into t_student values(201916010001, '����', '2019-09-09', now())");
	printf("\n");
	//��ѯ��
	d1->Query("t_student");
	printf("\n");
	return 0;
}