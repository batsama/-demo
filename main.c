#include"all.h"
int main(void)
{
	P_Head = loadCode(P_Head);
	/*loading();//���ؽ���
	//��ȡ�ɼ���Ϣ
	Nav_menu();//��ʾ��½�˵�
	system("color F9");*/
	supervisSystem(3);
	P_Head=FreeAc(P_Head);
	return 0;
}