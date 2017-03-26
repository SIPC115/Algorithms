#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define ElemType int
using namespace std;

//*顺序表存储结构 
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

void Print1(LinkList &);//带头结点输出 
void Print2(LinkList &);//不带头结点输出 

// 前插法（头插法）建立单链表（带头结点） 
void CreateList1(LinkList &L) {
	LinkList s;
	ElemType d;
	L = (LinkList)malloc(sizeof(LNode));
	L -> next = NULL;
	while(cin >> d && d != -1){
		s = (LinkList)malloc(sizeof(LNode));
		s -> data = d;
		s -> next = L -> next;
		L -> next = s;
	}
}

// 尾插法建立单链表（不带头结点） 
void CreateList2(LinkList &L) {
	LinkList rear,s;
	ElemType d;
	while(cin >> d && d != -1){
		if(L == NULL){
			L = (LinkList)malloc(sizeof(LNode));
			L -> data = d;
			L -> next = NULL;
			rear = L;
			continue;
		}
		s = (LinkList)malloc(sizeof(LNode));
		s -> data = d;
		s -> next = NULL;
		rear -> next = s;
		rear = s;
	}
}

// 尾插法建立带头结点单链表
void CreateList3(LinkList &L) {
	LinkList rear,s;
	ElemType d;
	L = (LinkList)malloc(sizeof(LNode));
	L -> next = NULL;
	rear = L;
	while(cin >> d && d != -1){
		s = (LinkList)malloc(sizeof(LNode));
		s -> data = d;
		s -> next = NULL;
		rear -> next = s;
		rear = s;
	}
}


// 递归删除不带头结点的单链表L中所有值为x的结点 
LinkList Del_x1(LinkList L, ElemType x) {
	if(L == NULL) return NULL;
	if(L -> data == x) 
		return Del_x1(L -> next, x); 
	L -> next = Del_x1(L -> next, x);
	return L;
}

//*删除带头结点的单链表L中所有值为x的结点，并释放其空间 
void Del_x2(LinkList &L, ElemType x) {
	LinkList p;
	p = L;
	while(p -> next != NULL) {
		if(p -> next -> data == x){
			p -> next = p -> next -> next;
		}
		p = p -> next; 
	}
}

//*L为带头结点的单链表，从尾到头反向输出每个节点的值
void Reverse_Print(LinkList &L) {
	LinkList s,N,p;
	N = (LinkList)malloc(sizeof(LNode));
	N -> next = NULL;
	p = L;
	while(p -> next != NULL) {
		s = (LinkList)malloc(sizeof(LNode));
		s -> data = p -> next -> data;
		s -> next = N -> next;
		N -> next = s;
		p = p -> next;
	}
	Print1(N);
}

// 删除带头结点的L中的最小值结点 
void Delete_Min(LinkList &L) {
	LinkList q,m;
	q = L;
	m = q;
	while(q -> next != NULL) {
		if(m -> next -> data > q -> next ->data)
			m = q;
		q = q -> next;
	}
	m -> next = m -> next -> next;
}

//*将带头结点的单链表就地逆置，即空O(1)
void Reverse_1(LinkList &L) {
	LinkList p,q,s;
	p = L;
	q = L -> next;
	while(q != NULL) {
		s = q -> next;
		q -> next = p;
		p = q;
		q = s; 
	}
	L -> next -> next = NULL;
	L -> next = p;
}	

//*将带头结点的单链表逆置(头插入法)
LinkList Reverse_2(LinkList &L) {
	LinkList p,q,s,N;
	N = (LinkList)malloc(sizeof(LNode));
	N -> next = NULL;
	p = L;
	q = N;
	while(p -> next != NULL) {
		s = p -> next;
		p -> next = p -> next -> next;
		q -> next = s;
		q = q -> next;
	}
	return N;
}

// 有一个带头结点的单链表L，设计一个算法使其递增有序 
void Sort(LinkList &L) {
	LinkList q,s,m;
	q = L;
	while(q -> next != NULL) {
		s = q;
		m = s;
		while(s -> next != NULL) {
			if(s -> next -> data < m -> next -> data)
				m = s;
			s = s -> next;
		}
		s = m -> next;
		m -> next = m -> next -> next;
		s -> next = q -> next;
		q -> next = s;
		q = q -> next;
	}
}

//*给定两个单链表，编写算法找出两链表的公共节点（公共结点之后的元素都相同） 
LinkList Search_Common(LinkList &L, LinkList &M) {
	int lenl = 0,lenm = 0,d,k = 0,s = 0,ld;
	LinkList p,q;
	p = L;
	while(p != NULL) {
		lenl++;
		p = p -> next;
	}
	p = M;
	while(p != NULL) {
		lenm++;
		p = p -> next;
	}
	d = lenl - lenm;
	ld = d;
	p = L;
	q = M;
	if(d > 0) 
		while(d--) p = p -> next;
	else{
		d *= -1;
		while(d--) q = q -> next;
	}
	while(p != NULL) {
		if(p -> data == q -> data)
			k++;
		else {
			s += k;
			k = 0;
		}
		p = p -> next;
		q = q -> next;
	}
	p = L;
	q = M;
	if(ld > 0) 
		while(ld--) p = p -> next;
	else{
		ld *= -1;
		while(ld--) q = q -> next;
	}
	while(s--) p = p -> next;
	return p;
}

//*将两个递增有序的单链表归并为一个递减单链表（不添加新的结点） 
LinkList MergeList(LinkList &LA, LinkList &LB) {
	LinkList c = NULL,p,q,s;
	p = LA;
	q = LB;
	while(p -> next != NULL && q -> next != NULL){
		if(p -> next -> data < q -> next -> data) {
			s = p -> next;
			p -> next = p -> next -> next;
		} else {
			s = q -> next;
			q -> next = q -> next -> next;
		}
		s -> next = c;
		c = s;
	}
	while(p -> next != NULL){
		s = p -> next;
		p -> next = p -> next -> next;
		s -> next = c;
		c = s;
	}
	while(q -> next != NULL){
		s = q -> next;
		q -> next = q -> next -> next;
		s -> next = c;
		c = s;
	}
	return c;
}

//*两个链表A和B分别表示两个集合，其元素递增排列，编制函数，求A和B的交集，并存放于A链中 
void Union(LinkList &LA, LinkList &LB) {
	LinkList p,q;
	p = LA;
	q = LB;
	while(p -> next != NULL) {
		q = LB;
		while(q -> next != NULL) {
			if(p -> next -> data == q -> next -> data)
				break;
			q = q -> next;
		}
		if(q -> next != NULL)
			p = p -> next;	
		else
			p -> next = p -> next -> next;
	}
}

// 一个带头结点的单链表，只给出了头指针list，不改变链表的前提下，设计一个尽可能高效的算法，
// 查找倒数第k个位置上的结点。若成功，输出data域并返回1；否则只返回0。
int Search_k(LinkList &list, int k) {
	int i;
	LinkList p,q;
	p = list;
	for(i = 0; i < k; i++)
		if(p -> next != NULL)
			p = p -> next;
		else
			break;
	if(i != k) return 0;
	q = list;
	while(p -> next != NULL) {
		q = q -> next;
		p = p -> next;
	}
	cout << q -> next -> data << endl;
	return 1;
}

// 从带头结点的链表中删除所有其值重复的元素，使得表中所有元素的值均不同 
void Del_same(LinkList &L) {
	LinkList p,q;
	p = L;
	while(p -> next != NULL) {
		q = p -> next;
		while(q -> next != NULL) {
			if(q -> next -> data == p -> next -> data)
				break;
			q = q -> next;
		}
		if(q -> next != NULL)
			p -> next = p -> next -> next;
		else
			p = p -> next;
	}
}

// 从带头结点的链表中删除所有其值重复的元素，使得表中所有元素的值均不同 
void Del_same2(LinkList &L) {
	LinkList p,q;
	p = L;
	while(p -> next != NULL) {
		q = L;
		while(q != p) {
			if(q -> next -> data == p -> next -> data)
				break;
			q = q -> next;
		}
		if(q != p)
			p -> next = p -> next -> next;
		else
			p = p -> next;
	}
}


int main() {
	LinkList L = NULL;
	
	CreateList1(L);
	Print1(L); 
	
	CreateList2(L);
	Print2(L);
	
	//Del_x1(L, x)
	ElemType x;
	cout << "Create the LinkList:" << endl;
	CreateList2(L);
	cout << "Input the x:" << endl;
	cin >> x;
	L=Del_x1(L, x);
	Print2(L);
	
	//
	ElemType x;
	cout << "Create the LinkList:" << endl;
	CreateList1(L);
	cout << "Input the x:" << endl;
	cin >> x;
	Del_x2(L, x);
	Print1(L);
	
	//Reverse_Print(L)
	CreateList1(L);
	Reverse_Print(L);

	//Delete_Min(L)
	CreateList1(L);
	Delete_Min(L);
	Print1(L);
	
	//Reverse_1(L)
	CreateList1(L);
	L = Reverse_2(L);
	Print1(L);
	
	//Sort(L)
	CreateList1(L);
	Sort(L);
	Print1(L);
	
	//Search_Common(L)
	LinkList M;
	CreateList2(L);
	CreateList2(M);
	L = Search_Common(L, M);
	Print2(L);
	
	//MergeList(L, M)
	LinkList M;
	CreateList3(L);
	CreateList3(M);
	L = MergeList(L, M);
	Print2(L);
	
	//Union(L, M)
	LinkList M;
	CreateList3(L);
	CreateList3(M);
	Union(L, M);
	Print1(L);
	
	//Search_k(L, k)
	int k;
	cout << "Input the list:" << endl;
	CreateList3(L);
	cout << "Input the k:" << endl;
	cin >> k;
	int result = Search_k(L, k);
	if(!result)
		cout << "NOT EXISTS!" << endl;
	
	//Del_same(L)
	CreateList3(L);
	Del_same(L);
	Print1(L);
	
	//Del_same2(L)
	CreateList3(L);
	Del_same2(L);
	Print1(L);
	
	return 0;
}

void Print1(LinkList &L) {
	LinkList p;
	p = L;
	while(p -> next != NULL) {
		cout << p -> next -> data << " ";
		p = p -> next;	
	}
	cout << endl;
}

void Print2(LinkList &L) {
	LinkList p;
	p = L;
	while(p != NULL) {
		cout << p -> data << " ";
		p = p -> next;	
	}
	cout << endl;
}