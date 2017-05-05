#ifndef STUDENT_H
#define STUDENT_H
typedef struct Data
{
	char strStuName[20];
	char strStuNum[20];
	int strStuSorce;
}Data; //构造Data数据结构体
typedef struct NODE
{
	Data data;
	struct NODE* pFont;
	struct NODE* pNext;
}Node;   //构造数据节点
Node* S_Head;//建立数据链表头
Node* loadData(Node* pHead);//从文件中读取学生的信息
void print(Node* pHead);//打印全部内容
void saveData(Node* pHead);//保存学生信息到文件中
Node* freeLink(Node* pHead); //清空学生信息
Node* FindStu(Node* pHead);//查找指定学生的信息
int strNum(char* str); //判断学号是否正确
Node* rewriteStu(Node*pHead);//修改指定学生的信息
Node* addStu(Node*pHead);//添加学生信息
int lookupStu(Node* pHead, char* name); //判断是否存在学生
Node* delStu(Node* pHead);//输出指定学生信息
Node* sortStu(Node* pHead);//冒泡排序 由小到大
#endif