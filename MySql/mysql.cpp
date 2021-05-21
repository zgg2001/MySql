#include "mysql.h"

DataBase::DataBase()
{
    _state = false;
    _mysql = new MYSQL; 
    _fd = nullptr;
    memset(_field, NULL, sizeof(_field));
    _res = nullptr;
    _column = nullptr;
    memset(_query, NULL, sizeof(_query));
}

DataBase::~DataBase()
{
}

bool DataBase::Connect(const char* ip, const char* name, const char* cypher, const char* database_name, const int port)
{
    if (true == _state)
    {
        printf("Database connected\n");
        return false;
    }
    //��ʼ��mysql  
    mysql_init(_mysql);
    //����false������ʧ�ܣ�����true�����ӳɹ�  
    if (!(mysql_real_connect(_mysql, ip, name, cypher, database_name, port, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
    {
        printf("Error connecting to database:%s\n", mysql_error(_mysql));
        return false;
    }
    else
    {
        _state = true;
        printf("Connected succeed\n\n");
        return true;
    }
    return true;
}

int DataBase::GetTableField(const char* table_name)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return -1;
    }
    //��ѯ����
    sprintf_s(_query, "desc %s", table_name); //desc ����ȡ�ֶ���
    //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd���������� 
    mysql_query(_mysql, "set names gbk");
    //����0 ��ѯ�ɹ�������1��ѯʧ��  
    if (mysql_query(_mysql, _query))    //ִ��SQL���
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    //��ȡ�����  
    if (!(_res = mysql_store_result(_mysql)))   //���sql�������󷵻صĽ����  
    {
        printf("Couldn't get result from %s\n", mysql_error(_mysql));
        return false;
    }
    //����������Ϊ�ֶθ���
    return mysql_affected_rows(_mysql);
}

bool DataBase::Query(const char* table_name)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return false;
    }
    //��ȡ�ֶ���
    int field = GetTableField(table_name);
    //��ѯ����
    sprintf_s(_query, "select * from %s", table_name); //ִ�в�ѯ��� 
    //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd���������� 
    mysql_query(_mysql, "set names gbk");
    //����0 ��ѯ�ɹ�������1��ѯʧ��  
    if (mysql_query(_mysql, _query))    //ִ��SQL���
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    else
    {
        printf("query success\n");
    }
    //��ȡ�����  
    if (!(_res = mysql_store_result(_mysql)))   //���sql�������󷵻صĽ����  
    {
        printf("Couldn't get result from %s\n", mysql_error(_mysql));
        return false;
    }
    //��ӡ��������  
    printf("number of dataline returned: %lld\n", mysql_affected_rows(_mysql));
    //��ȡ�ֶε���Ϣ  
    char* str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ  
    for (int i = 0; i < field; i++)  //����֪�ֶ�����������»�ȡ�ֶ���  
    {
        str_field[i] = mysql_fetch_field(_res)->name;
    }
    for (int i = 0; i < field; i++)  //��ӡ�ֶ�  
    {
        printf("%10s\t", str_field[i]);
    }
    printf("\n");
    //��ӡ��ȡ������  
    while (_column = mysql_fetch_row(_res))   //����֪�ֶ���������£���ȡ����ӡ��һ��  
    {
        for (int i = 0; i < field; i++)
        {
            printf("%10s\t", _column[i]);  //column��������  
        }
        printf("\n");
    }
    return true;
}

bool DataBase::Implement(const char* sentence)
{
    if (false == _state)
    {
        printf("Database not connected\n");
        return false;
    }
    //��ѯ����
    sprintf_s(_query, "%s", sentence); //desc ����ȡ�ֶ���
    //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd���������� 
    mysql_query(_mysql, "set names gbk");
    //ִ��SQL���
    if (mysql_query(_mysql, _query))    
    {
        printf("Query failed (%s)\n", mysql_error(_mysql));
        return false;
    }
    return true;
}
