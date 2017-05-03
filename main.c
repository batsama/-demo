#include"all.h"
int main(void)
{
	P_Head = loadCode(P_Head);
	/*loading();//加载界面
	//读取成绩信息
	Nav_menu();//显示登陆菜单
	system("color F9");*/
	supervisSystem(3);
	P_Head=FreeAc(P_Head);
	return 0;
}