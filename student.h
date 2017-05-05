#ifndef STUDENT_H
#define STUDENT_H
typedef struct Data
{
	char strStuName[20];
	char strStuNum[20];
	int strStuSorce;
}Data; //����Data���ݽṹ��
typedef struct NODE
{
	Data data;
	struct NODE* pFont;
	struct NODE* pNext;
}Node;   //�������ݽڵ�
Node* S_Head;//������������ͷ
Node* loadData(Node* pHead);//���ļ��ж�ȡѧ������Ϣ
void print(Node* pHead);//��ӡȫ������
void saveData(Node* pHead);//����ѧ����Ϣ���ļ���
Node* freeLink(Node* pHead); //���ѧ����Ϣ
Node* FindStu(Node* pHead);//����ָ��ѧ������Ϣ
int strNum(char* str); //�ж�ѧ���Ƿ���ȷ
Node* rewriteStu(Node*pHead);//�޸�ָ��ѧ������Ϣ
Node* addStu(Node*pHead);//���ѧ����Ϣ
int lookupStu(Node* pHead, char* name); //�ж��Ƿ����ѧ��
Node* delStu(Node* pHead);//���ָ��ѧ����Ϣ
Node* sortStu(Node* pHead);//ð������ ��С����
#endif