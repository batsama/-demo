#ifndef LOGIN_H
#define LOGIN_H
typedef struct CODE
{
	char name[20];
	char password[20];
	struct CODE *pNext;
	int power; //权限
}Code;//声明注册信息节点
Code*  P_Head;
Code* addCode(Code* pHead, int power); //增加一个注册信息
void saveCode(Code* pHead); //保存注册信息
int lookup(Code* pHead, char* name); //判断是否存在用户
#endif