#include"all.h"
Node* loadData(Node* pHead)//从文件中读取学生的信息
{
	FILE *p = fopen("dat.txt", "r+");
	Node *pTemp = NULL;
	Node *pNew = NULL;
	char strname[20];
	char strnum[20];
	int sorce;
	if (p != NULL)
	{
		while (fscanf(p, "姓名:%s 学号:%s 成绩:%d\n", strname, strnum, &sorce) == 3)
		{
			pNew = (Node*)malloc(sizeof(Node));
			if (pNew == NULL)
			{
				drawnav();
				Gotoxy(52, 10);
				printf("内存申请失败\n");
				return NULL;
			}
			strcpy(pNew->data.strStuName, strname);
			strcpy(pNew->data.strStuNum, strnum);
			pNew->data.strStuSorce = sorce;   //初始化
			if (pHead == NULL)//若头为空 第一个节点为头
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
		printf("文件打开失败\n");
		return NULL;
	}
	return pHead;
}
void print(Node* pHead)  //打印全部内容
{
	Node *pTemp = pHead;
	int num = 0;//记录学生的个数
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表中无数据\n");
		return;
	}
	int i, j, flag = 0;
	drawnav();
	hicehandle(0);
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 12);
		printf("信息为空");
		_getch();
		return;
	}
	pTemp = pHead;
	for (i = 1, j = 1, pTemp = pHead; pTemp != NULL; i++, j++, pTemp = pTemp->pNext)
	{
		Gotoxy(40, j);
		printf("%2d:学号:%10s 姓名:%6s 成绩%3d ", i,pTemp->data.strStuNum,pTemp->data.strStuName,pTemp->data.strStuSorce);
		if (j % 25 == 0)
		{
			Gotoxy(90, 25);
			printf("回车下一页");
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
	printf("回车退出");
	while (1)
	{
		flag = _getch();
		if (flag == 13)
		{
			return;
		}
	}
}
void saveData(Node* pHead)//保存学生信息到文件中
{
	FILE *p = NULL;
	Node *pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("学生信息为空\n");
		return;
	}
	p = fopen("dat.txt", "w+");
	if (p != NULL)
	{
		pTemp = pHead;
		while (pTemp != NULL)
		{
			fprintf(p, "姓名:%s 学号:%s 成绩:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
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
			printf("文件关闭失败\n");
			return;
		}
	}
	else
	{
		drawnav();
		Gotoxy(52, 10);
		printf("文件打开失败\n");
		return;
	}
}
Node* freeLink(Node* pHead) //清空学生信息
{
	Node* pTemp = NULL;
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表为空\n");
		return NULL;
	}
	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
		/*pTemp->pFont = NULL;
		pTemp->pNext = NULL; */
		//周报有的写了
		pTemp = NULL;
	}
	return pHead;
}
Node* FindStu(Node* pHead)//查找指定学生的信息
{
	Node* pTemp = NULL;
	char str[20];
	if (pHead == NULL)
	{
		drawnav();
		Gotoxy(52, 10);
		printf("链表中无数据\n");
		return NULL;
	}
	while (1)
	{   
		drawnav();
		Gotoxy(45,10);
		hicehandle(1);
		printf("请输入要查找的学生的学号:");
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
			printf("学号输入错误,请重新输入");
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
		printf("查无此人!");
		_getch();
		return NULL;
	}
	drawnav();
	Gotoxy(53, 10);
	printf("已查找到这个学生!");
	Sleep(500);
	drawnav();
	Gotoxy(35, 10);
	printf("学生姓名:%s 学生学号:%s 学生成绩:%d\n", pTemp->data.strStuName, pTemp->data.strStuNum, pTemp->data.strStuSorce);
	_getch();
	return pTemp;
}
int strNum(char* str) //判断学号是否正确
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
		printf("链表中无数据\n");
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
				printf("请选择要修改的信息");
				Gotoxy(52, 10);
				printf("1.学生姓名");
				Gotoxy(52, 11);
				printf("2.学生学号");
				Gotoxy(52, 12);
				printf("3.学生成绩");
				Gotoxy(52, 13);
				printf("4.返回上一层");
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
						printf("请输入修改后的姓名:");
						hicehandle(1);
						scanf("%s", pTemp->data.strStuName);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
						Sleep(500);
					}
					if (l == 11)
					{
						while (1)
						{
							drawnav();
							Gotoxy(48, 10);
							printf("请输入修改后的学号:");
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
									printf("学号已存在请重新输入！");
									Gotoxy(48, 10);
									printf("请输入修改后的学号:        \b\b\b\b\b\b\b\b");
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
							printf("请输入正确学号！");
							Sleep(500);
						}
						strcpy(pTemp->data.strStuNum,stuNum);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
						Sleep(500);
					}
					if (l == 12)
					{
						drawnav();
						Gotoxy(52, 10);
						printf("请输入修改后的成绩:");
						hicehandle(1);
						scanf("%d", &pTemp->data.strStuSorce);
						hicehandle(0);
						drawnav();
						Gotoxy(53, 10);
						printf("修改成功!");
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
	printf("查无此人");
	return pHead;
}
Node* addStu(Node*pHead)//添加学生信息
{
	int n = 0;   //要添加学生的个数
	int flogs = 1;
	int l = 11;
	int i;
	int flag;
	Node* pNew = NULL;
	Node* pStu = NULL;
	Node* pFoot = NULL;
	drawnav();
	Gotoxy(48, 10);
	printf("请输入要添加学生的个数:");
	Gotoxy(48, 12);
	printf("注：若只添加一个需要指定位置");
	hicehandle(1);
	Gotoxy(72, 10);
	scanf("%d", &n);
	hicehandle(0);
	if (n == 1)  //插入一个学生
	{
		if (pHead == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("链表为空\n");
			return NULL;
		}
		while (pStu == NULL)
		{
			printf("未找到插入位置 请重新查找\n");
			pStu = FindStu(pHead);
		}
		pNew = (Node*)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			drawnav();
			Gotoxy(52, 10);
			printf("创建节点失败\n");
			return NULL;
		}
		while (flogs)
		{   
			drawnav();
			Gotoxy(48, 10);
			printf("请输入要插入学生的信息:");
			Gotoxy(50, 12);
			printf("学生姓名:");
			Gotoxy(50, 13);
			printf("学生学号:");
			Gotoxy(50, 14);
			printf("学生成绩:");
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
					printf("学号已存在请重新输入！");
					Gotoxy(50, 13);
					printf("学生学号:         \b\b\b\b\b\b\b\b");
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
				printf("您输入的信息有误,请重新输入\n");
				_getch();
			}
		}
		while (1)
		{
			drawnav();
			Gotoxy(48, 10);
			printf("请选择要插入的位置\n");
			Gotoxy(48, 11);
			printf("前");
			Gotoxy(48, 12);
			printf("后");
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
				if (l == 11)   //插入指定位置前
				{
					if (pStu == pHead)
					{
						pHead->pFont = pNew;
						pNew->pFont = NULL;
						pNew->pNext = pHead;
						pHead = pHead->pFont;
						drawnav();
						Gotoxy(52, 10);
						printf("添加成功！");
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
						printf("添加成功！");
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
						printf("添加成功！");
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
						printf("添加成功！");
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
				printf("创建节点失败\n");
				return pHead;
			}
			while (1)
			{
				drawnav();
				Gotoxy(48, 10);
				printf("请输入第%d个要插入学生的信息:",i+1);
				Gotoxy(50, 12);
				printf("学生姓名:");
				Gotoxy(50, 13);
				printf("学生学号:");
				Gotoxy(50, 14);
				printf("学生成绩:");
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
						printf("学号已存在请重新输入！");
						Gotoxy(50, 13);
						printf("学生学号:         \b\b\b\b\b\b\b\b");
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
					printf("您输入的信息有误,请重新输入\n");
				}
			}
			while (pFoot->pNext != NULL&&pHead != NULL)
			{
				pFoot = pFoot->pNext;  //遍历找尾
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
		printf("添加成功！");
		_getch();
		return pHead;
	}
	return pHead;
}
int lookupStu(Node* pHead, char* Num) //判断是否存在学生
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
Node* delStu(Node* pHead)//输出指定学生信息
{
	Node* pTemp;
	int l = 10;
	int flag;
	pTemp = FindStu(pHead);
	while (1)
	{

		drawnav();
		Gotoxy(52, 9);
		printf("是否要删除?");
		Gotoxy(52, 10);
		printf("1.是");
		Gotoxy(52, 11);
		printf("2.否");
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
				printf("删除成功");
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
Node* sortStu(Node* pHead)//冒泡排序 由小到大
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
		printf("学生信息为空\n");
		return NULL;
	}
	if (pNew == NULL)
	{
		drawnav();
		Gotoxy(52,10);
		printf("排序失败！");
		return pHead;
	}
	pHead->pFont = pNew;
	pNew->pNext = pHead;
	pNew->pFont = NULL;
	pHead = pHead->pFont;
	pTemp = pHead->pNext;
	while (pTemp != NULL)
	{
		pTemp = pTemp->pNext;//temp后移
		n++;
	}
	for (i = 1; i<n; i++)
	{
		for (pTemp = pHead->pNext, j = 1; j<n; j++)
		{
			if (pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //冒泡排序
			{
				if (pTemp->pNext->pNext == NULL)  //若小后为空
				{
					pTemp->pFont->pNext = pTemp->pNext; //大的前驱的后驱指向小的
					pTemp->pNext->pNext = pTemp; //小的后驱指向大的
					pTemp->pNext->pFont = pTemp->pFont; //小的前驱指向大的前驱
					pTemp->pFont = pTemp->pNext; //大的前驱指向小的
					pTemp->pNext = NULL;  //大的后驱指向NULL
				}
				else
				{
					(pTemp->pFont)->pNext = pTemp->pNext;               //大的前驱的后驱指向小的
					((pTemp->pNext)->pNext)->pFont = pTemp;             //小的后驱的前驱指向大的
					pTemp->pNext = ((pTemp->pFont)->pNext)->pNext;     //大的后驱指向小的后驱					 
					((pTemp->pFont)->pNext)->pNext = pTemp;            //小的后驱指向大的
					((pTemp->pFont)->pNext)->pFont = pTemp->pFont;    //小的前驱指向大前
					pTemp->pFont = ((pTemp->pFont)->pNext);            //大的前驱指向小的
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
	printf("排序成功!");
	return pHead;
}