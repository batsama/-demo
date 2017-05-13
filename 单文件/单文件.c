#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define LODING_H
#define LEN 25//�������������
#define MENU_H
#define Up 0x48
#define Down 0x50
#define Left 0x4b 
#define Right 0x4d
#define Stu 1;
#define Tea 2;
#define adm 3;
int p;//����Ȩ�ޣ���ʼΪ0
typedef struct CODE
{
	char name[21];
	char password[21];
	struct CODE *pNext;
	int power; //Ȩ��
}Code;//����ע����Ϣ�ڵ�
Code*  P_Head;
typedef struct Data
{
	char strStuName[21];
	char strStuNum[21];
	int strStuSorce;
}Data; //����Data���ݽṹ��
typedef struct NODE
{
	Data data;
	struct NODE* pFont;
	struct NODE* pNext;
}Node;   //�������ݽڵ�
Node* S_Head;//������������ͷ
Code* loadCode(Code* pHead);  //��ȡע����Ϣ
int loginIn(Code* pHead);//��¼����
int lookupPassword(Code* pHead, char* name, char * password); //��ѯָ���˻������Ƿ���ȷ 
Code* P_Ac; //��½�˺���Ϣ
Node* loadData(Node* pHead);//���ļ��ж�ȡѧ������Ϣ
void print(Node* pHead);//��ӡȫ������
void saveData(Node* pHead);//����ѧ����Ϣ���ļ���
Node* freeLink(Node* pHead); //���ѧ����Ϣ
Node* FindStu(Node* pHead);//����ָ��ѧ������Ϣ
int strNum(char* str); //�ж�ѧ���Ƿ���ȷ
Node* rewriteStu(Node*pHead);//�޸�ָ��ѧ������Ϣ
Node* addStu(Node*pHead);//���ѧ����Ϣ
int lookupStu(Node* pHead, char* name); //�ж��Ƿ����ѧ��
Node* delStu(Node* pHead);//���ָ��ѧ����Ϣ
Node* sortStu(Node* pHead);//ð������ ��С����
void AC_Printf(Code* pHead);//��ӡ�����˻���Ϣ 
Code*findCode(Code* pHead, char* name);//����ָ���û���Ϣ
void AC_munu(void);//�˻�����˵�
Code* rewiteCode(Code* pHead);//�޸�ָ���û���Ϣ
Code* AC_del(Code* pHead);//ɾ��ָ���˻���Ϣ
Code* AC_Free(Code* pHead);//����˻���Ϣ
Code* FreeAc(Code* pHead);//�������
void fetchstr(char* str, int num);//��ȡ�ַ�������
void fetchpas(char* str, int num);//��ȡ���뺯��
Code* addCode(Code* pHead, int power); //����һ��ע����Ϣ
void saveCode(Code* pHead); //����ע����Ϣ
int lookup(Code* pHead, char* name); //�ж��Ƿ�����û�
void Nav_menu(void);//��¼ע��ҳ��
void Loginin_menu(void);//��½����
void supervisSystem(int power);//����ϵͳ����
void Gotoxy(int x, int y);//����ƶ�
void Drawbox(void);//��������
void loading(void);//���ؽ���������
void hicehandle(int i);//���ع����Ϣ
void drawnav(void);//������߿�
void powerLoading(int power);//����ɼ�����ϵͳ���ؽ��������� 
int main(void)
{
	system("color F9");
	loading(); 
	Nav_menu();
	return 0;
}
Code* loadCode(Code* pHead)  //��ȡע����Ϣ
{
	FILE * p = NULL;
	Code *pTemp = NULL;
	Code* pNew = NULL;
	char name[21];
	char password[21];
	int power;
	p = fopen("register.txt", "r+ ");
	if (p == NULL)
	{
		system("cls");
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	while (fscanf(p, "�˺�:%s ����:%s Ȩ��:%d\n", name, password, &power) == 3)
	{
		pNew = (Code*)malloc(sizeof(Code));
		if (pNew == NULL)
		{
			system("cls");
			printf("�ڴ�����ʧ��\n");
			exit(0);
		}
		pNew->pNext = NULL;
		strcpy(pNew->name, name);
		strcpy(pNew->password, password);
		pNew->power = power;
		if (pHead == NULL)
		{
			pHead = pNew;
			pTemp = pHead;
		}
		else
		{
			pTemp->pNext = pNew;
			pTemp = pTemp->pNext;
		}
	}
	fclose(p);
	return pHead;
}
int lookupPassword(Code* pHead, char* name, char * password) //��ѯָ���˻������Ƿ��������ж�Ȩ��
{
	Code* pTemp;
	if (pHead == NULL)
	{
		return 0;
	}
		pTemp = pHead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->name,name)==0 &&strcmp(pTemp->password, password) == 0)
			{
				P_Ac = pTemp;  //��ס��½�˺ŵ���Ϣ
				if (pTemp->power == 1)
					return 1;
				if (pTemp->power == 2)
					return 2;
				if (pTemp->power == 3)
					return 3;
			}
			pTemp = pTemp->pNext;
		}
		return 0;
	

}
int loginIn(Code* pHead) //��¼����
{
	Code* pTemp = NULL;
	char name[21];
	char password[21];
	char ch;
	int l=17;
	int p=0, flog = 1, n;
	int flag;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("��ϢΪ��");
		_getch();
		return 0;
	}
	drawnav();
	hicehandle(1);
	while (1)
	{
		Gotoxy(52, 1);
		printf("�������˺���Ϣ:\n");
		Gotoxy(52, 4);
		printf("�˺�:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("����:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		fetchstr(name, 21);
		Gotoxy(57, 6);
		printf("                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		fetchpas(password, 19);
		if (lookupPassword(pHead, name, password) > 0)
		{
			Gotoxy(52,10);
			printf("��¼�ɹ�!");
			hicehandle(0);
			Sleep(1000);
			return lookupPassword(pHead, name, password);
		}
		else
			flog = 1;
		Gotoxy(48, 15);
		printf("�˺Ż��������!\n");
		hicehandle(0);
		while (1)
		{   
			Gotoxy(46, 17);
			printf("  \b");
			Gotoxy(46, 18);
			printf("  \b");
			Gotoxy(48, 16);
			printf("��ѡ��:");
			Gotoxy(48, 17);
			printf("1,���µ�¼");
			Gotoxy(48, 18);
			printf("2.����");
			Gotoxy(47,l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 19)
					l = 17;
			}
			if (flag == Up)
			{
				l--;
				if (l == 16)
					l = 18;
			}
			if (flag == 13)
			{
				if (l == 17)
				{
					break;
				}
				if (l == 18)
				{
					return;
				}
			}
		}
		hicehandle(1);
		drawnav();
	}
}
void AC_munu(void)//�˻�����˵�
{
	int flag;
	int l = 9;
	hicehandle(0);
	if (P_Ac->power < 3)
	{
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.�鿴�˺���Ϣ");
			Gotoxy(53, 10);
			printf("2.�޸��˺���Ϣ");
			Gotoxy(53, 11);
			printf("3.������һ��");
			Gotoxy(52, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				while (l == 12)
					l = 9;
			}
			if (flag == Up)
			{
				l--;
				while (l == 8)
					l = 11;
			}
			if (flag == 13)
			{
				if (l == 9)
				{
					drawnav();
					Gotoxy(40,10);
					printf("�˺�:%-10s ����:%-10s Ȩ��:%d", P_Ac->name, P_Ac->password, P_Ac->power);
					_getch();
				}
				if (l == 10)
				{
					P_Head = rewiteCode(P_Head);
				}
				if (l == 11)
				{
					return;
				}
			}

		}
		return ;
	}
	while (1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.�鿴�����˻���Ϣ");
		Gotoxy(53, 10);
		printf("2.�޸�ָ���˻���Ϣ");
		Gotoxy(53, 11);
		printf("3.ɾ��ָ���˻���Ϣ");
		Gotoxy(53, 12);
		printf("4.��������˻���Ϣ"); 
		Gotoxy(53, 13);
		printf("5.������һ��");
		Gotoxy(52, l);
		printf("%c", 16);
		flag = _getch();
		if (flag == Down)
		{
			l++;
			while (l == 14)
				l = 9;
		}
		if (flag == Up)
		{
			l--;
			while (l == 8)
				l = 13;
		}
		if (flag == 13)
		{
			if (l == 9)
			{

				AC_Printf(P_Head);
			}
			if (l == 10)
			{
				P_Head=rewiteCode(P_Head);
			}
			if (l == 11)
			{
				P_Head = AC_del(P_Head);
			}
			if (l == 12)
			{
				P_Head = AC_Free(P_Head);
			}
			if (l == 13)
			{  
				return;
			}
		}
	}
}
void AC_Printf(Code* pHead)//��ӡ�����˻���Ϣ
{
	Code* pTemp = NULL;
	int num = 0;//��¼�˺Ÿ���
	int i,j,flag=0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("��ϢΪ��");
		_getch();
		return ;
	}
	pTemp = pHead;
	for (i = 1,j=1,pTemp=pHead;pTemp!=NULL; i++,j++,pTemp=pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:�˺�:%-10s ����:%-10s Ȩ��:%d", i, pTemp->name,pTemp->password,pTemp->power);
		if (j%25==0)
		{
			Gotoxy(90, 25);
			printf("�س���һҳ");
			while (1)
			{
				flag = _getch();
				if (13 == flag)
				{ 
					_getch();
					drawnav();
					j = 0;
					break;
				}
			}
		}
	}
	Gotoxy(90, 25);
	printf("�س��˳�");
	while (1)
	{
		flag = _getch();
		if (flag == 13)
		{
			return;
		}
	}
}
Code*findCode(Code* pHead, char* name)//����ָ���û���Ϣ
{
	Code* pTemp=NULL;
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("��ϢΪ��");
		_getch();
		return NULL;
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (strcmp(pTemp->name, name) == 0)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	if (pTemp != NULL)
	{
		drawnav();
		Gotoxy(54, 9);
		printf("�Ѿ���ѯ��");
		Gotoxy(40, 12);
		printf("�˺� : %-10s ���� : %-10s Ȩ�� : %d", pTemp->name, pTemp->password, pTemp->power);
		_getch();
	}
	return pTemp;
}
Code* rewiteCode(Code* pHead)//�޸�ָ���˻�����Ϣ
{
	int flag, flog1 = 1, flog2 = 1, power = 0, l = 9;
	char ch;
	char name[21];
	char newName[21];//������
	char newPassword[21];//������
	char psw[21];//�ظ���������
	Code* pTemp = NULL;
	if (P_Ac->power == 3)
	{
		if (pHead == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("�˻���ϢΪ��");
			_getch();
			return pHead;
		}
		drawnav();
		Gotoxy(45, 10);
		printf("�������˻��˺�:");
		hicehandle(1);
		fetchstr(name, 20);
		pTemp = findCode(pHead, name);
		if (pTemp == NULL)
		{
			drawnav();
			Gotoxy(52, 12);
			printf("���޴���");
			_getch();
			return pHead;//���޴���
		}
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.�޸��˻���");
			Gotoxy(53, 10);
			printf("2.�޸��˻�����");
			Gotoxy(53, 11);
			printf("3.�޸��˻�Ȩ��");
			Gotoxy(53, 12);
			printf("4.������һ��");
			Gotoxy(52, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 13)
					l = 9;
			}
			if (flag == Up)
			{
				l--;
				if (l == 8)
					l = 12;
			}
			if (flag == 13)
			{
				if (l == 9)
				{
					while (flog1)
					{
						drawnav();
						Gotoxy(45, 4);
						printf("���������˺�:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						hicehandle(1);
						fetchstr(newName, 20);
						hicehandle(0);
						if (lookup(pHead, newName) == 0) //�ж��Ƿ�����û� 
						{
							flog1 = 0;
							Gotoxy(20, 4);
							printf("���˺ſ���ʹ��!            ");
						}
						else
						{
							Gotoxy(20, 4);
							printf("���˺��Ѿ�ע���,����������");
							Sleep(1000);
							continue;
						}
					}
					strcpy(pTemp->name, newName);
					drawnav();
					Gotoxy(52, 10);
					printf("�޸ĳɹ���");
					_getch();
					return pHead;
				}
				if (l == 10)
				{
					while (flog2)
					{
						drawnav();
						hicehandle(1);
						Gotoxy(45, 4);
						printf("������������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchstr(newPassword, 19);
						Gotoxy(43, 6);
						printf("���ٴ���������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchstr(psw, 19);
						hicehandle(0);
						if (strcmp(newPassword, psw) == 0)
						{
							flog2 = 0;
						}
						else
						{
							Gotoxy(20, 6);
							printf("���������������,����������");
							Sleep(500);
						}
					}
					strcpy(pTemp->password, newPassword);
					drawnav();
					Gotoxy(52, 10);

					printf("�޸ĳɹ���");
					_getch();
					return pHead;
				}
				if (l == 11)
				{
					while (1)
					{
						l = 11;
						drawnav();
						Gotoxy(52, 10);
						printf("��ѡ��Ȩ��");
						Gotoxy(52, 11);
						printf("ѧ��");
						Gotoxy(52, 12);
						printf("��ʦ");
						Gotoxy(52, 13);
						printf("����Ա");
						Gotoxy(51, l);
						printf("%c", l);
						flag = _getch();
						if (flag == Down)
						{
							l++;
							if (l == 10)
								l = 13;
						}
						if (flag == Up)
						{
							l--;
							if (l == 14)
								l = 11;
						}
						if (flag == 13)
						{
							if (l == 11)
							{
								pTemp->power = 1;
								drawnav();
								Gotoxy(52, 10);
								printf("�޸ĳɹ�!");
								_getch();
								return pHead;
							}
							if (l == 12)
							{
								pTemp->power = 2;
								drawnav();
								Gotoxy(52, 10);
								printf("�޸ĳɹ�!");
								_getch();
								return pHead;
							}
							if (l == 13)
							{
								pTemp->power = 3;
								drawnav();
								Gotoxy(52, 10);
								printf("�޸ĳɹ�!");
								_getch();
								return pHead;
							}
						}
					}
				}
				if (l == 12)
				{
					return pHead;
				}
			}
		}
	}
	else
	{
		pTemp = P_Ac;
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.�޸��˻���");
			Gotoxy(53, 10);
			printf("2.�޸��˻�����");
			Gotoxy(53, 11);
			printf("3.������һ��");
			Gotoxy(52, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 12)
					l = 9;
			}
			if (flag == Up)
			{
				l--;
				if (l == 8)
					l = 11;
			}
			if (flag == 13)
			{
				if (l == 9)
				{
					while (flog1)
					{
						drawnav();
						Gotoxy(45, 4);
						printf("���������˺�:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						hicehandle(1);
						fetchpas(newName, 20);
						hicehandle(0);
						if (lookup(pHead, newName) == 0) //�ж��Ƿ�����û� 
						{
							flog1 = 0;
							Gotoxy(20, 4);
							printf("���˺ſ���ʹ��!            ");
						}
						else
						{
							Gotoxy(20, 4);
							printf("���˺��Ѿ�ע���,����������");
							Sleep(1000);
							continue;
						}
					}
					strcpy(pTemp->name, newName);
					drawnav();
					Gotoxy(52, 10);
					printf("�޸ĳɹ���");
					_getch();
				}
				if (l == 10)
				{
					while (flog2)
					{
						drawnav();
						hicehandle(1);
						Gotoxy(45, 4);
						printf("������������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchpas(newPassword, 19);
						Gotoxy(43, 6);
						printf("���ٴ���������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchpas(psw, 19);
						hicehandle(0);
						if (strcmp(newPassword, psw) == 0)
						{
							flog2 = 0;
						}
						else
						{
							Gotoxy(20, 6);
							printf("���������������,����������");
							Sleep(500);
						}
					}
					strcpy(pTemp->password, newPassword);
					drawnav();
					Gotoxy(52, 10);

					printf("�޸ĳɹ���");
					_getch();
				}
				if (l == 11)
				{
					return pHead;
				}
			}
		}
	}
}
Code* AC_del(Code* pHead)//ɾ��ָ���˻���Ϣ
{ 
	char name[21];
	Code* pCurrent = NULL;
	Code* pTemp = NULL;
	int flag;
	int l = 9;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�˻���ϢΪ��");
		_getch();
		return pHead;
	}
	drawnav();
	Gotoxy(45, 10);
	printf("�������˻��˺�:");
	hicehandle(1);
	fetchstr(name, 20);
	hicehandle(0);
	pTemp = findCode(pHead, name);
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("���޴���");
		_getch();
		return pHead;//���޴���
	}
	if (pTemp != NULL)
	{
		while (1)
		{
			drawnav();
			Gotoxy(47, 8);
			printf("�Ƿ�Ҫɾ�����˺�?");
			Gotoxy(53, 9);
			printf("1.��");
			Gotoxy(53, 10);
			printf("2.��");
			Gotoxy(52, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l ==11)
					l = 9;
			}
			if (flag == Up)
			{
				l--;
				if (l == 8)
					l = 10;
			}
			if (flag == 13)
			{
				if (l == 9)
				{   
					if (pTemp == pHead)
					{
						pHead = pHead->pNext;//ͷ����
						pTemp->pNext = NULL;
						free(pTemp);
						pTemp = NULL;
						return pHead;
					}
					if (pTemp!=pHead)
					{
						pCurrent = pHead;
						while (pCurrent->pNext != NULL)
						{
							if (pCurrent->pNext == pTemp)
							{
								pCurrent->pNext = pTemp->pNext;
								pTemp->pNext = NULL;
								free(pTemp);
								pTemp = NULL; 
								drawnav();
								Gotoxy(52, 8);
								printf("ɾ���ɹ�");
								_getch();
								return pHead;
							}
							pCurrent = pCurrent->pNext;
						}
					}
				}
				if (l == 10)
				{
					AC_munu();
					return pHead;
				}
			}
		}
	}
	return pHead;
}
Code* AC_Free(Code* pHead)//����˻���Ϣ
{
	int flag;
	int l = 9;
	Code* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�˻���ϢΪ��");
		_getch();
		return pHead;
	}
	while (1)
	{
		drawnav();
		Gotoxy(47, 8);
		printf("�Ƿ�Ҫ��������˻���Ϣ?");
		Gotoxy(53, 9);
		printf("1.��");
		Gotoxy(53, 10);
		printf("2.��");
		Gotoxy(52, l);
		printf("%c", 16);
		flag = _getch();
		if (flag == Down)
		{
			l++;
			if (l == 11)
				l = 9;
		}
		if (flag == Up)
		{
			l--;
			if (l == 8)
				l = 10;
		}
		if (flag == 13)
		{
			if (l == 9)
			{
				while (pHead != NULL)
				{
					pTemp = pHead;
					pHead = pHead->pNext;
					free(pTemp);
					pTemp = NULL;
				}
				drawnav();
				Gotoxy(52, 10);
				printf("��ճɹ�");
				_getch();
				return pHead;
			}
			if (l == 10)
			{
				return pHead;
			}
		}
	}
}
Code* FreeAc(Code* pHead)//�������
{
	Code* pTemp;
	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
		pTemp = NULL;
	}
	  return pHead;
}
void fetchstr(char* str, int num)//��ȡ�ַ�������
{
	int i = 0;
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == ' ')
		{
			continue;
		}
		if (ch == 8)
		{
			if(i!=0)
			{
			putchar('\b');
			putchar(' ');
			putchar('\b');
		    }
			if (i>0)
				i--;
			continue;
		}
		if (i == num || ch == 13)
		{
			str[i] = '\0';
			break;
		}
		printf("%c", ch);
		str[i] = ch;
		i++;
	}
	return ;
}
void fetchpas(char* str, int num)//��ȡ���뺯��
{
	int i = 0;
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == ' ')
		{
			continue;
		}
		if (ch == 8)
		{
				if(i!=0)
			{
			putchar('\b');
			putchar(' ');
			putchar('\b');
		    }
			if (i>0)
				i--;
			continue;
		}
		if (i == num || ch == 13)
		{
			str[i] = '\0';
			break;
		}
		printf("*");
		str[i] = ch;
		i++;
	}
	return;
}
Node* loadData(Node* pHead)//���ļ��ж�ȡѧ������Ϣ
{
	FILE *p = fopen("dat.txt", "r+");
	Node *pTemp = NULL;
	Node *pNew = NULL;
	char strname[21];
	char strnum[21];
	int sorce;
	if (p != NULL)
	{
		while (fscanf(p, "����:%s ѧ��:%s �ɼ�:%d\n", strname, strnum, &sorce) == 3)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("�ڴ�����ʧ��\n");
				return NULL;
			}
			strcpy(pNew->data.strStuName, strname);
			strcpy(pNew->data.strStuNum, strnum);
			pNew->data.strStuSorce = sorce;   //��ʼ��
			if (pHead == NULL)//��ͷΪ�� ��һ���ڵ�Ϊͷ
			{
				pHead = pNew;
				pHead->pFont = NULL;
				pHead->pNext = NULL;
				pTemp = pHead;
			}
			else
			{

				pNew->pNext = NULL;
				pNew->pFont = pTemp;
				pTemp->pNext = pNew;
				pTemp = pTemp->pNext;
			}
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	return pHead;
}
void print(Node* pHead)  //��ӡȫ������
{
	Node *pTemp = pHead;
	int num = 0;//��¼ѧ���ĸ���
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return;
	}
	int i, j, flag = 0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("��ϢΪ��");
		_getch();
		return;
	}
	pTemp = pHead;
	for (i = 1, j = 1, pTemp = pHead; pTemp != NULL; i++, j++, pTemp = pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:ѧ��:%10s ����:%6s �ɼ�%3d ", i,pTemp->data.strStuNum,pTemp->data.strStuName,pTemp->data.strStuSorce);
		if (j % 25 == 0)
		{
			Gotoxy(90, 25);
			printf("�س���һҳ");
			while (1)
			{
				flag = _getch();
				if (13 == flag)
				{
					_getch();
					drawnav();
					j = 0;
					break;
				}
			}
		}
	}
	Gotoxy(90, 25);
	printf("�س��˳�");
	while (1)
	{
		flag = _getch();
		if (flag == 13)
		{
			return;
		}
	}
}
void saveData(Node* pHead)//����ѧ����Ϣ���ļ���
{
	FILE *p = NULL;
	Node *pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("ѧ����ϢΪ��\n");
		return;
	}
	p = fopen("dat.txt", "w+");
	if (p != NULL)
	{
		pTemp = pHead;
		while (pTemp != NULL)
		{
			fprintf(p, "����:%s ѧ��:%s �ɼ�:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
			pTemp = pTemp->pNext;
		}
		if (fclose(p) == 0)
		{
			p = NULL;
			return;
		}
		else
		{
			drawnav();
			Gotoxy(52, 10);
			printf("�ļ��ر�ʧ��\n");
			return;
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�ļ���ʧ��\n");
		return;
	}
}
Node* freeLink(Node* pHead) //���ѧ����Ϣ
{
	Node* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("����Ϊ��\n");
		return NULL;
	}
	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
		/*pTemp->pFont = NULL;
		pTemp->pNext = NULL; */
		//�ܱ��е�д��
		pTemp = NULL;
	}
	return pHead;
}
Node* FindStu(Node* pHead)//����ָ��ѧ������Ϣ
{
	Node* pTemp = NULL;
	char str[21];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return NULL;
	}
	while (1)
	{   
		drawnav();
		Gotoxy(45,10);
		hicehandle(1);
		printf("������Ҫ���ҵ�ѧ����ѧ��:");
		fetchstr(str, 20);
		hicehandle(0);
		if (strNum(str))
		{
			break;
		}
		else
		{
			drawnav();
			Gotoxy(53, 10);
			printf("ѧ���������,����������");
			_getch();
		}
	}
	pTemp = pHead;
	while (pTemp != NULL&&strcmp(pTemp->data.strStuNum, str))
	{
		pTemp = pTemp->pNext;
	}
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(53, 10);
		printf("���޴���!");
		_getch();
		return NULL;
	}
	drawnav();
	Gotoxy(53, 10);
	printf("�Ѳ��ҵ����ѧ��!");
	Sleep(500);
	drawnav();
	Gotoxy(35, 10);
	printf("ѧ������:%s ѧ��ѧ��:%s ѧ���ɼ�:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
	_getch();
	return pTemp;
}
int strNum(char* str) //�ж�ѧ���Ƿ���ȷ
{
	int i, flog = 0;
	for (i = 0; i<strlen(str); i++)
	{
		if (str[i] >= '0'&&str[i] <= '9')
		{
			flog++;
		}
	}
	if (flog == strlen(str))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Node* rewriteStu(Node*pHead)
{
	Node* pTemp = NULL;
	Node* pStu = NULL;
	int l =10 , flag;
	char stuNum[21];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return NULL;
	}
	pStu = FindStu(pHead);
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (pTemp == pStu&&pStu!=NULL)
		{
			while (1)
			{
				drawnav();
				Gotoxy(52, 9);
				printf("��ѡ��Ҫ�޸ĵ���Ϣ");
				Gotoxy(52, 10);
				printf("1.ѧ������");
				Gotoxy(52, 11);
				printf("2.ѧ��ѧ��");
				Gotoxy(52, 12);
				printf("3.ѧ���ɼ�");
				Gotoxy(52, 13);
				printf("4.������һ��");
				Gotoxy(51, l);
				printf("%c", 16);
				flag = _getch();
				if (flag == Down)
				{
					l++;
					if (l == 14)
						l = 10;
				}
				if (flag == Up)
				{
					l--;
					if (l == 9)
						l = 13;
				}
				if (flag == 13)
				{
					if (l == 10)
					{
						drawnav();
						Gotoxy(48, 10);
						printf("�������޸ĺ������:");
						hicehandle(1);
						fetchstr(pTemp->data.strStuName, 20);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 11)
					{
						while (1)
						{
							drawnav();
							Gotoxy(48, 10);
							printf("�������޸ĺ��ѧ��:");
							hicehandle(1);
							fetchstr(stuNum, 20);
							while (1)
							{
								if (lookupStu(pHead, stuNum) == 1)
								{
									break;
								}
								else
								{

									Gotoxy(20, 10);
									printf("ѧ���Ѵ������������룡");
									Gotoxy(48, 10);
									printf("�������޸ĺ��ѧ��:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
									fetchstr(stuNum, 20);
								}
							}
							hicehandle(0);
							if (strNum(stuNum) == 1)
							{
								break;
							}
							Gotoxy(52, 12);
							printf("��������ȷѧ�ţ�");
							Sleep(500);
						}
						strcpy(pTemp->data.strStuNum,stuNum);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 12)
					{
						drawnav();
						Gotoxy(52, 10);
						printf("�������޸ĺ�ĳɼ�:");
						hicehandle(1);
						scanf("%d", &pTemp->data.strStuSorce);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 13)
					{
						return pHead;
					}
				}
			}
		}
		pTemp = pTemp->pNext;
	}
	
	drawnav();
	Gotoxy(52, 10);
	printf("���޴���");
	return pHead;
}
Node* addStu(Node*pHead)//���ѧ����Ϣ
{
	int n = 0;   //Ҫ���ѧ���ĸ���
	int flogs = 1;
	int l = 11;
	int i;
	int flag;
	Node* pNew = NULL;
	Node* pStu = NULL;
	Node* pFoot = NULL;
	drawnav();
	Gotoxy(48, 10);
	printf("������Ҫ���ѧ���ĸ���:");
	Gotoxy(48, 12);
	printf("ע����ֻ���һ����Ҫָ��λ��");
	hicehandle(1);
	Gotoxy(72, 10);
	scanf("%d", &n);
	hicehandle(0);
	if (n == 1)  //����һ��ѧ��
	{
		if (pHead == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("����Ϊ��\n");
			return NULL;
		}
		while (pStu == NULL)
		{
			printf("δ�ҵ�����λ�� �����²���\n");
			pStu = FindStu(pHead);
		}
		pNew = (Node*)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("�����ڵ�ʧ��\n");
			return NULL;
		}
		while (flogs)
		{   
			drawnav();
			Gotoxy(48, 10);
			printf("������Ҫ����ѧ������Ϣ:");
			Gotoxy(50, 12);
			printf("ѧ������:");
			Gotoxy(50, 13);
			printf("ѧ��ѧ��:");
			Gotoxy(50, 14);
			printf("ѧ���ɼ�:");
			Gotoxy(60, 12);
			hicehandle(1);
			fetchstr(pNew->data.strStuName, 20);
			Gotoxy(60, 13);
			fetchstr(pNew->data.strStuNum, 20);
			while (1)
			{ 
				if (lookupStu(pHead,pNew->data.strStuNum) == 1)
				{
					break;
				}
				else
				{
					Gotoxy(20, 13);
					printf("ѧ���Ѵ������������룡");
					Gotoxy(50, 13);
					printf("ѧ��ѧ��:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					fetchstr(pNew->data.strStuNum, 20);
				}
				
			}
			Gotoxy(60, 14);
			scanf("%d", &pNew->data.strStuSorce);
			hicehandle(0);
			if (pNew->data.strStuName != NULL&&strNum(pNew->data.strStuNum) && pNew->data.strStuSorce >= 0)
			{
				flogs = 0;
			}
			else
			{
				Gotoxy(60, 20);
				printf("���������Ϣ����,����������\n");
				_getch();
			}
		}
		while (1)
		{
			drawnav();
			Gotoxy(48, 10);
			printf("��ѡ��Ҫ�����λ��\n");
			Gotoxy(48, 11);
			printf("ǰ");
			Gotoxy(48, 12);
			printf("��");
			Gotoxy(47, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 13)
					l = 11;
			}
			if (flag == Up)
			{
				l--;
				if (l == 10)
					l = 12;
			}
			if (flag == 13)
			{
				if (l == 11)   //����ָ��λ��ǰ
				{
					if (pStu == pHead)
					{
						pHead->pFont = pNew;
						pNew->pFont = NULL;
						pNew->pNext = pHead;
						pHead = pHead->pFont;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
					else
					{
						pNew->pNext = pStu;
						pNew->pFont = pStu->pFont;
						pStu->pFont->pNext = pNew;
						pStu->pFont = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
				}
				if (l == 12)
				{
					if (pStu->pNext == NULL)
					{
						pNew->pNext = NULL;
						pNew->pFont = pStu;
						pStu->pNext = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
					else
					{
						pNew->pNext = pStu->pNext;
						pNew->pFont = pStu;
						pStu->pNext->pFont = pNew;
						pStu->pNext = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
				}
			}
		}
	}
	pFoot = pHead;
	if (n > 1)
	{
		for (i = 0; i < n; i++)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("�����ڵ�ʧ��\n");
				return pHead;
			}
			while (1)
			{
				drawnav();
				Gotoxy(48, 10);
				printf("�������%d��Ҫ����ѧ������Ϣ:",i+1);
				Gotoxy(50, 12);
				printf("ѧ������:");
				Gotoxy(50, 13);
				printf("ѧ��ѧ��:");
				Gotoxy(50, 14);
				printf("ѧ���ɼ�:");
				Gotoxy(60, 12);
				hicehandle(1);
				fetchstr(pNew->data.strStuName, 20);
				Gotoxy(60, 13);
				fetchstr(pNew->data.strStuNum, 20);
				while (1)
				{
					if (lookupStu(pHead, pNew->data.strStuNum) == 1)
					{
						break;
					}
					else
					{
						Gotoxy(20, 13);
						printf("ѧ���Ѵ������������룡");
						Gotoxy(50, 13);
						printf("ѧ��ѧ��:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchstr(pNew->data.strStuNum, 20);
					}

				}
				Gotoxy(60, 14);
				scanf("%d", &pNew->data.strStuSorce);
				hicehandle(0);
				if (pNew->data.strStuName != NULL&&strNum(pNew->data.strStuNum) && pNew->data.strStuSorce >= 0)
				{
					break;
				}
				else
				{
					Gotoxy(60, 20);
					printf("���������Ϣ����,����������\n");
				}
			}
			while (pFoot->pNext != NULL&&pHead != NULL)
			{
				pFoot = pFoot->pNext;  //������β
			}
			if (pHead == NULL)
			{
				pHead = pNew;
				pHead->pNext = NULL;
				pHead->pFont = NULL;
			}
			else
			{
				pNew->pNext = NULL;
				pNew->pFont = pFoot;
				pFoot->pNext = pNew;
			}
		}
		drawnav();
		Gotoxy(52, 10);
		printf("��ӳɹ���");
		_getch();
		return pHead;
	}
	return pHead;
}
int lookupStu(Node* pHead, char* Num) //�ж��Ƿ����ѧ��
{
    Node *pTemp = NULL;
	if (pHead == NULL)
	{
		return 1;
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (strcmp(Num, pTemp->data.strStuNum) == 0)
		{
			return 0;
		}
		pTemp = pTemp->pNext;
	}
	return 1;
}
Node* delStu(Node* pHead)//���ָ��ѧ����Ϣ
{
	Node* pTemp;
	int l = 10;
	int flag;
	pTemp = FindStu(pHead);
	while (1)
	{

		drawnav();
		Gotoxy(52, 9);
		printf("�Ƿ�Ҫɾ��?");
		Gotoxy(52, 10);
		printf("1.��");
		Gotoxy(52, 11);
		printf("2.��");
		Gotoxy(51, l);
		printf("%c", 16);
		flag = _getch();
		if (flag == Down)
		{
			l++;
			while (l == 12)
				l = 10;
		}
		if (flag == Up)
		{
			l--;
			while (l == 9)
				l = 11;
		}
		if (flag == 13)
		{
			if (l == 10)
			{
				if (pTemp == pHead)
				{
					pHead = pHead->pNext;
					pHead->pFont = NULL;
					free(pTemp);
					pTemp = NULL;
				}
				else
				{
					if (pTemp->pNext == NULL)
					{
						pTemp->pFont->pNext = NULL;
						free(pTemp);
						pTemp = NULL;
					}
					else
					{
						pTemp->pFont->pNext = pTemp->pNext;
						pTemp->pNext->pFont = pTemp->pFont;
						free(pTemp);
						pTemp = NULL;
					}
				}
				drawnav();
				Gotoxy(52, 10);
				printf("ɾ���ɹ�");
				_getch();
				return pHead;
			}
			if (l == 11)
			{
				return pHead;
			}
		}
	}
}
Node* sortStu(Node* pHead)//ð������ ��С����
{
	Node* pTemp = NULL;
	Node* p = NULL;
	Node* pNew = NULL;
	int i = 0;
	int j = 0;
	int n = 0;
	pNew = (Node*)malloc(sizeof(Node));
	if (pHead== NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("ѧ����ϢΪ��\n");
		return NULL;
	}
	if (pNew == NULL)
	{
		drawnav();
		Gotoxy(52,10);
		printf("����ʧ�ܣ�");
		return pHead;
	}
	pHead->pFont = pNew;
	pNew->pNext = pHead;
	pNew->pFont = NULL;
	pHead = pHead->pFont;
	pTemp = pHead->pNext;
	while (pTemp != NULL)
	{
		pTemp = pTemp->pNext;//temp����
		n++;
	}
	for (i = 1; i<n; i++)
	{
		for (pTemp = pHead->pNext, j = 1; j<n; j++)
		{
			if (pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //ð������
			{
				if (pTemp->pNext->pNext == NULL)  //��С��Ϊ��
				{
					pTemp->pFont->pNext = pTemp->pNext; //���ǰ���ĺ���ָ��С��
					pTemp->pNext->pNext = pTemp; //С�ĺ���ָ����
					pTemp->pNext->pFont = pTemp->pFont; //С��ǰ��ָ����ǰ��
					pTemp->pFont = pTemp->pNext; //���ǰ��ָ��С��
					pTemp->pNext = NULL;  //��ĺ���ָ��NULL
				}
				else
				{
					(pTemp->pFont)->pNext = pTemp->pNext;               //���ǰ���ĺ���ָ��С��
					((pTemp->pNext)->pNext)->pFont = pTemp;             //С�ĺ�����ǰ��ָ����
					pTemp->pNext = ((pTemp->pFont)->pNext)->pNext;     //��ĺ���ָ��С�ĺ���					 
					((pTemp->pFont)->pNext)->pNext = pTemp;            //С�ĺ���ָ����
					((pTemp->pFont)->pNext)->pFont = pTemp->pFont;    //С��ǰ��ָ���ǰ
					pTemp->pFont = ((pTemp->pFont)->pNext);            //���ǰ��ָ��С��
				}
			}
			else
			{
				pTemp = pTemp->pNext;
			}

		}
	}
	p = pHead;
	pHead = pHead->pNext;
	pHead->pFont = NULL;
	free(p);
	p = NULL;
	drawnav();
	Gotoxy(52, 10);
	printf("����ɹ�!");
	return pHead;
}
void Nav_menu(void)//��¼ע��ҳ��
{
	int flag;
	int l = 9;
	extern int p;
	hicehandle(0);
	while (1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.ע��");
		Gotoxy(53, 10);
		printf("2.��¼");
		Gotoxy(53, 11);
		printf("3.�˳�");
		Gotoxy(52, l);
		printf("%c", 16);
		flag = _getch();
		if (flag == Down)
		{
			l++;
			while (l == 12)
				l = 9;
		}
		if (flag == Up)
		{
			l--;
			while (l == 8)
				l = 11;
		}
		if (flag == 13)
		{
			if (l == 9)
			{
				Loginin_menu();
			}
			if (l == 10)
			{
				p = loginIn(P_Head);//Ȩ�ޱ��
				hicehandle(0);
				system("cls");
				if (p > 0)
				{
					powerLoading(p);//ִ�м��ؽ��溯��
					supervisSystem(p);

				}
			}
				if (l == 11)
				{
					saveData(S_Head);
					saveCode(P_Head);
					FreeAc(P_Head);
					freeLink(S_Head);
					exit(0);
				}
			}
	}
}
	void Loginin_menu(void)//ע��ҳ��
	{
		int flag;
		int l = 9;
		hicehandle(0);
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.ѧ��ע��");
			Gotoxy(53, 10);
			printf("2.��ʦע��");
			Gotoxy(53, 11);
			printf("3.����Աע��");
			Gotoxy(53, 12);
			printf("4.������һ��");
			Gotoxy(52, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 13)
					l = 9;
			}
			if (flag == Up)
			{
				l--;
				if (l == 8)
					l = 12;
			}
			if (flag == 13)
			{
				if (l == 9)
				{
					P_Head = addCode(P_Head, 1);
					saveCode(P_Head);
					Nav_menu();
				}
				if (l == 10)
				{
					if (p > 1) //Ȩ����ѧ����֮�ϲ���ע��
					{
						P_Head = addCode(P_Head, 2);
						saveCode(P_Head);
					}
					else
					{
						drawnav();
						Gotoxy(48, 10);
						printf("Ȩ�޲��㣬���ȵ�¼");
						_getch();
					}
					Nav_menu();
				}
				if (l == 11)   //Ȩ������ʦ��֮�ϲ���ע��
				{
					if (p > 2)
					{
						P_Head = addCode(P_Head, 3);
						saveCode(P_Head);
					}
					else
					{
						drawnav();
						Gotoxy(48, 10);
						printf("Ȩ�޲��㣬���ȵ�¼");
						_getch();
					}
					Nav_menu();
				}
				if (l == 12)
				{
					Nav_menu();
				}
			}
		}
	}
	void supervisSystem(int power)//����ϵͳ����
	{
		int flag;
		int l=6;
		hicehandle(0);
		switch (power)
		{
		case 1:while (1)
		    {  
				   drawnav();
				   Gotoxy(54, 4);
				   printf("����ϵͳѧ����");
				   Gotoxy(52, 6);
				   printf("1.��ѯѧ������Ϣ");
				   Gotoxy(52, 7);
				   printf("2.��ӡȫ������Ϣ");
				   Gotoxy(52, 8);
				   printf("3.����ѧ������Ϣ");
				   Gotoxy(52, 9);
				   printf("4.�޸��˺���Ϣ");
				   Gotoxy(52, 10);
				   printf("5.�˳���½");
				   Gotoxy(52, 11);
				   printf("6.�˳�����");
				   Gotoxy(51, l);
				   printf("%c", 16);
				   flag = _getch();
				   if (flag == Down)
				   {
					   l++;
					   if (l == 12)
						   l = 6;
				   }
				   if (flag == Up)
				   {
					   l--;
					   if (l == 5)
						   l = 11;
				   }
				   if (flag == 13)
				   {
					   
					   if (l == 6)
					   {
						   FindStu(S_Head);
					   }
					   if (l == 7)
					   {
						   print(S_Head);
					   }
					   if (l == 8)
					   {
						   S_Head = sortStu(S_Head);
						   print(S_Head);
					   }
					   if (l == 9)
					   {
						   AC_munu();
					   }
					   if (l == 10)
					   {
						   Nav_menu();
					   }
					   if (l == 11)
					   {
						   saveCode(P_Head);
						   drawnav();
						   Gotoxy(54, 12);
						   printf("ллʹ�ã�");
						   saveData(S_Head);
						   saveCode(P_Head);
						   FreeAc(P_Head);
						   freeLink(S_Head);
						   Sleep(2000);
						   exit(0);
					   }
				   }
	    	}		
			break;
		case 2: 
			while (1)
			{
				drawnav();
				Gotoxy(54, 4);
				printf("����ϵͳ��ʦ��");
				Gotoxy(52, 6);
				printf("1.��ѯָ��ѧ������Ϣ");
				Gotoxy(52, 7);
				printf("2.��ӡȫ��ѧ������Ϣ");
				Gotoxy(52, 8);
				printf("3.ɾ��ָ��ѧ������Ϣ");
				Gotoxy(52, 9);
				printf("4.�޸�ָ��ѧ������Ϣ");
				Gotoxy(52, 10);
				printf("5.���һЩѧ������Ϣ");
				Gotoxy(52, 11);
				printf("6.����ѧ������Ϣ");
				Gotoxy(52, 12);
				printf("7.��ʦ�˺Ź���");
				Gotoxy(52, 13);
				printf("8.�˳���½");
				Gotoxy(52, 14);
				printf("9.�˳�����");
				Gotoxy(51, l);
				printf("%c", 16);
				flag = _getch();
				if (flag == Down)
				{
					l++;
					if (l == 15)
						l = 6;
				}
				if (flag == Up)
				{
					l--;
					if (l == 5)
						l = 14;
				}
				if (flag == 13)
				{
					if (l == 6)
					{
						FindStu(S_Head);
					}
					if (l == 7)
					{
						print(S_Head);
					}
					if (l == 8)
					{
						S_Head = delStu(S_Head);
					}
					if (l == 9)
					{
						S_Head = rewriteStu(S_Head);
					}
					if (l == 10)
					{
						S_Head = addStu(S_Head);
					}
					if (l == 11)
					{
						S_Head = sortStu(S_Head);
						print(S_Head);
					}
					if (l == 12)
					{
						AC_munu();
					}
					if (l == 13)
					{
						Nav_menu();
					}
					if (l == 14)
					{
						saveCode(P_Head);
						drawnav();
						Gotoxy(54, 12);
						printf("ллʹ�ã�");
						saveData(S_Head);
						saveCode(P_Head);
						FreeAc(P_Head);
						freeLink(S_Head);
						Sleep(2000);
						exit(0);
					}
				}

			}
			break;
		case 3: //����ˡ���
			while (1)
			{
				drawnav();
				Gotoxy(54, 4);
				printf("����ϵͳ�����");
				Gotoxy(52, 6);
				printf("1.��ѯָ��ѧ������Ϣ");
				Gotoxy(52, 7);
				printf("2.��ӡȫ��ѧ������Ϣ");
				Gotoxy(52, 8);
				printf("3.ɾ��ָ��ѧ������Ϣ");
				Gotoxy(52, 9);
				printf("4.�޸�ָ��ѧ������Ϣ");
				Gotoxy(52, 10);
				printf("5.���һЩѧ������Ϣ");
				Gotoxy(52, 11);
				printf("6.����ѧ������Ϣ");
				Gotoxy(52, 12);
				printf("7.����ϵͳ�˺�");
				Gotoxy(52, 13);
				printf("8.�˳���½");
				Gotoxy(52, 14);
				printf("9.�˳�����");
				Gotoxy(51, l);
				printf("%c", 16);
				flag = _getch();
				if (flag == Down)
				{
					l++;
					if (l == 15)
						l = 6;
				}
				if (flag == Up)
				{
					l--;
					if (l == 5)
						l = 14;
				}
				if (flag == 13)
				{
					if (l == 6)
					{
						FindStu(S_Head);
					}
					if (l == 7)
					{
						print(S_Head);
					}
					if (l == 8)
					{
						S_Head=delStu(S_Head);
					}
					if (l == 9)
					{
						S_Head=rewriteStu(S_Head);
					}
					if (l == 10)
					{
						S_Head = addStu(S_Head);
					}
					if (l == 11)
					{
						S_Head = sortStu(S_Head);
						print(S_Head);
					}
					if (l == 12)
					{
						AC_munu();
					}
					if (l == 13)
					{
						Nav_menu();
					}
					if (l == 14)
					{
						saveCode(P_Head);
						drawnav();
						Gotoxy(54, 12);
						printf("ллʹ�ã�");
						saveData(S_Head);
						saveCode(P_Head);
						FreeAc(P_Head);
						freeLink(S_Head);
						Sleep(2000);
						exit(0);
					}
				}
			}
			break;
		}
		return;
	}
Code* addCode(Code* pHead, int power)
{
	int l=1;
	Code* pNew = (Code*)malloc(sizeof(Code));
	Code* pTemp = NULL; //��סβ�ڵ� 
	char ch;
	char psw[20]; //���������������; 
	int p = 0, flog1 = 1, flog2 = 1;
	if (pNew == NULL)
	{
		system("cls");
		printf("�ڴ�����ʧ��\n");
		exit(0);
		return NULL;
	}
	pTemp = pHead;
	while (pHead != NULL&&pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;   //������β ͷ��Ϊ�� 
	}
	drawnav();
	hicehandle(1);
	while (flog1) //�ж��Ƿ�ע���  
	{
		Gotoxy(52,1);
		switch (power)
		{
		case 1: printf("������ѧ��ע����Ϣ:");
			break;
		case 2: printf("�������ʦע����Ϣ:");
			break;
		case 3: printf("���������Աע����Ϣ;");
		}
		Gotoxy(52, 4);
     	printf("�˺�:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("����:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		fetchstr(pNew->name, 20);
		if (lookup(pHead, pNew->name) == 0) //�ж��Ƿ�����û� 
		{
			flog1 = 0;
			Gotoxy(20, 4);
			printf("���˺ſ���ʹ��!            ");
		}
		else
		{
			Gotoxy(20, 4);
			printf("���˺��Ѿ�ע���,����������");
			continue;
		}
		while (flog2)
		{
			Gotoxy(58, 6);
			printf("                   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			fetchpas(pNew->password, 19);
			Gotoxy(42, 8);
			printf("���ٴ���������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			fetchpas(psw, 19);
			if (strcmp(pNew->password, psw) == 0)
			{
				flog2 = 0;
			}
			else
			{
				Gotoxy(10, 8);
				printf("���������������,����������");
				Sleep(500);
				Gotoxy(42, 8);
				printf("���ٴ���������:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			}                                      
		}
	}
	pNew->power = power;
	pNew->pNext = NULL;
	if (pHead == NULL)   //ͷ��Ϊ�� �½ڵ��Ϊͷ 
	{
		pHead = pNew;
		Gotoxy(52, 15);
		printf("ע��ɹ���");
		Sleep(1000);
		return pHead;
	}
	pTemp->pNext = pNew; //ͷ��Ϊ�� ����β֮�� 
	Gotoxy(52, 15);
	printf("ע��ɹ�!");
	Sleep(1000);
	return pHead;
}
int lookup(Code* pHead, char* name) //�ж��Ƿ�����û�
{
	Code *pTemp = NULL;
	if (pHead == NULL)
	{
		return 0;
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (strcmp(name, pTemp->name) == 0)
		{
			return 1;
		}
		pTemp = pTemp->pNext;
	}
	return 0;
}
void saveCode(Code* pHead) //����ע����Ϣ���ļ���
{
	Code* pTemp = NULL;
	FILE *p = NULL;
	if (pHead == NULL)
	{   
		system("cls");
		printf("ע����ϢΪ��\n");
		Sleep(1000);
		exit(0);
	}
	p = fopen("register.txt", "w+");
	if (p == NULL)
	{
		system("cls");
		printf("�ļ���ʧ��\n");
		Sleep(1000);
		exit(0);
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		fprintf(p,"�˺�:%s ����:%s Ȩ��:%d\n",pTemp->name,pTemp->password,pTemp->power);
		pTemp = pTemp->pNext;
	}
	fclose(p);
	p = NULL;
}
void hicehandle(int i)//���ع����Ϣ
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼����豸���
	CONSOLE_CURSOR_INFO cci;//��������Ϣ�ṹ��
	GetConsoleCursorInfo(handle_out, &cci);//��ȡ��ǰ�����Ϣ
	if (i == 0)
	{
		cci.bVisible = 0;//���ù��Ϊ���ɼ�
	}
	else
	{
		cci.bVisible = 1;
	}
	SetConsoleCursorInfo(handle_out, &cci);
	return;
}
void Gotoxy(int x, int y)  //����ƶ�
{
	HANDLE hout;//����������
	COORD coord;//����ṹ��
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼������
	SetConsoleCursorPosition(hout, coord);//�ƶ����
	return;
}
void Drawbox(void) //��������
{
	printf("\t\t\t\t �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	putchar('\n');
	printf("\t\t\t\t �U                                                  �U");
	putchar('\n');
	printf("\t\t\t\t �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	return;
}
void loading(void)//���ؽ���������
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//������
	//��������
	Gotoxy(52, 5);
	printf(" �ɼ�����ϵͳ\n");
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("��");
		Gotoxy(21, 4);
		printf("\t\t\t\t     �����  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(55, 10);
	printf("�������\n");
	Gotoxy(55, 13);
	printf("����ϵͳ\n");
	P_Head = loadCode(P_Head);
	S_Head = loadData(S_Head);
	Sleep(1000);
	system("cls");
	return;
}
void drawnav(void)//������߿�
{
	int i;
	system("cls");//����
	Gotoxy(0, 0);
	printf("��");//�����Ͻ�
	for (i = 0; i < 58; i++)
	{
		printf("��");//��ˮƽ��
	}
	printf("��"); //�����Ͻ�
	for (i = 1; i <= 26; i++)
	{
		Gotoxy(0, i);
		printf("��");//����ֱ��
		Gotoxy(118, i);
		printf("��");
	}
	printf("��");//�����½�
	for (i = 0; i < 58; i++)
	{
		printf("��");//��ˮƽ��
	}
	printf("��"); //�����½�
	system("color F9");
	Gotoxy(29, 14);
	return;
}
void powerLoading(int power)//����ɼ�����ϵͳ���ؽ��������� 
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//������
	//��������
	Gotoxy(48, 5);
	switch (power)
	{
	case 1 : printf(" �ɼ�����ϵͳ:ѧ����\n");
		break;
	case 2 : printf(" �ɼ�����ϵͳ:��ʦ��\n");
		break;
	case 3 : printf(" �ɼ�����ϵͳ:�����\n");
		break;
	}
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("��");
		Gotoxy(21, 4);
		printf("\t\t\t\t     �����  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(52, 10);
	printf("�������\n");
	Gotoxy(52, 13);
	printf("�������ϵͳ\n");
	Sleep(1000);
	system("cls");
	return;
}
