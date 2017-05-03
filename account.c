#include"all.h"
void AC_munu(void)//账户管理菜单
{
	int flag;
	int l = 9;
	hicehandle(0);
	while (1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.查看所有账户信息");
		Gotoxy(53, 10);
		printf("2.修改指定账户信息");
		Gotoxy(53, 11);
		printf("3.删除指定账户信息");
		Gotoxy(53, 12);
		printf("4.清空所有账户信息"); 
		Gotoxy(53, 13);
		printf("5.返回上一层");
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
void AC_Printf(Code* pHead)//打印所有账户信息
{
	Code* pTemp = NULL;
	int num = 0;//记录账号个数
	int i,j,flag=0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("信息为空");
		_getch();
		return ;
	}
	pTemp = pHead;
	for (i = 1,j=1,pTemp=pHead;pTemp!=NULL; i++,j++,pTemp=pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:账号:%-10s 密码:%-10s 权限:%d", i, pTemp->name,pTemp->password,pTemp->power);
		if (j%25==0)
		{
			Gotoxy(90, 25);
			printf("回车下一页");
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
	printf("回车退出");
	while (1)
	{
		flag = _getch();
		if (flag == 13)
		{
			return;
		}
	}
}
Code*findCode(Code* pHead, char* name)//查找指定用户信息
{
	Code* pTemp=NULL;
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("信息为空");
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
		printf("已经查询到");
		Gotoxy(40, 12);
		printf("账号 : %-10s 密码 : %-10s 权限 : %d", pTemp->name, pTemp->password, pTemp->power);
		_getch();
	}
	return pTemp;
}
Code* rewiteCode(Code* pHead)//修改指定账户的信息
{
	int flag,flog1=1,flog2=1,power=0,l=9;
	char ch;
	char name[20];
	char newName[20];//新名字
	char newPassword[20];//新密码
	char psw[20];//重复输入密码
	Code* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("账户信息为空");
		_getch();
		return pHead;
	}
	drawnav();
	Gotoxy(45, 10);
	printf("请输入账户账号:");
	hicehandle(1);
	scanf_s("%s", name, 20);
	pTemp = findCode(pHead, name);
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("查无此人");
		_getch();
		return pHead;//查无此人
	}
	while(1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.修改账户名");
		Gotoxy(53, 10);
		printf("2.修改账户密码");
		Gotoxy(53, 11);
		printf("3.修改账户权限");
		Gotoxy(53, 12);
		printf("4.返回上一层");
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
					printf("请输入新账号:          \b\b\b\b\b\b\b\b\b\b");
					hicehandle(1);
					scanf_s("%s", newName, 20);
					hicehandle(0);
					if (lookup(pHead,newName) == 0) //判断是否存在用户 
					{
						flog1 = 0;
						Gotoxy(70, 4);
						printf("该账号可以使用!            ");
					}
					else
					{
						Gotoxy(70, 4);
						printf("该账号已经注册过,请重新输入");
						Sleep(1000);
						continue;
					}
				}
				strcpy(pTemp->name, newName);
				drawnav();
				Gotoxy(52, 10);
				printf("修改成功！");
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
					printf("请输入新密码:          \b\b\b\b\b\b\b\b\b\b");
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
						newPassword[p++]= ch;//保存密码 
					}
					newPassword[p] = '\0';//字符串结尾
					p = 0;
					Gotoxy(43, 6);
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
					hicehandle(0); 
					if (strcmp(newPassword, psw) == 0)
					{
						flog2 = 0;
					}
					else
					{
						Gotoxy(70, 6);
						printf("二次密码输入错误,请重新输入");
						Sleep(500);
					}
			   }
				strcpy(pTemp->password, newPassword);
				drawnav();
				Gotoxy(52, 10);

				printf("修改成功！");
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
Code* AC_del(Code* pHead)//删除指定账户信息
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
		printf("账户信息为空");
		_getch();
		return pHead;
	}
	drawnav();
	Gotoxy(45, 10);
	printf("请输入账户账号:");
	hicehandle(1);
	scanf_s("%s", name, 20);
	hicehandle(0);
	pTemp = findCode(pHead, name);
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("查无此人");
		_getch();
		return pHead;//查无此人
	}
	if (pTemp != NULL)
	{
		while (1)
		{
			drawnav();
			Gotoxy(47, 8);
			printf("是否要删除此账号?");
			Gotoxy(53, 9);
			printf("1.是");
			Gotoxy(53, 10);
			printf("2.否");
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
						pHead = pHead->pNext;//头后移
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
								printf("删除成功");
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
Code* AC_Free(Code* pHead)//清空账户信息
{
	int flag;
	int l = 9;
	Code* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("账户信息为空");
		_getch();
		return pHead;
	}
	while (1)
	{
		drawnav();
		Gotoxy(47, 8);
		printf("是否要清空所有账户信息?");
		Gotoxy(53, 9);
		printf("1.是");
		Gotoxy(53, 10);
		printf("2.否");
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
				printf("清空成功");
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
Code* FreeAc(Code* pHead)//清空链表
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