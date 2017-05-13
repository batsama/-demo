#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define LODING_H
#define LEN 25//定义进度条长度
#define MENU_H
#define Up 0x48
#define Down 0x50
#define Left 0x4b 
#define Right 0x4d
#define Stu 1;
#define Tea 2;
#define adm 3;
int p;//声明权限，初始为0
typedef struct CODE
{
	char name[21];
	char password[21];
	struct CODE *pNext;
	int power; //权限
}Code;//声明注册信息节点
Code*  P_Head;
typedef struct Data
{
	char strStuName[21];
	char strStuNum[21];
	int strStuSorce;
}Data; //构造Data数据结构体
typedef struct NODE
{
	Data data;
	struct NODE* pFont;
	struct NODE* pNext;
}Node;   //构造数据节点
Node* S_Head;//建立数据链表头
Code* loadCode(Code* pHead);  //读取注册信息
int loginIn(Code* pHead);//登录程序
int lookupPassword(Code* pHead, char* name, char * password); //查询指定账户密码是否正确 
Code* P_Ac; //登陆账号信息
Node* loadData(Node* pHead);//从文件中读取学生的信息
void print(Node* pHead);//打印全部内容
void saveData(Node* pHead);//保存学生信息到文件中
Node* freeLink(Node* pHead); //清空学生信息
Node* FindStu(Node* pHead);//查找指定学生的信息
int strNum(char* str); //判断学号是否正确
Node* rewriteStu(Node*pHead);//修改指定学生的信息
Node* addStu(Node*pHead);//添加学生信息
int lookupStu(Node* pHead, char* name); //判断是否存在学生
Node* delStu(Node* pHead);//输出指定学生信息
Node* sortStu(Node* pHead);//冒泡排序 由小到大
void AC_Printf(Code* pHead);//打印所有账户信息 
Code*findCode(Code* pHead, char* name);//查找指定用户信息
void AC_munu(void);//账户管理菜单
Code* rewiteCode(Code* pHead);//修改指定用户信息
Code* AC_del(Code* pHead);//删除指定账户信息
Code* AC_Free(Code* pHead);//清空账户信息
Code* FreeAc(Code* pHead);//清空链表
void fetchstr(char* str, int num);//读取字符串函数
void fetchpas(char* str, int num);//读取密码函数
Code* addCode(Code* pHead, int power); //增加一个注册信息
void saveCode(Code* pHead); //保存注册信息
int lookup(Code* pHead, char* name); //判断是否存在用户
void Nav_menu(void);//登录注册页面
void Loginin_menu(void);//登陆界面
void supervisSystem(int power);//管理系统界面
void Gotoxy(int x, int y);//光标移动
void Drawbox(void);//画出方框
void loading(void);//加载进度条函数
void hicehandle(int i);//隐藏光标信息
void drawnav(void);//画出外边框
void powerLoading(int power);//进入成绩管理系统加载进度条函数 
int main(void)
{
	system("color F9");
	loading(); 
	Nav_menu();
	return 0;
}
Code* loadCode(Code* pHead)  //读取注册信息
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
				P_Ac = pTemp;  //记住登陆账号的信息
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
		printf("账号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		fetchstr(name, 21);
		Gotoxy(57, 6);
		printf("                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		fetchpas(password, 19);
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
		hicehandle(0);
		while (1)
		{   
			Gotoxy(46, 17);
			printf("  \b");
			Gotoxy(46, 18);
			printf("  \b");
			Gotoxy(48, 16);
			printf("请选择:");
			Gotoxy(48, 17);
			printf("1,重新登录");
			Gotoxy(48, 18);
			printf("2.返回");
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
void AC_munu(void)//账户管理菜单
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
			printf("1.查看账号信息");
			Gotoxy(53, 10);
			printf("2.修改账号信息");
			Gotoxy(53, 11);
			printf("3.返回上一层");
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
					printf("账号:%-10s 密码:%-10s 权限:%d", P_Ac->name, P_Ac->password, P_Ac->power);
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
	int flag, flog1 = 1, flog2 = 1, power = 0, l = 9;
	char ch;
	char name[21];
	char newName[21];//新名字
	char newPassword[21];//新密码
	char psw[21];//重复输入密码
	Code* pTemp = NULL;
	if (P_Ac->power == 3)
	{
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
		fetchstr(name, 20);
		pTemp = findCode(pHead, name);
		if (pTemp == NULL)
		{
			drawnav();
			Gotoxy(52, 12);
			printf("查无此人");
			_getch();
			return pHead;//查无此人
		}
		while (1)
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
						printf("请输入新账号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						hicehandle(1);
						fetchstr(newName, 20);
						hicehandle(0);
						if (lookup(pHead, newName) == 0) //判断是否存在用户 
						{
							flog1 = 0;
							Gotoxy(20, 4);
							printf("该账号可以使用!            ");
						}
						else
						{
							Gotoxy(20, 4);
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
						printf("请输入新密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchstr(newPassword, 19);
						Gotoxy(43, 6);
						printf("请再次输入密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchstr(psw, 19);
						hicehandle(0);
						if (strcmp(newPassword, psw) == 0)
						{
							flog2 = 0;
						}
						else
						{
							Gotoxy(20, 6);
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
					while (1)
					{
						l = 11;
						drawnav();
						Gotoxy(52, 10);
						printf("请选择权限");
						Gotoxy(52, 11);
						printf("学生");
						Gotoxy(52, 12);
						printf("老师");
						Gotoxy(52, 13);
						printf("管理员");
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
								printf("修改成功!");
								_getch();
								return pHead;
							}
							if (l == 12)
							{
								pTemp->power = 2;
								drawnav();
								Gotoxy(52, 10);
								printf("修改成功!");
								_getch();
								return pHead;
							}
							if (l == 13)
							{
								pTemp->power = 3;
								drawnav();
								Gotoxy(52, 10);
								printf("修改成功!");
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
			printf("1.修改账户名");
			Gotoxy(53, 10);
			printf("2.修改账户密码");
			Gotoxy(53, 11);
			printf("3.返回上一层");
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
						printf("请输入新账号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						hicehandle(1);
						fetchpas(newName, 20);
						hicehandle(0);
						if (lookup(pHead, newName) == 0) //判断是否存在用户 
						{
							flog1 = 0;
							Gotoxy(20, 4);
							printf("该账号可以使用!            ");
						}
						else
						{
							Gotoxy(20, 4);
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
				}
				if (l == 10)
				{
					while (flog2)
					{
						drawnav();
						hicehandle(1);
						Gotoxy(45, 4);
						printf("请输入新密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchpas(newPassword, 19);
						Gotoxy(43, 6);
						printf("请再次输入密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						fetchpas(psw, 19);
						hicehandle(0);
						if (strcmp(newPassword, psw) == 0)
						{
							flog2 = 0;
						}
						else
						{
							Gotoxy(20, 6);
							printf("二次密码输入错误,请重新输入");
							Sleep(500);
						}
					}
					strcpy(pTemp->password, newPassword);
					drawnav();
					Gotoxy(52, 10);

					printf("修改成功！");
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
Code* AC_del(Code* pHead)//删除指定账户信息
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
		printf("账户信息为空");
		_getch();
		return pHead;
	}
	drawnav();
	Gotoxy(45, 10);
	printf("请输入账户账号:");
	hicehandle(1);
	fetchstr(name, 20);
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
void fetchstr(char* str, int num)//读取字符串函数
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
void fetchpas(char* str, int num)//读取密码函数
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
Node* loadData(Node* pHead)//从文件中读取学生的信息
{
	FILE *p = fopen("dat.txt", "r+");
	Node *pTemp = NULL;
	Node *pNew = NULL;
	char strname[21];
	char strnum[21];
	int sorce;
	if (p != NULL)
	{
		while (fscanf(p, "姓名:%s 学号:%s 成绩:%d\n", strname, strnum, &sorce) == 3)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("内存申请失败\n");
				return NULL;
			}
			strcpy(pNew->data.strStuName, strname);
			strcpy(pNew->data.strStuNum, strnum);
			pNew->data.strStuSorce = sorce;   //初始化
			if (pHead == NULL)//若头为空 第一个节点为头
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
		printf("文件打开失败\n");
		return NULL;
	}
	return pHead;
}
void print(Node* pHead)  //打印全部内容
{
	Node *pTemp = pHead;
	int num = 0;//记录学生的个数
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表中无数据\n");
		return;
	}
	int i, j, flag = 0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("信息为空");
		_getch();
		return;
	}
	pTemp = pHead;
	for (i = 1, j = 1, pTemp = pHead; pTemp != NULL; i++, j++, pTemp = pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:学号:%10s 姓名:%6s 成绩%3d ", i,pTemp->data.strStuNum,pTemp->data.strStuName,pTemp->data.strStuSorce);
		if (j % 25 == 0)
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
void saveData(Node* pHead)//保存学生信息到文件中
{
	FILE *p = NULL;
	Node *pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("学生信息为空\n");
		return;
	}
	p = fopen("dat.txt", "w+");
	if (p != NULL)
	{
		pTemp = pHead;
		while (pTemp != NULL)
		{
			fprintf(p, "姓名:%s 学号:%s 成绩:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
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
			printf("文件关闭失败\n");
			return;
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("文件打开失败\n");
		return;
	}
}
Node* freeLink(Node* pHead) //清空学生信息
{
	Node* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表为空\n");
		return NULL;
	}
	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
		/*pTemp->pFont = NULL;
		pTemp->pNext = NULL; */
		//周报有的写了
		pTemp = NULL;
	}
	return pHead;
}
Node* FindStu(Node* pHead)//查找指定学生的信息
{
	Node* pTemp = NULL;
	char str[21];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表中无数据\n");
		return NULL;
	}
	while (1)
	{   
		drawnav();
		Gotoxy(45,10);
		hicehandle(1);
		printf("请输入要查找的学生的学号:");
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
			printf("学号输入错误,请重新输入");
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
		printf("查无此人!");
		_getch();
		return NULL;
	}
	drawnav();
	Gotoxy(53, 10);
	printf("已查找到这个学生!");
	Sleep(500);
	drawnav();
	Gotoxy(35, 10);
	printf("学生姓名:%s 学生学号:%s 学生成绩:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
	_getch();
	return pTemp;
}
int strNum(char* str) //判断学号是否正确
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
		printf("链表中无数据\n");
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
				printf("请选择要修改的信息");
				Gotoxy(52, 10);
				printf("1.学生姓名");
				Gotoxy(52, 11);
				printf("2.学生学号");
				Gotoxy(52, 12);
				printf("3.学生成绩");
				Gotoxy(52, 13);
				printf("4.返回上一层");
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
						printf("请输入修改后的姓名:");
						hicehandle(1);
						fetchstr(pTemp->data.strStuName, 20);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
						Sleep(500);
					}
					if (l == 11)
					{
						while (1)
						{
							drawnav();
							Gotoxy(48, 10);
							printf("请输入修改后的学号:");
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
									printf("学号已存在请重新输入！");
									Gotoxy(48, 10);
									printf("请输入修改后的学号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
									fetchstr(stuNum, 20);
								}
							}
							hicehandle(0);
							if (strNum(stuNum) == 1)
							{
								break;
							}
							Gotoxy(52, 12);
							printf("请输入正确学号！");
							Sleep(500);
						}
						strcpy(pTemp->data.strStuNum,stuNum);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
						Sleep(500);
					}
					if (l == 12)
					{
						drawnav();
						Gotoxy(52, 10);
						printf("请输入修改后的成绩:");
						hicehandle(1);
						scanf("%d", &pTemp->data.strStuSorce);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
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
	printf("查无此人");
	return pHead;
}
Node* addStu(Node*pHead)//添加学生信息
{
	int n = 0;   //要添加学生的个数
	int flogs = 1;
	int l = 11;
	int i;
	int flag;
	Node* pNew = NULL;
	Node* pStu = NULL;
	Node* pFoot = NULL;
	drawnav();
	Gotoxy(48, 10);
	printf("请输入要添加学生的个数:");
	Gotoxy(48, 12);
	printf("注：若只添加一个需要指定位置");
	hicehandle(1);
	Gotoxy(72, 10);
	scanf("%d", &n);
	hicehandle(0);
	if (n == 1)  //插入一个学生
	{
		if (pHead == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("链表为空\n");
			return NULL;
		}
		while (pStu == NULL)
		{
			printf("未找到插入位置 请重新查找\n");
			pStu = FindStu(pHead);
		}
		pNew = (Node*)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("创建节点失败\n");
			return NULL;
		}
		while (flogs)
		{   
			drawnav();
			Gotoxy(48, 10);
			printf("请输入要插入学生的信息:");
			Gotoxy(50, 12);
			printf("学生姓名:");
			Gotoxy(50, 13);
			printf("学生学号:");
			Gotoxy(50, 14);
			printf("学生成绩:");
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
					printf("学号已存在请重新输入！");
					Gotoxy(50, 13);
					printf("学生学号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
				printf("您输入的信息有误,请重新输入\n");
				_getch();
			}
		}
		while (1)
		{
			drawnav();
			Gotoxy(48, 10);
			printf("请选择要插入的位置\n");
			Gotoxy(48, 11);
			printf("前");
			Gotoxy(48, 12);
			printf("后");
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
				if (l == 11)   //插入指定位置前
				{
					if (pStu == pHead)
					{
						pHead->pFont = pNew;
						pNew->pFont = NULL;
						pNew->pNext = pHead;
						pHead = pHead->pFont;
						drawnav();
						Gotoxy(52, 10);
						printf("添加成功！");
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
						printf("添加成功！");
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
						printf("添加成功！");
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
						printf("添加成功！");
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
				printf("创建节点失败\n");
				return pHead;
			}
			while (1)
			{
				drawnav();
				Gotoxy(48, 10);
				printf("请输入第%d个要插入学生的信息:",i+1);
				Gotoxy(50, 12);
				printf("学生姓名:");
				Gotoxy(50, 13);
				printf("学生学号:");
				Gotoxy(50, 14);
				printf("学生成绩:");
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
						printf("学号已存在请重新输入！");
						Gotoxy(50, 13);
						printf("学生学号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
					printf("您输入的信息有误,请重新输入\n");
				}
			}
			while (pFoot->pNext != NULL&&pHead != NULL)
			{
				pFoot = pFoot->pNext;  //遍历找尾
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
		printf("添加成功！");
		_getch();
		return pHead;
	}
	return pHead;
}
int lookupStu(Node* pHead, char* Num) //判断是否存在学生
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
Node* delStu(Node* pHead)//输出指定学生信息
{
	Node* pTemp;
	int l = 10;
	int flag;
	pTemp = FindStu(pHead);
	while (1)
	{

		drawnav();
		Gotoxy(52, 9);
		printf("是否要删除?");
		Gotoxy(52, 10);
		printf("1.是");
		Gotoxy(52, 11);
		printf("2.否");
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
				printf("删除成功");
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
Node* sortStu(Node* pHead)//冒泡排序 由小到大
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
		printf("学生信息为空\n");
		return NULL;
	}
	if (pNew == NULL)
	{
		drawnav();
		Gotoxy(52,10);
		printf("排序失败！");
		return pHead;
	}
	pHead->pFont = pNew;
	pNew->pNext = pHead;
	pNew->pFont = NULL;
	pHead = pHead->pFont;
	pTemp = pHead->pNext;
	while (pTemp != NULL)
	{
		pTemp = pTemp->pNext;//temp后移
		n++;
	}
	for (i = 1; i<n; i++)
	{
		for (pTemp = pHead->pNext, j = 1; j<n; j++)
		{
			if (pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //冒泡排序
			{
				if (pTemp->pNext->pNext == NULL)  //若小后为空
				{
					pTemp->pFont->pNext = pTemp->pNext; //大的前驱的后驱指向小的
					pTemp->pNext->pNext = pTemp; //小的后驱指向大的
					pTemp->pNext->pFont = pTemp->pFont; //小的前驱指向大的前驱
					pTemp->pFont = pTemp->pNext; //大的前驱指向小的
					pTemp->pNext = NULL;  //大的后驱指向NULL
				}
				else
				{
					(pTemp->pFont)->pNext = pTemp->pNext;               //大的前驱的后驱指向小的
					((pTemp->pNext)->pNext)->pFont = pTemp;             //小的后驱的前驱指向大的
					pTemp->pNext = ((pTemp->pFont)->pNext)->pNext;     //大的后驱指向小的后驱					 
					((pTemp->pFont)->pNext)->pNext = pTemp;            //小的后驱指向大的
					((pTemp->pFont)->pNext)->pFont = pTemp->pFont;    //小的前驱指向大前
					pTemp->pFont = ((pTemp->pFont)->pNext);            //大的前驱指向小的
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
	printf("排序成功!");
	return pHead;
}
void Nav_menu(void)//登录注册页面
{
	int flag;
	int l = 9;
	extern int p;
	hicehandle(0);
	while (1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.注册");
		Gotoxy(53, 10);
		printf("2.登录");
		Gotoxy(53, 11);
		printf("3.退出");
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
				p = loginIn(P_Head);//权限变更
				hicehandle(0);
				system("cls");
				if (p > 0)
				{
					powerLoading(p);//执行加载界面函数
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
	void Loginin_menu(void)//注册页面
	{
		int flag;
		int l = 9;
		hicehandle(0);
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.学生注册");
			Gotoxy(53, 10);
			printf("2.教师注册");
			Gotoxy(53, 11);
			printf("3.管理员注册");
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
					P_Head = addCode(P_Head, 1);
					saveCode(P_Head);
					Nav_menu();
				}
				if (l == 10)
				{
					if (p > 1) //权限在学生端之上才能注册
					{
						P_Head = addCode(P_Head, 2);
						saveCode(P_Head);
					}
					else
					{
						drawnav();
						Gotoxy(48, 10);
						printf("权限不足，请先登录");
						_getch();
					}
					Nav_menu();
				}
				if (l == 11)   //权限在老师端之上才能注册
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
						printf("权限不足，请先登录");
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
	void supervisSystem(int power)//管理系统界面
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
				   printf("管理系统学生端");
				   Gotoxy(52, 6);
				   printf("1.查询学生的信息");
				   Gotoxy(52, 7);
				   printf("2.打印全部的信息");
				   Gotoxy(52, 8);
				   printf("3.排序学生的信息");
				   Gotoxy(52, 9);
				   printf("4.修改账号信息");
				   Gotoxy(52, 10);
				   printf("5.退出登陆");
				   Gotoxy(52, 11);
				   printf("6.退出程序");
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
						   printf("谢谢使用！");
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
				printf("管理系统教师端");
				Gotoxy(52, 6);
				printf("1.查询指定学生的信息");
				Gotoxy(52, 7);
				printf("2.打印全部学生的信息");
				Gotoxy(52, 8);
				printf("3.删除指定学生的信息");
				Gotoxy(52, 9);
				printf("4.修改指定学生的信息");
				Gotoxy(52, 10);
				printf("5.添加一些学生的信息");
				Gotoxy(52, 11);
				printf("6.排序学生的信息");
				Gotoxy(52, 12);
				printf("7.教师账号管理");
				Gotoxy(52, 13);
				printf("8.退出登陆");
				Gotoxy(52, 14);
				printf("9.退出程序");
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
						printf("谢谢使用！");
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
		case 3: //管理端。。
			while (1)
			{
				drawnav();
				Gotoxy(54, 4);
				printf("管理系统管理端");
				Gotoxy(52, 6);
				printf("1.查询指定学生的信息");
				Gotoxy(52, 7);
				printf("2.打印全部学生的信息");
				Gotoxy(52, 8);
				printf("3.删除指定学生的信息");
				Gotoxy(52, 9);
				printf("4.修改指定学生的信息");
				Gotoxy(52, 10);
				printf("5.添加一些学生的信息");
				Gotoxy(52, 11);
				printf("6.排序学生的信息");
				Gotoxy(52, 12);
				printf("7.管理系统账号");
				Gotoxy(52, 13);
				printf("8.退出登陆");
				Gotoxy(52, 14);
				printf("9.退出程序");
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
						printf("谢谢使用！");
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
     	printf("账号:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(52, 6);
		printf("密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		Gotoxy(57, 4);
		fetchstr(pNew->name, 20);
		if (lookup(pHead, pNew->name) == 0) //判断是否存在用户 
		{
			flog1 = 0;
			Gotoxy(20, 4);
			printf("该账号可以使用!            ");
		}
		else
		{
			Gotoxy(20, 4);
			printf("该账号已经注册过,请重新输入");
			continue;
		}
		while (flog2)
		{
			Gotoxy(58, 6);
			printf("                   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			fetchpas(pNew->password, 19);
			Gotoxy(42, 8);
			printf("请再次输入密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			fetchpas(psw, 19);
			if (strcmp(pNew->password, psw) == 0)
			{
				flog2 = 0;
			}
			else
			{
				Gotoxy(10, 8);
				printf("二次密码输入错误,请重新输入");
				Sleep(500);
				Gotoxy(42, 8);
				printf("请再次输入密码:                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			}                                      
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
	fclose(p);
	p = NULL;
}
void hicehandle(int i)//隐藏光标信息
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出设备句柄
	CONSOLE_CURSOR_INFO cci;//定义光标信息结构体
	GetConsoleCursorInfo(handle_out, &cci);//获取当前光标信息
	if (i == 0)
	{
		cci.bVisible = 0;//设置光标为不可见
	}
	else
	{
		cci.bVisible = 1;
	}
	SetConsoleCursorInfo(handle_out, &cci);
	return;
}
void Gotoxy(int x, int y)  //光标移动
{
	HANDLE hout;//定义句柄变量
	COORD coord;//定义结构体
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出句柄
	SetConsoleCursorPosition(hout, coord);//移动光标
	return;
}
void Drawbox(void) //画出方框
{
	printf("\t\t\t\t ╔═════════════════════════╗");
	putchar('\n');
	printf("\t\t\t\t ║                                                  ║");
	putchar('\n');
	printf("\t\t\t\t ╚═════════════════════════╝");
	return;
}
void loading(void)//加载进度条函数
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//画方框
	//画进度条
	Gotoxy(52, 5);
	printf(" 成绩管理系统\n");
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("█");
		Gotoxy(21, 4);
		printf("\t\t\t\t     已完成  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(55, 10);
	printf("加载完成\n");
	Gotoxy(55, 13);
	printf("进入系统\n");
	P_Head = loadCode(P_Head);
	S_Head = loadData(S_Head);
	Sleep(1000);
	system("cls");
	return;
}
void drawnav(void)//画出外边框
{
	int i;
	system("cls");//清屏
	Gotoxy(0, 0);
	printf("┌");//画左上角
	for (i = 0; i < 58; i++)
	{
		printf("─");//画水平线
	}
	printf("┐"); //画右上角
	for (i = 1; i <= 26; i++)
	{
		Gotoxy(0, i);
		printf("│");//画垂直线
		Gotoxy(118, i);
		printf("│");
	}
	printf("└");//画左下角
	for (i = 0; i < 58; i++)
	{
		printf("─");//画水平线
	}
	printf("┘"); //画右下角
	system("color F9");
	Gotoxy(29, 14);
	return;
}
void powerLoading(int power)//进入成绩管理系统加载进度条函数 
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//画方框
	//画进度条
	Gotoxy(48, 5);
	switch (power)
	{
	case 1 : printf(" 成绩管理系统:学生端\n");
		break;
	case 2 : printf(" 成绩管理系统:教师端\n");
		break;
	case 3 : printf(" 成绩管理系统:管理端\n");
		break;
	}
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("█");
		Gotoxy(21, 4);
		printf("\t\t\t\t     已完成  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(52, 10);
	printf("加载完成\n");
	Gotoxy(52, 13);
	printf("进入管理系统\n");
	Sleep(1000);
	system("cls");
	return;
}
