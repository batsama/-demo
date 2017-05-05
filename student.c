#include"all.h"
Node* loadData(Node* pHead)//���ļ��ж�ȡѧ������Ϣ
{
	FILE *p = fopen("dat.txt", "r+");
	Node *pTemp = NULL;
	Node *pNew = NULL;
	char strname[20];
	char strnum[20];
	int sorce;
	if (p != NULL)
	{
		while (fscanf(p, "����:%s ѧ��:%s �ɼ�:%d\n", strname, strnum, &sorce) == 3)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("�ڴ�����ʧ��\n");
				return NULL;
			}
			strcpy(pNew->data.strStuName, strname);
			strcpy(pNew->data.strStuNum, strnum);
			pNew->data.strStuSorce = sorce;   //��ʼ��
			if (pHead == NULL)//��ͷΪ�� ��һ���ڵ�Ϊͷ
			{
				pHead = pNew;
				pHead->pFont = NULL;
				pHead->pNext = NULL;
				pTemp = pHead;
			}
			else
			{

				pNew->pNext = NULL;
				pNew->pFont = pTemp;
				pTemp->pNext = pNew;
				pTemp = pTemp->pNext;
			}
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	return pHead;
}
void print(Node* pHead)  //��ӡȫ������
{
	Node *pTemp = pHead;
	int num = 0;//��¼ѧ���ĸ���
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return;
	}
	int i, j, flag = 0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("��ϢΪ��");
		_getch();
		return;
	}
	pTemp = pHead;
	for (i = 1, j = 1, pTemp = pHead; pTemp != NULL; i++, j++, pTemp = pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:ѧ��:%10s ����:%6s �ɼ�%3d ", i,pTemp->data.strStuNum,pTemp->data.strStuName,pTemp->data.strStuSorce);
		if (j % 25 == 0)
		{
			Gotoxy(90, 25);
			printf("�س���һҳ");
			while (1)
			{
				flag = _getch();
				if (13 == flag)
				{
					_getch();
					drawnav();
					j = 0;
					break;
				}
			}
		}
	}
	Gotoxy(90, 25);
	printf("�س��˳�");
	while (1)
	{
		flag = _getch();
		if (flag == 13)
		{
			return;
		}
	}
}
void saveData(Node* pHead)//����ѧ����Ϣ���ļ���
{
	FILE *p = NULL;
	Node *pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("ѧ����ϢΪ��\n");
		return;
	}
	p = fopen("dat.txt", "w+");
	if (p != NULL)
	{
		pTemp = pHead;
		while (pTemp != NULL)
		{
			fprintf(p, "����:%s ѧ��:%s �ɼ�:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
			pTemp = pTemp->pNext;
		}
		if (fclose(p) == 0)
		{
			p = NULL;
			return;
		}
		else
		{
			drawnav();
			Gotoxy(52, 10);
			printf("�ļ��ر�ʧ��\n");
			return;
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("�ļ���ʧ��\n");
		return;
	}
}
Node* freeLink(Node* pHead) //���ѧ����Ϣ
{
	Node* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("����Ϊ��\n");
		return NULL;
	}
	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
		/*pTemp->pFont = NULL;
		pTemp->pNext = NULL; */
		//�ܱ��е�д��
		pTemp = NULL;
	}
	return pHead;
}
Node* FindStu(Node* pHead)//����ָ��ѧ������Ϣ
{
	Node* pTemp = NULL;
	char str[20];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return NULL;
	}
	while (1)
	{   
		drawnav();
		Gotoxy(45,10);
		hicehandle(1);
		printf("������Ҫ���ҵ�ѧ����ѧ��:");
		scanf("%s", str);
		hicehandle(0);
		if (strNum(str))
		{
			break;
		}
		else
		{
			drawnav();
			Gotoxy(53, 10);
			printf("ѧ���������,����������");
			_getch();
		}
	}
	pTemp = pHead;
	while (pTemp != NULL&&strcmp(pTemp->data.strStuNum, str))
	{
		pTemp = pTemp->pNext;
	}
	if (pTemp == NULL)
	{
		drawnav();
		Gotoxy(53, 10);
		printf("���޴���!");
		_getch();
		return NULL;
	}
	drawnav();
	Gotoxy(53, 10);
	printf("�Ѳ��ҵ����ѧ��!");
	Sleep(500);
	drawnav();
	Gotoxy(35, 10);
	printf("ѧ������:%s ѧ��ѧ��:%s ѧ���ɼ�:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
	_getch();
	return pTemp;
}
int strNum(char* str) //�ж�ѧ���Ƿ���ȷ
{
	int i, flog = 0;
	for (i = 0; i<strlen(str); i++)
	{
		if (str[i] >= '0'&&str[i] <= '9')
		{
			flog++;
		}
	}
	if (flog == strlen(str))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Node* rewriteStu(Node*pHead)
{
	Node* pTemp = NULL;
	Node* pStu = NULL;
	int l =10 , flag;
	char stuNum[20];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("������������\n");
		return NULL;
	}
	pStu = FindStu(pHead);
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (pTemp == pStu&&pStu!=NULL)
		{
			while (1)
			{
				drawnav();
				Gotoxy(52, 9);
				printf("��ѡ��Ҫ�޸ĵ���Ϣ");
				Gotoxy(52, 10);
				printf("1.ѧ������");
				Gotoxy(52, 11);
				printf("2.ѧ��ѧ��");
				Gotoxy(52, 12);
				printf("3.ѧ���ɼ�");
				Gotoxy(52, 13);
				printf("4.������һ��");
				Gotoxy(51, l);
				printf("%c", 16);
				flag = _getch();
				if (flag == Down)
				{
					l++;
					if (l == 14)
						l = 10;
				}
				if (flag == Up)
				{
					l--;
					if (l == 9)
						l = 13;
				}
				if (flag == 13)
				{
					if (l == 10)
					{
						drawnav();
						Gotoxy(48, 10);
						printf("�������޸ĺ������:");
						hicehandle(1);
						scanf("%s", pTemp->data.strStuName);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 11)
					{
						while (1)
						{
							drawnav();
							Gotoxy(48, 10);
							printf("�������޸ĺ��ѧ��:");
							hicehandle(1);
							scanf("%s", stuNum);
							while (1)
							{
								if (lookupStu(pHead, stuNum) == 1)
								{
									break;
								}
								else
								{

									Gotoxy(70, 10);
									printf("ѧ���Ѵ������������룡");
									Gotoxy(48, 10);
									printf("�������޸ĺ��ѧ��:        \b\b\b\b\b\b\b\b");
									scanf("%s", stuNum);
								}
								Gotoxy(99, 20);
								printf("haha");
							}
							hicehandle(0);
							if (strNum(stuNum) == 1)
							{
								break;
							}
							Gotoxy(52, 12);
							printf("��������ȷѧ�ţ�");
							Sleep(500);
						}
						strcpy(pTemp->data.strStuNum,stuNum);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 12)
					{
						drawnav();
						Gotoxy(52, 10);
						printf("�������޸ĺ�ĳɼ�:");
						hicehandle(1);
						scanf("%d", &pTemp->data.strStuSorce);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("�޸ĳɹ�!");
						Sleep(500);
					}
					if (l == 13)
					{
						return pHead;
					}
				}
			}
		}
		pTemp = pTemp->pNext;
	}
	
	drawnav();
	Gotoxy(52, 10);
	printf("���޴���");
	return pHead;
}
Node* addStu(Node*pHead)//���ѧ����Ϣ
{
	int n = 0;   //Ҫ���ѧ���ĸ���
	int flogs = 1;
	int l = 11;
	int i;
	int flag;
	Node* pNew = NULL;
	Node* pStu = NULL;
	Node* pFoot = NULL;
	drawnav();
	Gotoxy(48, 10);
	printf("������Ҫ���ѧ���ĸ���:");
	Gotoxy(48, 12);
	printf("ע����ֻ���һ����Ҫָ��λ��");
	hicehandle(1);
	Gotoxy(72, 10);
	scanf("%d", &n);
	hicehandle(0);
	if (n == 1)  //����һ��ѧ��
	{
		if (pHead == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("����Ϊ��\n");
			return NULL;
		}
		while (pStu == NULL)
		{
			printf("δ�ҵ�����λ�� �����²���\n");
			pStu = FindStu(pHead);
		}
		pNew = (Node*)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("�����ڵ�ʧ��\n");
			return NULL;
		}
		while (flogs)
		{   
			drawnav();
			Gotoxy(48, 10);
			printf("������Ҫ����ѧ������Ϣ:");
			Gotoxy(50, 12);
			printf("ѧ������:");
			Gotoxy(50, 13);
			printf("ѧ��ѧ��:");
			Gotoxy(50, 14);
			printf("ѧ���ɼ�:");
			Gotoxy(60, 12);
			hicehandle(1);
			scanf("%s", pNew->data.strStuName);
			Gotoxy(60, 13);
			scanf("%s", pNew->data.strStuNum);
			while (1)
			{ 
				if (lookupStu(pHead,pNew->data.strStuNum) == 1)
				{
					break;
				}
				else
				{
					Gotoxy(70, 13);
					printf("ѧ���Ѵ������������룡");
					Gotoxy(50, 13);
					printf("ѧ��ѧ��:         \b\b\b\b\b\b\b\b");
					scanf("%s", pNew->data.strStuNum);
				}
				
			}
			Gotoxy(60, 14);
			scanf("%d", &pNew->data.strStuSorce);
			hicehandle(0);
			if (pNew->data.strStuName != NULL&&strNum(pNew->data.strStuNum) && pNew->data.strStuSorce >= 0)
			{
				flogs = 0;
			}
			else
			{
				Gotoxy(60, 20);
				printf("���������Ϣ����,����������\n");
				_getch();
			}
		}
		while (1)
		{
			drawnav();
			Gotoxy(48, 10);
			printf("��ѡ��Ҫ�����λ��\n");
			Gotoxy(48, 11);
			printf("ǰ");
			Gotoxy(48, 12);
			printf("��");
			Gotoxy(47, l);
			printf("%c", 16);
			flag = _getch();
			if (flag == Down)
			{
				l++;
				if (l == 13)
					l = 11;
			}
			if (flag == Up)
			{
				l--;
				if (l == 10)
					l = 12;
			}
			if (flag == 13)
			{
				if (l == 11)   //����ָ��λ��ǰ
				{
					if (pStu == pHead)
					{
						pHead->pFont = pNew;
						pNew->pFont = NULL;
						pNew->pNext = pHead;
						pHead = pHead->pFont;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
					else
					{
						pNew->pNext = pStu;
						pNew->pFont = pStu->pFont;
						pStu->pFont->pNext = pNew;
						pStu->pFont = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
				}
				if (l == 12)
				{
					if (pStu->pNext == NULL)
					{
						pNew->pNext = NULL;
						pNew->pFont = pStu;
						pStu->pNext = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
					else
					{
						pNew->pNext = pStu->pNext;
						pNew->pFont = pStu;
						pStu->pNext->pFont = pNew;
						pStu->pNext = pNew;
						drawnav();
						Gotoxy(52, 10);
						printf("��ӳɹ���");
						_getch();
						return pHead;
					}
				}
			}
		}
	}
	pFoot = pHead;
	if (n > 1)
	{
		for (i = 0; i < n; i++)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("�����ڵ�ʧ��\n");
				return pHead;
			}
			while (1)
			{
				drawnav();
				Gotoxy(48, 10);
				printf("�������%d��Ҫ����ѧ������Ϣ:",i+1);
				Gotoxy(50, 12);
				printf("ѧ������:");
				Gotoxy(50, 13);
				printf("ѧ��ѧ��:");
				Gotoxy(50, 14);
				printf("ѧ���ɼ�:");
				Gotoxy(60, 12);
				hicehandle(1);
				scanf("%s", pNew->data.strStuName);
				Gotoxy(60, 13);
				scanf("%s", pNew->data.strStuNum);
				while (1)
				{
					if (lookupStu(pHead, pNew->data.strStuNum) == 1)
					{
						break;
					}
					else
					{
						Gotoxy(70, 13);
						printf("ѧ���Ѵ������������룡");
						Gotoxy(50, 13);
						printf("ѧ��ѧ��:         \b\b\b\b\b\b\b\b");
						scanf("%s", pNew->data.strStuNum);
					}

				}
				Gotoxy(60, 14);
				scanf("%d", &pNew->data.strStuSorce);
				hicehandle(0);
				if (pNew->data.strStuName != NULL&&strNum(pNew->data.strStuNum) && pNew->data.strStuSorce >= 0)
				{
					break;
				}
				else
				{
					Gotoxy(60, 20);
					printf("���������Ϣ����,����������\n");
				}
			}
			while (pFoot->pNext != NULL&&pHead != NULL)
			{
				pFoot = pFoot->pNext;  //������β
			}
			if (pHead == NULL)
			{
				pHead = pNew;
				pHead->pNext = NULL;
				pHead->pFont = NULL;
			}
			else
			{
				pNew->pNext = NULL;
				pNew->pFont = pFoot;
				pFoot->pNext = pNew;
			}
		}
		drawnav();
		Gotoxy(52, 10);
		printf("��ӳɹ���");
		_getch();
		return pHead;
	}
	return pHead;
}
int lookupStu(Node* pHead, char* Num) //�ж��Ƿ����ѧ��
{
    Node *pTemp = NULL;
	if (pHead == NULL)
	{
		return 1;
	}
	pTemp = pHead;
	while (pTemp != NULL)
	{
		if (strcmp(Num, pTemp->data.strStuNum) == 0)
		{
			return 0;
		}
		pTemp = pTemp->pNext;
	}
	return 1;
}
Node* delStu(Node* pHead)//���ָ��ѧ����Ϣ
{
	Node* pTemp;
	int l = 10;
	int flag;
	pTemp = FindStu(pHead);
	while (1)
	{

		drawnav();
		Gotoxy(52, 9);
		printf("�Ƿ�Ҫɾ��?");
		Gotoxy(52, 10);
		printf("1.��");
		Gotoxy(52, 11);
		printf("2.��");
		Gotoxy(51, l);
		printf("%c", 16);
		flag = _getch();
		if (flag == Down)
		{
			l++;
			while (l == 12)
				l = 10;
		}
		if (flag == Up)
		{
			l--;
			while (l == 9)
				l = 11;
		}
		if (flag == 13)
		{
			if (l == 10)
			{
				if (pTemp == pHead)
				{
					pHead = pHead->pNext;
					pHead->pFont = NULL;
					free(pTemp);
					pTemp = NULL;
				}
				else
				{
					if (pTemp->pNext == NULL)
					{
						pTemp->pFont->pNext = NULL;
						free(pTemp);
						pTemp = NULL;
					}
					else
					{
						pTemp->pFont->pNext = pTemp->pNext;
						pTemp->pNext->pFont = pTemp->pFont;
						free(pTemp);
						pTemp = NULL;
					}
				}
				drawnav();
				Gotoxy(52, 10);
				printf("ɾ���ɹ�");
				_getch();
				return pHead;
			}
			if (l == 11)
			{
				return pHead;
			}
		}
	}
}
Node* sortStu(Node* pHead)//ð������ ��С����
{
	Node* pTemp = NULL;
	Node* p = NULL;
	Node* pNew = NULL;
	int i = 0;
	int j = 0;
	int n = 0;
	pNew = (Node*)malloc(sizeof(Node));
	if (pHead== NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("ѧ����ϢΪ��\n");
		return NULL;
	}
	if (pNew == NULL)
	{
		drawnav();
		Gotoxy(52,10);
		printf("����ʧ�ܣ�");
		return pHead;
	}
	pHead->pFont = pNew;
	pNew->pNext = pHead;
	pNew->pFont = NULL;
	pHead = pHead->pFont;
	pTemp = pHead->pNext;
	while (pTemp != NULL)
	{
		pTemp = pTemp->pNext;//temp����
		n++;
	}
	for (i = 1; i<n; i++)
	{
		for (pTemp = pHead->pNext, j = 1; j<n; j++)
		{
			if (pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //ð������
			{
				if (pTemp->pNext->pNext == NULL)  //��С��Ϊ��
				{
					pTemp->pFont->pNext = pTemp->pNext; //���ǰ���ĺ���ָ��С��
					pTemp->pNext->pNext = pTemp; //С�ĺ���ָ����
					pTemp->pNext->pFont = pTemp->pFont; //С��ǰ��ָ����ǰ��
					pTemp->pFont = pTemp->pNext; //���ǰ��ָ��С��
					pTemp->pNext = NULL;  //��ĺ���ָ��NULL
				}
				else
				{
					(pTemp->pFont)->pNext = pTemp->pNext;               //���ǰ���ĺ���ָ��С��
					((pTemp->pNext)->pNext)->pFont = pTemp;             //С�ĺ�����ǰ��ָ����
					pTemp->pNext = ((pTemp->pFont)->pNext)->pNext;     //��ĺ���ָ��С�ĺ���					 
					((pTemp->pFont)->pNext)->pNext = pTemp;            //С�ĺ���ָ����
					((pTemp->pFont)->pNext)->pFont = pTemp->pFont;    //С��ǰ��ָ���ǰ
					pTemp->pFont = ((pTemp->pFont)->pNext);            //���ǰ��ָ��С��
				}
			}
			else
			{
				pTemp = pTemp->pNext;
			}

		}
	}
	p = pHead;
	pHead = pHead->pNext;
	pHead->pFont = NULL;
	free(p);
	p = NULL;
	drawnav(5);
	Gotoxy(52, 10);
	printf("����ɹ�!");
	return pHead;
}