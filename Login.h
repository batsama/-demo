#ifndef LOGIN_H
#define LOGIN_H
typedef struct CODE
{
	char name[20];
	char password[20];
	struct CODE *pNext;
	int power; //Ȩ��
}Code;//����ע����Ϣ�ڵ�
Code*  P_Head;
Code* addCode(Code* pHead, int power); //����һ��ע����Ϣ
void saveCode(Code* pHead); //����ע����Ϣ
int lookup(Code* pHead, char* name); //�ж��Ƿ�����û�
#endif