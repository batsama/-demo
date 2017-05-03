#ifndef LOGUP_H
#define LOGUP_H
Code* loadCode(Code* pHead);  //读取注册信息
int loginIn(Code* pHead);//登录程序
int lookupPassword(Code* pHead, char* name, char * password); //查询指定账户密码是否正确 
#endif