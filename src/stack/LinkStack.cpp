#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define MAX 100
using namespace std;

typedef struct stacknode
{
   int data;
   struct stacknode *next;        
}stacknode;

typedef struct
{
   struct stacknode *top;   
}linkstack;

int Push(linkstack *s,int x)
{
     stacknode *p = new stacknode();
     if(p==NULL)
       return -1;
     else
       p->data = x;
       p->next = s->top;
       s->top = p;
       return 0;
}

int Pop(linkstack *s)
{
     stacknode *p = s->top;
     int data;
     if(p==NULL)
        return -1;
     else
     {
         data = p->data;
         s->top = p->next;   
         free(p);
         return data;
     } 
}

int ShowStack(linkstack *s)
{ 
     stacknode *p = s->top;
     if(p==NULL)
        return -1;
     else
     {
        cout<<"\n\t\t 栈元素为："<<endl;   
        while(p!=NULL)
        {
           cout<<"\n\t\t\t"<<p->data<<endl;
           p=p->next;        
        }
     }
}

int Convert()
{
       
}

void Option()
{
     system("cls");
		cout<<("\t\t                    链 栈\n");
		cout<<("\t\t***********************************************")<<endl;
		cout<<("\t\t*          1----------进          栈          *")<<endl;
		cout<<("\t\t*          2----------出          栈          *")<<endl;
		cout<<("\t\t*          3----------显          示          *")<<endl;
	    cout<<("\t\t*          4----------数  制  转  换          *")<<endl;
	    cout<<("\t\t*          5----------逆  波  兰  式          *")<<endl;
		cout<<("\t\t*          0----------返          回          *")<<endl;
		cout<<("\t\t***********************************************")<<endl;
		cout<<("\n\t\t 请选择菜单号:  ");
}

int main()
{
   int i=1;
   int choice = -1;
   int val;
   int result;
   linkstack *s = new linkstack();
   s->top = NULL;
   
   while(i)
   {
      Option();
      cin>>choice;
      
      switch(choice)
      {
         case 1:
              cout<<"\n\t\t 输入进栈元素:  "; 
              cin>>val;
              result = Push(s,val); 
              if(result==-1)
                cout<<"\n\t\t 进栈失败"<<endl; 
              else
                cout<<"\n\t\t 进栈成功"<<endl; 
              system("pause");break;
        case 2:
              result = Pop(s); 
              if(result ==-1)
                cout<<"\n\t\t 栈为空!!!"<<endl; 
              else
                cout<<"\n\t\t 出栈元素为："<<result<<endl; 
              system("pause");break;
              
         case 3:
              result = ShowStack(s);
              if(result == -1)
                 cout<<"\n\t\t 栈为空!!!"<<endl; 
              system("pause");break;
              
         case 0:i=0;break;   
         default:printf("\n\t\t invalid num!!!\n");system("pause");break;
      }
   }
  
}
