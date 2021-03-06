#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int r[5] = {10,5,9,6,7};
int num = 0;

int Partition(int i,int j)
{
   int temp = r[i];
   
   
   while(i < j && r[j] >= temp)
      j--;
   if(i < j)
   {
      r[i] = r[j];
      i++;
   }
   
   while(i < j && r[i] < temp)
      i++;
   if(i < j)
   {
      r[j] = r[i];
      j++;
   }  
   
   r[i] = temp;
   return i;   
}

void QuickSort(int low,int high)
{
   int pos,k;
   if(low < high)
   {
      pos = Partition(low,high);
      num++;
      printf("��%d��������Ϊ\n",num);
      for(k=0;k<5;k++)
         cout << r[k] <<endl;
      getchar();
      QuickSort(low,pos - 1);
      QuickSort(pos + 1,high);      
   }
}

int main()
{
   int i = 0;
   cout << "The source list is: " << endl;
   for(i = 0;i < 5;i++)
      cout << r[i] << endl;
   getchar();
   QuickSort(0,4);  
}
