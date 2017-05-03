#include"all.h"
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
					saveCode(P_Head);
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
		case 1: //学生端。。
			break;
		case 2: //教师端。。
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
				printf("7.管理系统账号管理");
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
						Sleep(2000);
						exit(0);
					}
				}
			}
			break;
		}
		return;
	}