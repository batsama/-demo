#include"all.h" 
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