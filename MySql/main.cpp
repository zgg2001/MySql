#include"mysql.h"

int main()
{
	DataBase* d1 = new DataBase;
	//连接
	d1->Connect("localhost", "root", "123456", "test", 0);
	printf("\n");
	//查询表
	d1->Query("t_student");
	printf("\n");
	//添加内容
	d1->Implement("insert into t_student values(201916010001, '赵四', '2019-09-09', now())");
	printf("\n");
	//查询表
	d1->Query("t_student");
	printf("\n");
	return 0;
}