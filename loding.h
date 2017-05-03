#ifndef LODING_H
#define LODING_H
#define LEN 25//定义进度条长度
void Gotoxy(int x, int y);//光标移动
void Drawbox(void);//画出方框
void loading(void);//加载进度条函数
void hicehandle(int i);//隐藏光标信息
void drawnav(void);//画出外边框
void powerLoading(int power);//进入成绩管理系统加载进度条函数 
#endif