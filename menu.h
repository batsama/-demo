#ifndef MENU_H
#define MENU_H
#define Up 0x48
#define Down 0x50
#define Left 0x4b 
#define Right 0x4d
#define Stu 1;
#define Tea 2;
#define adm 3;
void Nav_menu(void);//登录注册页面
void Loginin_menu(void);//登陆界面
void supervisSystem(int power);//管理系统界面
int p;//声明权限，初始为0
#endif