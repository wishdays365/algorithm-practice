#define listinitsize 100
#define listincrement 10
typedef int elemtype;
typedef struct {
    elemtype *elem;
    int len;
    int listsize;
}SqList;
int InitList(SqList *L)
{
    L->elem=(elemtype*)malloc(listinitsize*sizeof(elemtype));
    if(!L->elem) exit(0);
    L->len=0;
    L->listsize=listinitsize;
    return 1;
}
int Createlist(SqList *L,int n)
{
    int i;
    printf("输入%d个元素\n",n);
    for(i=0;i<n;i++)
   {
         scanf("%d",&L->elem[i]);
   }
   printf("\n");
   L->len=n;
   return 1;
}
int ListInsert(SqList *L,int i,elemtype e)
{
    int j;
    if(i<1||i>L->len+1) 
    {
        printf("插入失败\n");
        return 0;
    }
    if(L->len>=L->listsize)
    {  
        L->elem=(elemtype*)realloc(L->elem,(L->listsize+listincrement)*sizeof(elemtype));
        if(!L->elem) exit(0);
        L->listsize+=listincrement;
    }
    for(j=L->len-1;j>=i-1;j--)
    {
        L->elem[j+1]=L->elem[j];
    }
    L->elem[i-1]=e;
    L->len++;
    return 1;
}
int ListDelete(SqList *L,int i,elemtype *e)
{
    int j;
    *e=L->elem[i-1];
    if(i<1||i>L->len)
     {
        printf("删除失败\n");
        return 0;
    }
    
    else for(j=i;j<L->len;j++)
    {
        L->elem[j-1]=L->elem[j];
    }
    
    L->len--;
    return 1;
}
int ptintf(SqList *L)
{
    int i;
    if(L->len==0)  
    {
        printf("列表为空\n");
        return 0;
    }
    
    for(i=0;i<L->len;i++)
    {
        printf("%d ",L->elem[i]);

    }
    printf("\n");
    return 1;
}
int LocateElem(SqList *L,elemtype e)
{
    int i;
    if(L->len==0) return 0;
    for(i=0;i<L->len;i++)
    {   if(i>=L->len) 
        {
            printf("查找失败\n");
          return 0;
        }
       
        else if(L->elem[i]==e)
        {   
            printf("查找成功\n");
            printf("位置在第%d个\n",i+1);
            return i+1;
        }
    }
    return 0;
}
int Listorder(SqList *L)
{
    int i;
    int temp;
    if(L->len==0) return 0;
    for(int j=0;j<L->len-1;j++){
    for(i=j+1;i<=L->len-1;i++)
    {
        if(L->elem[j]>L->elem[i])
        {
            temp=L->elem[j];
            L->elem[j]=L->elem[i];
            L->elem[i]=temp;
        }
    }}
    return 1;
}
int hebing(SqList *A,SqList *B,SqList *C)
{
    C->elem=(elemtype*)malloc((A->len+B->len)*sizeof(elemtype));
    if(!C->elem) exit(0);
    C->len=A->len+B->len;
    C->listsize=A->len+B->len;
    for(int i=0;i<A->len+B->len;i++)
    {
        if(i<A->len)
        C->elem[i]=A->elem[i];
        else
        C->elem[i]=B->elem[i-A->len];
    }
}
int main()
{
    SqList *La,*Lb,*Lc;
    La=(SqList*)malloc(sizeof(SqList));
    Lb=(SqList*)malloc(sizeof(SqList));
    Lc=(SqList*)malloc(sizeof(SqList));
    InitList(La);
    Createlist(La,5);
    InitList(Lb);
    Createlist(Lb,5);
    InitList(Lc);
    // ListInsert(La,3,100);
    // elemtype e;
    // ListDelete(La,3,&e);
    // ptintf(La);
    // ptintf(Lb);
    // ptintf(Lc);
    // hebing(La,Lb,Lc);

    // Listorder(Lc);
    // ptintf(Lc);
    // int a;
    // printf("请输入要查找的元素\n");
    // scanf("%d",&a);
    // LocateElem(Lc,a);
    //     elemtype dd;
    //     ListDelete(Lc,6,&dd);
    //     printf("删除第六个元素\n");
    //     ptintf(Lc);
       
    //     printf("插入第四个元素\n");
    //     scanf("%d",&dd);
    //     ListInsert(Lc,4,dd);
    //     ptintf(Lc);
    
    ptintf(La);
    ptintf(Lb);
    hebing(La,Lb,Lc);
    printf("合并后的顺序表为:\n");
    ptintf(Lc);

    Listorder(La);
    printf("la排序后的顺序表为:\n");
    ptintf(La);

    Listorder(Lb);
    printf("lb排序后的顺序表为:\n");
    ptintf(Lb);
    printf("lc排序后的顺序表为:\n");
    Listorder(Lc);
    ptintf(Lc);
    free(La);
    free(Lb);
    free(Lc);
    return 0;
}
 