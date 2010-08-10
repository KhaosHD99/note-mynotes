#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define L 8
#define falses 0
#define ture 1
using namespace std;

typedef struct
{
	int key;
	char otherinfo;
}rectype;

typedef rectype seqlist[L+1];
int num;
seqlist r;
void insertsort();
void bubblesort();
void quicksort(int low,int high);
void shellsort();
void selectsort();
void mergesort();
int partition(int i,int j);
void heap();
int main()
{
	seqlist s;
	int i,k;
	char ch1,ch2,q;
	cout<<"请输入"<<L<<"个待排序数据(按回车分隔)"<<endl;
	for(i=1;i<=L;i++)
	{
		cin>>s[i].key;
	}
	cout<<"排序数据已经输入完毕!"<<endl;
	ch1='y';
	while(ch1=='y'||ch1=='Y')
	{
		cout<<"\t\t                  排序子系统                  "<<endl;
		cout<<"\t\t**********************************************"<<endl;
		cout<<"\t\t*            1----更新排序数据               *"<<endl;
		cout<<"\t\t*            2----直接插入排序               *"<<endl;
		cout<<"\t\t*            3----希 尔  排 序               *"<<endl;
		cout<<"\t\t*            4----冒 泡  排 序               *"<<endl;
		cout<<"\t\t*            5----快 速  排 序               *"<<endl;
		cout<<"\t\t*            6----选 择  排 序               *"<<endl;
		cout<<"\t\t*            7----归 并  排 序               *"<<endl;
		cout<<"\t\t*            8----堆   排   序               *"<<endl;
		cout<<"\t\t*            0----返        回               *"<<endl;
		cout<<"\t\t**********************************************"<<endl;
		cout<<"\t\t            请选择菜单号(0---8):              "<<endl;
		cin>>ch2;
		for(i=1;i<=L;i++)
			r[i].key=s[i].key;
		switch(ch2)
		{
		case '1':cout<<"请输入"<<L<<"个待排序数据(按回车分隔)"<<endl;
			for(i=1;i<=L;i++)
			{
				cin>>s[i].key;
				cout<<endl;
			}
			cout<<"排序数据已经输入完毕!"<<endl;
			break;
		case '2':insertsort();break;
		case '3':shellsort();break;
		case '4':bubblesort();break;
		case '5':cout<<"原始数据为(按回车开始排序)"<<endl;
			for(k=1;k<=L;k++)
				cout<<r[k].key<<" ";
			    cout<<endl;
			num=0;
			quicksort(1,L);
			cout<<"排序的最终结果是:"<<endl;
			for(k=1;k<=L;k++)
				cout<<r[k].key<<" ";
			    cout<<endl;
			break;
		case '6':selectsort();break;
		case '7':mergesort();break;
		case '8':heap();break;
		case '0':ch1='n';break;
		default:cout<<"输入错误!"<<endl;
		}
		if(ch2!='0')
		{if(ch2=='2'||ch2=='3'||ch2=='4'||ch2=='5'||ch2=='6'||ch2=='7'||ch2=='8')
		cout<<"排序输出完毕."<<endl;
		cout<<"按回车键返回."<<endl;
		q=getchar();
		if(q!='\xA')
		{
			getchar();
			ch1='n';
		}
		}
	}
}
void insertsort()
{
	int i,j,k,m=0;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
	for(i=2;i<=L;i++)
	{
		if(r[i].key<r[i-1].key)
		{
			r[0]=r[i];j=i-1;
			while(r[0].key<r[j].key)
			{
				r[j+1]=r[j];
				j--;
			}
			r[j+1]=r[0];
		}
		m++;
		cout<<"第"<<m<<"趟排序结果为(按回车继续):"<<endl;
		for(k=1;k<=L;k++)
			cout<<r[k].key<<" ";
		    cout<<endl;
	}
	cout<<"排序的最终结果是:"<<endl;
	for(i=1;i<=L;i++)
		cout<<r[i].key<<" ";
	    cout<<endl;
}
void shellsort()
{
	int i,j,gap,x,m=0,k;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
		gap=L/2;
	while(gap>0)
	{
		for(i=gap+1;i<=L;i++)
		{
			j=i-gap;
			while(j>0)
			{
				if(r[j].key>r[j+gap].key)
				{
					x=r[j].key;r[j].key=r[j+gap].key;
					r[j+gap].key=x;
					j=j-gap;
				}
				else
					j=0;
			}
		}
		gap=gap/2;
		m++;
		cout<<"第"<<m<<"趟排序结果为(按回车继续):"<<endl;
		for(k=1;k<=L;k++)
			cout<<r[k].key<<" ";
		    cout<<endl;
	}
	cout<<"排序的结果是:"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
}
void bubblesort()
{
	int i,j,k;
	int exchange;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
	for(i=1;i<L;i++)
	{
		exchange=falses;
		for(j=L;j>=i+1;j--)
			if(r[j].key<r[j-1].key)
			{
				r[0].key=r[j].key;
				r[j].key=r[j-1].key;
				r[j-1].key=r[0].key;
				exchange=ture;
			}
			if(exchange)
			{
				cout<<"第"<<i<<"趟排序结果为(按回车继续):"<<endl;
				for(k=1;k<=L;k++)
					cout<<r[k].key<<" ";
				    cout<<endl;
			}
	}
	cout<<"排序的最终结果是:"<<endl;
	for(i=1;i<=L;i++)
		cout<<r[i].key<<" ";
	    cout<<endl;
}
int partition(int i,int j)
{
	rectype pirot=r[i];
	while(i<j)
	{
		while(i<j&&r[j].key>=pirot.key)
			j--;
		if(i<j)
			r[i++]=r[j];
		while(i<j&&r[i].key<=pirot.key)
			i++;
		if(i<j)
			r[j--]=r[i];
	}
	r[i]=pirot;
	return i;
}
void quicksort(int low,int high)
{
	int pirotpos,k;
	if(low<high)
	{
		pirotpos=partition(low,high);
		num++;
		cout<<"第"<<num<<"趟排序结果为(按回车继续):"<<endl;
		for(k=1;k<=L;k++)
			cout<<r[k].key<<" ";
		    cout<<endl;
		quicksort(low,pirotpos-1);
		quicksort(pirotpos+1,high);
	}
}
void selectsort()
{
	int i,j,k,h;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
	for(i=1;i<L;i++)
	{
		h=i;
		for(j=i+1;j<=L;j++)
			if(r[j].key<r[h].key)
				h=j;
			if(h!=j)
			{
				r[0]=r[i];
				r[i]=r[h];
				r[h]=r[0];
			}
			cout<<"第"<<i<<"趟排序结果为(按回车继续):"<<endl;
			for(k=1;k<=L;k++)
				cout<<r[k].key<<" ";
			    cout<<endl;
	}
	cout<<"排序的最终结果是:"<<endl;
	for(i=1;i<=L;i++)
		cout<<r[i].key<<" ";
	    cout<<endl;
}
void merge(int low,int mm,int high)
{
	int i=low,j=mm+1,p=0;
	rectype *r1;
	r1=new rectype[high-low+1];
	if(!r1)
		cout<<"内存容量不够!"<<endl;
	while(i<=mm&&j<=high)
		r1[p++]=(r[i].key<=r[j].key)?r[i++]:r[j++];
	while(i<=mm)
		r1[p++]=r[i++];
	while(j<=high)
		r1[p++]=r[j++];
	for(p=0,i=low;i<=high;p++,i++)
		r[i]=r1[p];
}
void mergepass(int length)
{
	int i;
	for(i=1;i+2*length-1<=L;i=i+2*length)
		merge(i,i+length-1,i+2*length-1);
	if(i+length-1<L)
		merge(i,i+length-1,L);
}
void mergesort()
{
	int length,k,m=0;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
	for(length=1;length<L;length*=2)
	{
		mergepass(length);
		m++;
		cout<<"第"<<m<<"趟排序结果为(按回车继续):"<<endl;
		for(k=1;k<=L;k++)
			cout<<r[k].key<<" ";
		    cout<<endl;
	}
	cout<<"排序的最终结果是:"<<endl;
	for(k=1;k<=L;k++)
		cout<<r[k].key<<" ";
	    cout<<endl;
}
void createheap(int root,int index)
{
	int j,temp,finish;
	j=2*root;
	temp=r[root].key;
	finish=0;
	while(j<=index&&finish==0)
	{
		if(j<index)
			if(r[j].key<r[j+1].key)
				j++;
			if(temp>=r[j].key)
				finish=1;
			else
			{
				r[j/2].key=r[j].key;
				j=j*2;
			}
	}
	r[j/2].key=temp;
}
void heapsort()
{
	int i,j,temp,k;
	for(i=(L/2);i>=1;i--)
		createheap(i,L);
	for(i=L-1,k=1;i>=1;i--,k++)
	{
		temp=r[i+1].key;
		r[i+1].key=r[1].key;
		r[1].key=temp;
		createheap(1,i);
		cout<<"第"<<k<<"趟排序结果为(按回车继续):"<<endl;
		for(j=1;j<=L;j++)
			cout<<r[j].key<<" ";
		    cout<<endl;
	}
}
void heap()
{
	int i;
	cout<<"原始数据为(按回车开始排序):"<<endl;
	for(i=1;i<=L;i++)
		cout<<r[i].key<<" ";
	    cout<<endl;
	heapsort();
	cout<<"排序的最终结果是:"<<endl;
	for(i=1;i<=L;i++)
		cout<<r[i].key<<" ";
	    cout<<endl;
}
