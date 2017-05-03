#include"all.h"
Code* addCode(Code* pHead, int power)
{
	int l=1;
	Code* pNew = (Code*)malloc(sizeof(Code));
	Code* pTemp = NULL; //记住尾节点 
	char ch;
	char psw[20]; //二次输入密码检验; 
	int p = 0, flog1 = 1, flog2 = 1;
	if (pNew == NULL)
	{
		system("cls");
		printf("内存申请失败\n");
		exit(0);
		return NULL;
	}
	pTemp = pHead;
	while (pHead != NULL&&pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;   //遍历找尾 头不为空 
	}
	drawnav();
	hicehandle(1);
	while (flog1) //判断是否注册过  
	{
		Gotoxy(52,1);
		switch (power)
		{
		case 1: printf("请输入学生注册信息:");
			break;
		case 2: printf("请输入教师注册信息:");
			break;
		case 3: printf("请输入管理员注册信息;");
		}
		Gotoxy(52, 4);
     	printf("账号:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("密码:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		scanf_s("%s", pNew->name, 20);
		if (lookup(pHead, pNew->name) == 0) //判断是否存在用户 
		{
			flog1 = 0;
			Gotoxy(70, 4);
			printf("该账号可以使用!            ");
		}
		else
		{
			Gotoxy(70, 4);
			printf("该账号已经注册过,请重新输入");
			continue;
		}
		while (flog2)
		{
			Gotoxy(57, 6);
			printf("          \b\b\b\b\b\b\b\b\b\b");
			while ((ch = _getch()) != '\r')//判断是否为回车
			{
				if (ch == 8)
				{
					putchar('\b');
					putchar(' ');
					putchar('\b');
					if (p>0)
						p--;
				}
				if (!isdigit(ch) && !isalpha(ch))//判断是否是数字或字符串
					continue;
				putchar('*');
				pNew->password[p++] = ch;//保存密码 
			}
			pNew->password[p] = '\0';//字符串结尾
			p = 0;
			Gotoxy(42, 8);
			printf("请再次输入密码:          \b\b\b\b\b\b\b\b\b\b");
			while ((ch = _getch()) != '\r')//判断是否为回车
			{
				if (ch == 8)
				{
					putchar('\b');
					putchar(' ');
					putchar('\b');
					if (p>0)
						p--;
				}
				if (!isdigit(ch) && !isalpha(ch))//判断是否是数字或字符串
					continue;
				putchar('*');
				psw[p++] = ch;//保存密码 
			}
			psw[p] = '\0';//字符串结尾
			p = 0;
			if (strcmp(pNew->password, psw) == 0)
			{
				flog2 = 0;
			}
			else
			{
				Gotoxy(70, 8);
				printf("二次密码输入错误,请重新输入");
				Sleep(500);
				Gotoxy(42, 8);
				printf("请再次输入密码:          \b\b\b\b\b\b\b\b\b\b");
			}                                      
			Gotoxy(70, 8);
			printf("                           ");
		}
	}
	pNew->power = power;
	pNew->pNext = NULL;
	if (pHead == NULL)   //头若为空 新节点变为头 
	{
		pHead = pNew;
		Gotoxy(52, 15);
		printf("注册成功！");
		Sleep(1000);
		return pHead;
	}
	pTemp->pNext = pNew; //头不为空 接在尾之后 
	Gotoxy(52, 15);
	printf("注册成功!");
	Sleep(1000);
	return pHead;
}
int lookup(Code* pHead, char* name) //判断是否存在用户
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
void saveCode(Code* pHead) //保存注册信息到文件中
{
	Code* pTemp = NULL;
	FILE *p = NULL;
	if (pHead == NULL)
	{   
		system("cls");
		printf("注册信息为空\n");
		Sleep(1000);
		exit(0);
	}
	p = fopen("register.txt", "w+");
	if (p == NULL)
	{
		system("cls");
		printf("文件打开失败\n");
		Sleep(1000);
		exit(0);
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		fprintf(p,"账号:%s 密码:%s 权限:%d\n",pTemp->name,pTemp->password,pTemp->power);
		pTemp = pTemp->pNext;
	}
	printf("保存成功\n");
	fclose(p);
	p = NULL;
}
