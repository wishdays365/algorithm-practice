#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 50
typedef int elemtype;
typedef struct {
    elemtype data[M];
    int len;
}SqList;
int InitList(SqList *L)
{
    (*L).len=0;
}
int Createlist(SqList *L,int n)
{
    int i;
    printf("输入%d个元素\n",n);
    for(i=0;i<n;i++)
   {
         scanf("%d",&L->data[i]);
   }
   printf("\n");
   L->len=n;
}
int ListEmpty(SqList *L)
{
    return(L->len==0);
}

int ListLLength(SqList *L)
{
    return(L->len);
}
int DistList(SqList *L)
{
    int i;
    if(L->len==0)  return 0;
    for(i=0;i<L->len;i++)
    {
        printf("%d ",L->data[i]);

    }
    printf("\n");

}
int GetElem(SqList *L,int i,elemtype *e)
{
if(i<1||i>L->len) return 0;
*e=L->data[i-1];
return 1;
}
int LocateElem(SqList *L,elemtype e)
{
    int i=1;
    while (i<=L->len&&L->data[i-1]!=e)i++;
    if(i<=L->len)
    {
        return i;
    }
    else return 0;
}
int Listinsert(SqList *L,int i,elemtype e)
{
    int j;
    if(i<1||i>L->len+1)return 0;
    for (j=L->len-1;j>=i-1;j--)
    {
        L->data[j+1]=L->data[j];
    }
    L->data[i-1]=e;
    ++L->len;
    return 1 ;
}

int ListDelete(SqList *L,int i,elemtype *e)
{
    int j;
    if(i<1||i>L->len)return 0;
    *e=L->data[i-1];
    for(j=i;j<L->len;j++)
    {
        L->data[j-1]=L->data[j];
    }
    --L->len;
    return 1;
}

int main()
{
    elemtype dd,a,b;
    SqList *L;
    char *ch;
    L=(SqList*)malloc(sizeof(SqList));
    InitList(L);

    if(ListEmpty(L)) printf("顺序表为空\n");

    printf("创建顺序表\n");
    Createlist(L,5);

    printf("输出顺序表所有元素!\n");
    DistList(L);

    printf("输出顺序表长度!\n");
    printf("%d\n",ListLLength(L));

    printf("判断顺序表是否为空!\n");
    if(ListEmpty(L)) printf("顺序表为空\n");
    else printf("顺序表不为空\n");

    printf("输出顺序表第3个元素!\n");
    GetElem(L,3,&dd);
    printf("%d\n",dd);

    printf("查找元素a:\n");
    scanf("%d",&a);
    b=LocateElem(L,a);
    if(b) printf("元素a的位置为:%d\n",b);
    else printf("元素a不存在\n");

    printf("插入元素b:\n");
    scanf("%d",&b);
    printf("在元素表第4个位置插入元素b:\n");
    Listinsert(L,4,b);
    printf("输出顺序表所有元素\n");
    DistList(L);

    printf("删除元素表第3个位置元素:\n");
    ListDelete(L,3,&dd);
    printf("删除的元素为:%d\n",dd);
    printf("输出顺序表所有元素\n");
    DistList(L);
    free(L);
}
