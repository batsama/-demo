#include"all.h"
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
     	printf("�˺�:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("����:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		scanf_s("%s", pNew->name, 20);
		if (lookup(pHead, pNew->name) == 0) //�ж��Ƿ�����û� 
		{
			flog1 = 0;
			Gotoxy(70, 4);
			printf("���˺ſ���ʹ��!            ");
		}
		else
		{
			Gotoxy(70, 4);
			printf("���˺��Ѿ�ע���,����������");
			continue;
		}
		while (flog2)
		{
			Gotoxy(57, 6);
			printf("          \b\b\b\b\b\b\b\b\b\b");
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
				pNew->password[p++] = ch;//�������� 
			}
			pNew->password[p] = '\0';//�ַ�����β
			p = 0;
			Gotoxy(42, 8);
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
			if (strcmp(pNew->password, psw) == 0)
			{
				flog2 = 0;
			}
			else
			{
				Gotoxy(70, 8);
				printf("���������������,����������");
				Sleep(500);
				Gotoxy(42, 8);
				printf("���ٴ���������:          \b\b\b\b\b\b\b\b\b\b");
			}                                      
			Gotoxy(70, 8);
			printf("                           ");
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
	printf("����ɹ�\n");
	fclose(p);
	p = NULL;
}
