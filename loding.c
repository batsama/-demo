#include"all.h" 
void hicehandle(int i)//���ع����Ϣ
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼����豸���
	CONSOLE_CURSOR_INFO cci;//��������Ϣ�ṹ��
	GetConsoleCursorInfo(handle_out, &cci);//��ȡ��ǰ�����Ϣ
	if (i == 0)
	{
		cci.bVisible = 0;//���ù��Ϊ���ɼ�
	}
	else
	{
		cci.bVisible = 1;
	}
	SetConsoleCursorInfo(handle_out, &cci);
	return;
}
void Gotoxy(int x, int y)  //����ƶ�
{
	HANDLE hout;//����������
	COORD coord;//����ṹ��
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼������
	SetConsoleCursorPosition(hout, coord);//�ƶ����
	return;
}
void Drawbox(void) //��������
{
	printf("\t\t\t\t �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	putchar('\n');
	printf("\t\t\t\t �U                                                  �U");
	putchar('\n');
	printf("\t\t\t\t �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	return;
}
void loading(void)//���ؽ���������
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//������
	//��������
	Gotoxy(52, 5);
	printf(" �ɼ�����ϵͳ\n");
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("��");
		Gotoxy(21, 4);
		printf("\t\t\t\t     �����  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(55, 10);
	printf("�������\n");
	Gotoxy(55, 13);
	printf("����ϵͳ\n");
	P_Head = loadCode(P_Head);
	S_Head = loadData(S_Head);
	Sleep(1000);
	system("cls");
	return;
}
void drawnav(void)//������߿�
{
	int i;
	system("cls");//����
	Gotoxy(0, 0);
	printf("��");//�����Ͻ�
	for (i = 0; i < 58; i++)
	{
		printf("��");//��ˮƽ��
	}
	printf("��"); //�����Ͻ�
	for (i = 1; i <= 26; i++)
	{
		Gotoxy(0, i);
		printf("��");//����ֱ��
		Gotoxy(118, i);
		printf("��");
	}
	printf("��");//�����½�
	for (i = 0; i < 58; i++)
	{
		printf("��");//��ˮƽ��
	}
	printf("��"); //�����½�
	system("color F9");
	Gotoxy(29, 14);
	return;
}
void powerLoading(int power)//����ɼ�����ϵͳ���ؽ��������� 
{
	int len;
	system("color F9");
	hicehandle(0);
	Drawbox();//������
	//��������
	Gotoxy(48, 5);
	switch (power)
	{
	case 1 : printf(" �ɼ�����ϵͳ:ѧ����\n");
		break;
	case 2 : printf(" �ɼ�����ϵͳ:��ʦ��\n");
		break;
	case 3 : printf(" �ɼ�����ϵͳ:�����\n");
		break;
	}
	for (len = 1; len <= LEN + 1; len++)
	{
		Gotoxy((2 * len) + 32, 1);
		printf("��");
		Gotoxy(21, 4);
		printf("\t\t\t\t     �����  %d%%", 4 * len - 4);
		Sleep(100);
	}
	Gotoxy(52, 10);
	printf("�������\n");
	Gotoxy(52, 13);
	printf("�������ϵͳ\n");
	Sleep(1000);
	system("cls");
	return;
}