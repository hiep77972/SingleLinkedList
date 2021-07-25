#include<bits/stdc++.h>
using namespace std;

typedef struct{
	int ma;
	string ten;
	int age;
}Data;
typedef struct tagNode{
	Data infor;
	struct tagNode *link;
}Node;
typedef struct{
	Node *phead;
	Node *ptail;
	int spt;
}LList;
void initL(LList *L){
	L->phead=NULL;
	L->ptail=NULL;
	L->spt=0;
}
int emptyL(LList L){
	return (L.spt==0);
}
void nhap(Data*x){
	cin.ignore();
	cout<<"nhap ten = ";
	getline(cin,x->ten);
	cout<<"nhap ma = ";
	cin>>x->ma;
	cout<<"nhap tuoi = ";
	cin>>x->age;
}
void in(Data x){
	cout<<"Ma = "<<x.ma<<",Ten = "<<x.ten<<",Tuoi = "<<x.age<<'\n';
}
void insert_dau(LList *L,Data x){
	Node *pp=new Node;
	pp->infor=x;
	pp->link=NULL;
	if(emptyL(*L)){
		L->phead=pp;
		L->ptail=pp;
	}
	else{
		pp->link=L->phead;
		L->phead=pp;
	}
	L->spt++;
}
void insert_cuoi(LList *L,Data x){
	Node *pp= new Node;
	pp->infor=x;
	pp->link=NULL;
	if(emptyL(*L)){
		L->phead=pp;
		L->ptail=pp;
	}
	else{
		L->ptail->link=pp;
		L->ptail=pp;
	}
	L->spt++;
}
void insert_giua(LList *L,int vt,Data x){
	Node *pp=new Node;
	pp->infor=x;
	pp->link=NULL;
	if(vt==1) insert_dau(L,x);
	else if(vt==L->spt) insert_cuoi(L,x);
	else{
		Node *tmp=L->phead;
		while(vt!=1){
			tmp=tmp->link;
			vt--;
		}
		pp->link=tmp->link;
		tmp->link=pp;
		L->spt++;
	}
}
void xoa_dau(LList *L){
	if(emptyL(*L)){
		return;
	}
	if(L->phead==L->ptail){
		L->phead=NULL;
		L->ptail=NULL;
	}	
	else{
		Node *tmp=L->phead;
		L->phead=L->phead->link;
		delete tmp;
	}
	L->spt--;
}
void xoa_cuoi(LList *L){
	if(emptyL(*L)) return;
	if(L->phead==L->ptail){
		L->phead=NULL;
		L->ptail=NULL;
	}
	else{
		Node *tmp=L->ptail;
		Node *temp=L->phead;
		while(temp->link!=L->ptail) temp=temp->link;
		temp->link=NULL;
		L->ptail=temp;
		delete tmp;
	}
	L->spt--;
}
void xoa_giua(LList *L,int vt){
	if(emptyL(*L)) return;
	if(vt==1) xoa_dau(L);
	else if(vt==L->spt) xoa_cuoi(L);
	else{
		Node *temp=L->phead;
		Node *tmp=new Node;
		while(vt!=1){
			tmp=temp;
			temp=temp->link;
			vt--;
		}
		Node *tg=tmp->link;
		tmp->link=tmp->link->link;
		delete tg;
		L->spt--;	
	}
}
void xoa_sau(LList *L,Node *qq){
	if(qq==NULL) return;
	else{
		if(qq->link==L->ptail) xoa_cuoi(L);
		else{
			Node *tg=new Node;
			tg=qq->link;
			qq->link=qq->link->link;
			delete tg;
			L->spt--;
		}
	}
}
//
void xoa_K(LList *L,int x){
	if(L->phead->infor.ma==x) xoa_dau(L);
	else if(L->ptail->infor.ma==x) xoa_cuoi(L);
	else{
		Node *temp=L->phead;  //
		while(temp!=NULL && temp->link!=NULL && (temp->link->infor.ma!=x))
			temp=temp->link;
		if(temp==L->ptail) return;
		else{
			Node *tg=temp->link;
			temp->link=temp->link->link;
			delete tg;
			L->spt--;
		}
	}
}
//
void insert_sau(LList *L,Node *qq,Data x){
	if(qq==NULL) return;
	else{
		if(qq->link==L->ptail) insert_cuoi(L,x);
		else{
			Node *tg=new Node;
			tg->infor=x;
			tg->link=qq->link;
			qq->link=tg;
			L->spt++;
		}
	}
}
//
void chen_tang(LList *L,Data x){
	if(emptyL(*L)) insert_dau(L,x);
	else{
		Node *temp=L->phead;
		Node *tg=new Node;
		while(temp!=NULL && x.ma>=temp->infor.ma){
			tg=temp;
			temp=temp->link;
		}
		if(temp==L->phead) insert_dau(L,x);
		else if(temp==NULL) insert_cuoi(L,x);
		else insert_sau(L,tg,x);
	}
}
//
Node* tktt(LList L,int x){
 Node *i;
 for(i=L.phead; i!=NULL; i=i->link)
 if(i->infor.ma== x) return i;
 return NULL;
}
Node *trc(LList L,Node *qq){
	if(qq==NULL) return NULL;
	Node *temp = L.phead;
	while(temp->link!=qq) temp=temp->link;
	return temp;
}
void interchangeSort(LList *L){
	for(Node *i=L->phead;i->link!=NULL;i=i->link){
		for(Node *j=i->link;j!=NULL;j=j->link){
			if(i->infor.ma>j->infor.ma){
				swap(i->infor,j->infor);
			}
		}
	}
}
void selectionSort(LList *L){
	for(Node *i=L->phead;i->link!=NULL;i=i->link){
		Node *minn=i;
		for(Node *j=i->link;j!=NULL;j=j->link){
			if(j->infor.ma<minn->infor.ma)
				minn=j;
		}
		if(minn!=i)
			swap(minn->infor,i->infor);
	}
}
void bubbleSort(LList *L){
	for(Node *i=L->phead;i->link!=NULL;i=i->link){
		for(Node *j=L->ptail;j!=i;j=trc(*L,j)){
			if(j->infor.ma<trc(*L,j)->infor.ma)
				swap(j->infor,trc(*L,j)->infor);
		}
	}
}
//
void insertionSort(LList *L){
	Data x;
	Node *pos;
	for(Node *i=L->phead->link;i!=NULL;i=i->link){
		pos=i;
		x=i->infor;
		while(pos!=L->phead && x.ma<trc(*L,pos)->infor.ma){
			pos->infor=trc(*L,pos)->infor;
			pos=trc(*L,pos);
		}
		pos->infor=x;
	}
}
//
void QS(LList*L){
	LList L1,L2;
	Node *tag,*p;
	if(L->phead==L->ptail) return;
	initL(&L1);initL(&L2);
	tag=L->phead;
	L->phead=L->phead->link;
	tag->link=NULL;
	while(L->phead!=NULL){
		p=L->phead;
		L->phead=L->phead->link;
		p->link=NULL;
		if(p->infor.ma <= tag->infor.ma) insert_cuoi(&L1,p->infor);// >
		else insert_cuoi(&L2,p->infor);
	}
	QS(&L1);
	QS(&L2);
	if(L1.phead!=NULL){
		L->phead=L1.phead;
		L1.ptail->link=tag;
	}
	else L->phead=tag;
	tag->link=L2.phead;
	if(L2.phead!=NULL) L->ptail=L2.ptail;
	else L->ptail=tag;
}
void duyet(LList L){
	Node *pp=L.phead;
	while(pp!=NULL){
		in(pp->infor);
		pp=pp->link;
	}
}
//useless
Node* getmid(LList L){
//	if(emptyL(L) || L.spt==0) return NULL;
	Node *slow=L.phead;
	Node *fast=L.phead->link;
	while (fast != NULL) {
        fast = fast->link;
        if (fast != NULL) {
            slow = slow->link;
            fast = fast->link;
        }
    }
    return slow;
}
void merge(LList *L,LList *L1,LList *L2){
	initL(L);
	if(L1->phead==NULL){
		L->phead=L2->phead;
		L->ptail=L2->ptail;
	} 
	if(L2->phead==NULL){
		L->phead=L1->phead;
		L->ptail=L1->ptail;
	} 
	
		Node *i=L1->phead,*j=L2->phead;
		while(i!=NULL && j!=NULL){
			if(i->infor.ma<=j->infor.ma){
				insert_cuoi(L,i->infor);
				i=i->link;
			}
			else{
				insert_cuoi(L,j->infor);
				j=j->link;
			}
		}
		while(i!=NULL){
			insert_cuoi(L,i->infor);
			i=i->link;
		}
		while(j!=NULL){
			insert_cuoi(L,j->infor);
				j=j->link;
		}
}

void tach(LList L,LList *L1,LList *L2){
    Node *tmp = getmid(L);
    L1->phead=L.phead;
    L1->ptail=tmp;
    L2->phead=tmp->link;
    L2->ptail=L.ptail;
    tmp->link=NULL;
}
void MergeSort(LList *L){
	if(L->phead==NULL || L->phead->link==NULL) return;
	LList L1,L2;
	initL(&L1);
	initL(&L2);
	tach(*L,&L1,&L2);
	MergeSort(&L1);
	MergeSort(&L2);
	merge(L,&L1,&L2);
}
/////////////////////////////////
void LIFO(LList *L)
{
 	Data x;
 	initL(L);
 	do{
 	nhap(&x);
 	if(x.ma!=0)
  		insert_dau(L,x);
 	}while(x.ma!=0);
}

void FIFO(LList *L)
{
 	Data x;
 	initL(L);
 	do{
 		nhap(&x);
 		if(x.ma!=0)
  			insert_cuoi(L,x);
 	}while(x.ma!=0);
}
void noi(LList *n,LList *m){
	if(emptyL(*n) || emptyL(*m)) return ;
	else{
		n->ptail->link=m->phead;
		n->ptail=m->phead;
    	n->spt=n->spt+m->spt;
	}
}
////////////////
int main(){
	
	LList L,L1,L2;
	initL(&L);
	initL(&L1);
	initL(&L2);
	int n,m;
	cin>>n;
//	cin>>n>>m;
	Data x;
	while(n--){
		nhap(&x);
		insert_cuoi(&L,x);
	}
//	tach(L,&L1,&L2);
//		cout<<'\n';
//	duyet(L1);
//	cout<<'\n';
//	duyet(L2);



//	tach(L,&L1,&L2);
//	cout<<'\n';
//	duyet(L1);
//	while(m--){
//		nhap(&x);
//		insert_cuoi(&L2,x);
//	}
//	L=merge(&L1,&L2);
//	duyet(L);
//	cout<<'\n';

//	nhap(&x);
//	chen_tang(&L,x);
//	in(trc(L,L.phead->link->link)->infor);
//	xoa_K(&L,1);

//	QS(&L);
//	selectionSort(&L);
//	insertionSort(&L);
//	in(getmid(L)->infor);

	MergeSort(&L);	
	cout<<'\n';
	duyet(L);


//	nhap(&x);
//	insert_giua(&L,2,x);
//	Sort(&L);
//	cout<<'\n';
//	duyet(L);
//	xoa_cuoi(&L);
//	xoa_dau(&L);
//	cout<<'\n';
//	duyet(L);
//	xoa_giua(&L,2);
//	cout<<'\n';
//	duyet(L);
	
	return 0;
}
