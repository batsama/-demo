#include"all.h"
void AC_munu(void)//�˻�����˵�
{
	int flag;
	int l = 9;
	hicehandle(0);
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
	int flag,flog1=1,flog2=1,power=0,l=9;
	char ch;
	char name[20];
	char newName[20];//������
	char newPassword[20];//������
	char psw[20];//�ظ���������
	Code* pTemp = NULL;
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
	scanf_s("%s", name, 20);
	pTemp = findCode(pHead, name);
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("���޴���");
		_getch();
		return pHead;//���޴���
	}
	while(1)
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
					printf("���������˺�:          \b\b\b\b\b\b\b\b\b\b");
					hicehandle(1);
					scanf_s("%s", newName, 20);
					hicehandle(0);
					if (lookup(pHead,newName) == 0) //�ж��Ƿ�����û� 
					{
						flog1 = 0;
						Gotoxy(70, 4);
						printf("���˺ſ���ʹ��!            ");
					}
					else
					{
						Gotoxy(70, 4);
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
					printf("������������:          \b\b\b\b\b\b\b\b\b\b");
					while ((ch = _getch()) != '\r')//�ж��Ƿ�Ϊ�س�
					{
						if (ch == 8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if (p>0)
								p--;
						}
						if (!isdigit(ch) && !isalpha(ch))//�ж��Ƿ������ֻ��ַ���
							continue;
						putchar('*');
						newPassword[p++]= ch;//�������� 
					}
					newPassword[p] = '\0';//�ַ�����β
					p = 0;
					Gotoxy(43, 6);
					printf("���ٴ���������:          \b\b\b\b\b\b\b\b\b\b");
					while ((ch = _getch()) != '\r')//�ж��Ƿ�Ϊ�س�
					{
						if (ch == 8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if (p>0)
								p--;
						}
						if (!isdigit(ch) && !isalpha(ch))//�ж��Ƿ������ֻ��ַ���
							continue;
						putchar('*');
						psw[p++] = ch;//�������� 
					}
					psw[p] = '\0';//�ַ�����β
					p = 0;
					hicehandle(0); 
					if (strcmp(newPassword, psw) == 0)
					{
						flog2 = 0;
					}
					else
					{
						Gotoxy(70, 6);
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
				AC_munu();
			}
		}
	}
}
Code* AC_del(Code* pHead)//ɾ��ָ���˻���Ϣ
{ 
	char name[20];
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
	scanf_s("%s", name, 20);
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