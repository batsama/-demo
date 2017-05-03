#ifndef ACCOUN_T
#define ACCOUN_T
void AC_Printf(Code* pHead);//打印所有账户信息 
Code*findCode(Code* pHead, char* name);//查找指定用户信息
void AC_munu(void);//账户管理菜单
Code* rewiteCode(Code* pHead);//修改指定用户信息
Code* AC_del(Code* pHead);//删除指定账户信息
Code* AC_Free(Code* pHead);//清空账户信息
Code* FreeAc(Code* pHead);//清空链表
#endif