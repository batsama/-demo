#include"all.h"
Code* loadCode(Code* pHead)  //读取注册信息
{
	FILE * p = NULL;
	Code *pTemp = NULL;
	Code* pNew = NULL;
	char name[20];
	char password[20];
	int power;
	p = fopen("register.txt", "r+ ");
	if (p == NULL)
	{
		system("cls");
		printf("文件打开失败\n");
		exit(0);
	}
	while (fscanf(p, "账号:%s 密码:%s 权限:%d\n", name, password, &power) == 3)
	{
		pNew = (Code*)malloc(sizeof(Code));
		if (pNew == NULL)
		{
			system("cls");
			printf("内存申请失败\n");
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
int lookupPassword(Code* pHead, char* name, char * password) //查询指定账户密码是否正并且判断权限
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
int loginIn(Code* pHead) //登录程序
{
	Code* pTemp = NULL;
	char name[20];
	char password[20];
	char ch;
	int p=0, flog = 1, n;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("信息为空");
		_getch();
		return 0;
	}
	drawnav();
	hicehandle(1);
	while (1)
	{
		Gotoxy(52, 1);
		printf("请输入账号信息:\n");
		Gotoxy(52, 4);
		printf("账号:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("密码:          \b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		scanf_s("%s", name,20);
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
			password[p++] = ch;//保存密码 
		}
		password[p] = '\0';//字符串结尾 
		p = 0;
		if (lookupPassword(pHead, name, password) > 0)
		{
			Gotoxy(52,10);
			printf("登录成功!");
			hicehandle(0);
			Sleep(1000);
			return lookupPassword(pHead, name, password);
		}
		else
			flog = 1;
		Gotoxy(48, 15);
		printf("账号或密码错误!\n");
		Gotoxy(48, 16);
		printf("1.重试 2.退出登录\n");
		while (flog)
		{
			Gotoxy(48, 17);
			printf(" \b");
			if (scanf("%d", &n) != 1)
			{
				continue;
			}
			switch (n)
			{
			case 1:
				flog = 0;
				break;
			case 2:
				flog = 0;
				return 0;
				break;
			default:
				Gotoxy(68,16);
				printf("请输入正确指令\n");
			}
		}
		drawnav();
	}
}