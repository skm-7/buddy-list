#include<iostream>
#include<math.h>
#include<stdlib.h>
 int MIN_SIZE =32;
 int MAX_SIZE =2048;
 int start;
using namespace std;
class sllnode
{
	public:
	int info;
	char * locate;
	sllnode* next;
	
	sllnode(void)
	{
	info=0;
	locate=NULL;
	next=NULL;
	//cout<<"Constructor 1 node"<<endl;
	}	
	sllnode(int x,sllnode *p,char* a)
	{
		locate=a;
		info=x;
		next=p;
		//cout<<"Constructor 2 node"<<endl;
	}
	~sllnode()
	{
		cout<<"sllnode desctructor "<<endl;
	}
};
class sllist
{
public:
	sllnode * head;
	int lncount;
	sllist(void)
	{
		head=NULL;
		lncount=0;
		//cout<<"Constructor 1 list"<<endl;
	}
	sllist(sllnode *p,int n)
	{
		lncount=n;
		head=p;
		cout<<"Constructor 2 list"<<endl;
	}
	void insbeg(int x,char* p);
	void insbeg();
	int delbeg(void);
	int search(int x);
	void dispsll(void);
	~sllist();
};
void sllist::insbeg(int x,char* p)
{
	head=new sllnode(x,head,p);
	lncount++;
}
void sllist::insbeg()
{
	head=new sllnode();
	lncount++;
}
int sllist:: delbeg(void)
{
	sllnode *a=head;
	head=head->next;
	int n=a->info;
	a->locate=NULL;
	delete []a;
	lncount--;
	return n;
}
int sllist::search(int x)
{
	int cnt;
	cnt=0;
	sllnode *t=head;
	while(t!=NULL)
	{
		cnt++;
		if(t->info==x)
		{
			return cnt;
		}
			t=t->next;
		
	}
	return -1;
}
sllist::~sllist()
{
	//while(head !=NULL)
	//{
		//delbeg();
	cout<<"The list destructor"<<endl;
	sllnode *p=head;
	while(p!=NULL)
	{
		head=p->next;
		delete p;
		p=head;
	}

}
void sllist:: dispsll()
{
	sllnode *t=head;
	cout<<"["<<lncount<<"]";
	while(t!=NULL)
	{
		cout<<"->"<<t->info<<": "<<t->locate;	
		t=t->next;
	}
	cout<<endl;

}

class hash_table
{
public:
	 sllist *ht;
	 int htsize;
	 //int iterator;
	 hash_table(int t)
	 {
	 	ht=new sllist[t];
	 	htsize=t;
	 }
	 void inshash(int x)	 
	{
		int pos=ceil(log2(x)-log2(MIN_SIZE));
		char* a=NULL;
		ht[pos].insbeg(x,a);
	}
	void inshash(int x,char* a)	 
	{
		int pos=ceil(log2(x)-log2(MIN_SIZE));
		ht[pos].insbeg(x,a);
	}
	void searchhash(int x)
	{
		int pos=x%htsize;
		//cout<<pos<<endl;
		int p=ht[pos].search(x);
		if (p==-1)
		{
			cout<<"Not Found"<<endl;
		}
		else
		{
			cout<<"found at index "<<pos<<" element number "<<p<<endl;
		}
	}
	~hash_table()
	{
		
			if (ht!=NULL)
			delete []ht;
			
		cout<<"hash_table desctructor"<<endl;
	}

};

class buddy
{
public:
	int sizekb;
	int size_total;
	char * memory;	
	//const int MIN_SIZE;
	hash_table *h;

public:
	hash_table* initiate(int sizekb);
	buddy();
	buddy(int sizekb);
	bool isempty();
	void request(int sizekb);
	int gettableSize(int sizekb);
	int getListNo(int listNo);
	void display(int sizekb);


};


buddy::buddy()
{
	//cout<<MAX_SIZE<<endl;
	//MAX_SIZE++;
	//cout<<MAX_SIZE<<endl;
	h=initiate(MAX_SIZE);
}

buddy::buddy(int sizekb)
{
	h=initiate(sizekb);
}
hash_table* buddy::initiate(int sizekb)
{
	//cout<<"B"<<sizekb<<endl;
	size_total=sizekb *1024*sizeof(char);
	memory=new char[size_total];
	//cout<<"D"<<sizekb<<endl;
	cout<<memory<<endl;
	if(memory==NULL)
	{
		cout<<"could not allocate memory"<<endl;
		exit(0);
	}
	start=getListNo(sizekb);
	//cout<<sizekb<<endl;
	//cout<<gettableSize(sizekb)<<endl;
	h=new hash_table(gettableSize(sizekb));
	for(int i=0;i<gettableSize(sizekb);i++)
	{	
		h->ht[i].insbeg();
		//cout<<h->ht[i].head->info<<endl;
		h->ht[i].head->info=(pow(2, i + log2(MIN_SIZE)));
		//cout<<h->ht[i].head->info<<endl;
		h->ht[i].head->locate=NULL;
	}
	//cout<<memory<<endl;
	h->ht[getListNo(sizekb)].head->locate=memory;

	//cout<<getListNo(sizekb)<<endl;
	//cout<<h->ht[getListNo(sizekb)].head->locate<<endl;
	return h;
	
}
int buddy::getListNo(int sizekb) {
	//cout<<"A"<<sizekb<<endl;
	//cout<<log10(sizekb)/log10(2)<<endl;
    return ceil(log(sizekb)/log(2) - log(MIN_SIZE)/log(2));
}
int buddy::gettableSize(int sizekb) {
	//cout<<"C"<<sizekb<<endl;
    return getListNo(sizekb) +1;
}
void buddy::display(int sizekb)
{
	for(int i=0;i<gettableSize(sizekb);i++)
	{
		//cout<<"a"<<endl;
		if (h->ht[i].head->locate!= NULL)
			cout<<h->ht[i].head->info<<":     "<<&(h->ht[i].head->locate)<<endl;
		else
			cout<<h->ht[i].head->info<<":      "<<endl;
	}
}
void buddy:: request(int sizekb)
{
	int listNo=getListNo(sizekb);
	int k;
	//bool found=false;
	if(h->ht[listNo].head->locate==NULL)
	{		
			
			for(int i=getListNo(MAX_SIZE);i>=listNo;i--)
			{
				k=pow(2, i+log2(MIN_SIZE))*1024*sizeof(char);
				h->ht[i].head->locate=h->ht[getListNo(MAX_SIZE)].head->locate-k;


			}
			h->ht[start].head->locate=NULL;
			memory=h->ht[listNo].head->locate;
			start=listNo;
	} 
	else
	{
		//cout<<"a"<<endl;
		listNo=getListNo(2*sizekb);
		for(int i=getListNo(MAX_SIZE);i>=listNo;i--)
			{
				k=pow(2, i+log2(MIN_SIZE))*1024*sizeof(char);
				h->ht[i].head->locate=h->ht[getListNo(MAX_SIZE)].head->locate-k;


			}
			h->ht[start].head->locate=NULL;
			memory=h->ht[listNo].head->locate;
			start=listNo;
	} 
}



int main()
{
	int req,n;
	cout<<"INITIAL"<<endl;
	cout<<"Min size:32KB"<<endl;
	cout<<"MIN_SIZE size:2048KB"<<endl;

	cout<<"Memory status"<<endl;
	int ch;
	buddy A;
	
	A.display(MAX_SIZE);
	//return 0;
	cout<<"Enter the number of test cases"<<endl;
	cin>>n;
	while(n--)
	{
		cout<<"Enter the request of allocation"<<endl;
		cin>>req;
		A.request(req);
		
		A.display(MAX_SIZE);
	}

}



