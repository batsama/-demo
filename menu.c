#include"all.h"
void Nav_menu(void)//��¼ע��ҳ��
{
	int flag;
	int l = 9;
	extern int p;
	hicehandle(0);
	while (1)
	{
		drawnav();
		Gotoxy(53, 9);
		printf("1.ע��");
		Gotoxy(53, 10);
		printf("2.��¼");
		Gotoxy(53, 11);
		printf("3.�˳�");
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
				p = loginIn(P_Head);//Ȩ�ޱ��
				hicehandle(0);
				system("cls");
				if (p > 0)
				{
					powerLoading(p);//ִ�м��ؽ��溯��
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
	void Loginin_menu(void)//ע��ҳ��
	{
		int flag;
		int l = 9;
		hicehandle(0);
		while (1)
		{
			drawnav();
			Gotoxy(53, 9);
			printf("1.ѧ��ע��");
			Gotoxy(53, 10);
			printf("2.��ʦע��");
			Gotoxy(53, 11);
			printf("3.����Աע��");
			Gotoxy(53, 12);
			printf("4.������һ��");
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
					if (p > 1) //Ȩ����ѧ����֮�ϲ���ע��
					{
						P_Head = addCode(P_Head, 2);
						saveCode(P_Head);
					}
					else
					{
						drawnav();
						Gotoxy(48, 10);
						printf("Ȩ�޲��㣬���ȵ�¼");
						_getch();
					}
					Nav_menu();
				}
				if (l == 11)   //Ȩ������ʦ��֮�ϲ���ע��
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
						printf("Ȩ�޲��㣬���ȵ�¼");
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
	void supervisSystem(int power)//����ϵͳ����
	{
		int flag;
		int l=6;
		hicehandle(0);
		switch (power)
		{
		case 1: //ѧ���ˡ���
			break;
		case 2: //��ʦ�ˡ���
			break;
		case 3: //����ˡ���
			while (1)
			{
				drawnav();
				Gotoxy(54, 4);
				printf("����ϵͳ�����");
				Gotoxy(52, 6);
				printf("1.��ѯָ��ѧ������Ϣ");
				Gotoxy(52, 7);
				printf("2.��ӡȫ��ѧ������Ϣ");
				Gotoxy(52, 8);
				printf("3.ɾ��ָ��ѧ������Ϣ");
				Gotoxy(52, 9);
				printf("4.�޸�ָ��ѧ������Ϣ");
				Gotoxy(52, 10);
				printf("5.���һЩѧ������Ϣ");
				Gotoxy(52, 11);
				printf("6.����ѧ������Ϣ");
				Gotoxy(52, 12);
				printf("7.����ϵͳ�˺Ź���");
				Gotoxy(52, 13);
				printf("8.�˳���½");
				Gotoxy(52, 14);
				printf("9.�˳�����");
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
						printf("ллʹ�ã�");
						Sleep(2000);
						exit(0);
					}
				}
			}
			break;
		}
		return;
	}