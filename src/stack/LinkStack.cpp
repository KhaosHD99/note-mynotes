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
        cout<<"\n\t\t ջԪ��Ϊ��"<<endl;   
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
		cout<<("\t\t                    �� ջ\n");
		cout<<("\t\t***********************************************")<<endl;
		cout<<("\t\t*          1----------��          ջ          *")<<endl;
		cout<<("\t\t*          2----------��          ջ          *")<<endl;
		cout<<("\t\t*          3----------��          ʾ          *")<<endl;
	    cout<<("\t\t*          4----------��  ��  ת  ��          *")<<endl;
	    cout<<("\t\t*          5----------��  ��  ��  ʽ          *")<<endl;
		cout<<("\t\t*          0----------��          ��          *")<<endl;
		cout<<("\t\t***********************************************")<<endl;
		cout<<("\n\t\t ��ѡ��˵���:  ");
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
              cout<<"\n\t\t �����ջԪ��:  "; 
              cin>>val;
              result = Push(s,val); 
              if(result==-1)
                cout<<"\n\t\t ��ջʧ��"<<endl; 
              else
                cout<<"\n\t\t ��ջ�ɹ�"<<endl; 
              system("pause");break;
        case 2:
              result = Pop(s); 
              if(result ==-1)
                cout<<"\n\t\t ջΪ��!!!"<<endl; 
              else
                cout<<"\n\t\t ��ջԪ��Ϊ��"<<result<<endl; 
              system("pause");break;
              
         case 3:
              result = ShowStack(s);
              if(result == -1)
                 cout<<"\n\t\t ջΪ��!!!"<<endl; 
              system("pause");break;
              
         case 0:i=0;break;   
         default:printf("\n\t\t invalid num!!!\n");system("pause");break;
      }
   }
  
}
