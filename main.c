#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义状态码
#define OK 1
#define ERROR 0

//定义单链表
typedef struct book
{
    char name[50];
    char title[500];
    double time;
    struct book* next;
}book,*Linkbook;

//声明函数
Linkbook qvZhi(Linkbook L, int i);//取位置i的结点（返回指针）
Linkbook creatList(void);//创建单链表
Linkbook Listlnit(Linkbook L,int n);//把单链表上链接n个结点功能(前插)
Linkbook lnitList(Linkbook L,int n);//把单链表上链接n个结点功能(后插)
void printList(Linkbook L);//打印链表(不输出头节点)
int chazhao(char* name,char* title,Linkbook L);//给值查找(名字,标题,返回位置,找不到头结点)
int insertpoint(Linkbook L, int i);//定义插入节点功能
int deletepoint(Linkbook L, int i);//定义删除节点功能
int IfVoid(Linkbook L);//定义判断单链表是否为空功能
int destoryList(Linkbook L);//定义销毁单链表功能
int ClearList(Linkbook L);//定义清空单链表功能
int lenlist(Linkbook L);//定义求单链表长度功能(不包括头结点)

//主函数
int main(){
    //创建链表
    Linkbook a = creatList();
    //初始化链表，添加2个结点
    a = lnitList(a,2);
    
    strcpy(qvZhi(a,2)->name,"hello world");
    qvZhi(a,2)->time = 3.14;
    strcpy(qvZhi(a,2)->title,"mengbaijiang");
    
    //a = lnitList(a,2);//后插2个
    
    a = Listlnit(a,3);//前插3个
    printList(a);
    // printList(a);
    //长度
    printf("链表长度为：%d\n",lenlist(a));
    //查找
    int pos = chazhao("hello world", "", a);
    if(pos) {printf("查找到的位置为：%d\n",pos);
    printf("%s\n", qvZhi(a,pos)->title);}
    else printf("未查找到该结点\n");
    //插入节点
    insertpoint(a,3);
    printList(a);
    //清空链表
    destoryList(a);
    return 0;
}

//定义创建单链表功能
Linkbook creatList(void){
    Linkbook L = (Linkbook)malloc(sizeof(book));
    if (!L) return ERROR;  
    strcpy(L -> name, "name");
    strcpy(L -> title, "title");
    L -> time = 0.0;
    L -> next = NULL;
    return L;
}
//把单链表上链接n个结点功能(后插)
Linkbook lnitList(Linkbook L,int n){
    Linkbook p = L;
    while (p){p = p->next;}
    for(int i = 0; i < n; i++){
        p ->next = creatList();
        p = p -> next;
    }
    return L;
}
//把单链表上链接n个结点功能(前插)
Linkbook Listlnit(Linkbook L,int n){
    for(int i = 0;i<n;i++){
        Linkbook s = creatList();
        s -> next = L -> next;
        L -> next = s;
    }
    return L;
}
//定义插入节点功能
 int insertpoint(Linkbook L, int i){
    //让前一位的指针指向新节点
    Linkbook p = qvZhi(L,i - 1);
    if(!p) {
        printf("插入位置不合法\n");
        return ERROR;
    }
    Linkbook s = creatList();
    s -> next = p -> next;//顺序不可互换
    p -> next = s; 
    return OK;
}
//定义删除节点功能
int deletepoint(Linkbook L, int i){
    //让前一位的指针指向后一位
    Linkbook p = qvZhi(L,i - 1);
    if(!p) {
        printf("删除位置不合法\n");
        return ERROR;
    }
    Linkbook q = p -> next;
    if(!q){
        printf("删除位置不合法\n");
        return ERROR;
    }
    p -> next = q -> next;
    free(q);
    return OK;
}
//定义判断单链表是否为空功能
int IfVoid(Linkbook L){
    if(L -> next == NULL)
        return OK;
    else
        return ERROR;
}
//定义销毁单链表功能
int destoryList(Linkbook L){
    Linkbook p;
    while(L)
    {
        p = L;
        L = L -> next;
        free(p);
    }
    return OK;
}
//定义清空单链表功能
int ClearList(Linkbook L){
    Linkbook p,q;
    p = L -> next;
    while(p){
        q = p;
        p = p -> next;
        free(q);
    }
    L -> next = NULL;
    return OK;
}
//定义求单链表长度功能(不包括头结点)
int lenlist(Linkbook L){
    int i = 0;
    Linkbook p = L -> next;
    while(p){
        i++;
        p = p -> next;
    }
    return i;
}

//取位置i的结点（返回指针）
Linkbook qvZhi(Linkbook L, int i){
    if(i == 0) return L;
    int j = 1;
    int len = lenlist(L);
    if(i < 1 || i > len){
        printf("位置不合法\n");
        return NULL;
    }
    Linkbook p = L -> next;
    while(p && j < i){
        p = p -> next;
        j++;
    }
    return p;
}
//给值查找(名字,标题,返回位置,找不到头结点)
int chazhao(char* name,char* title,Linkbook L){
    Linkbook p = L -> next;
    int i = 1;
    while(p){
        if(strcmp(p -> name, name) == 0||strcmp(p -> title, title) == 0)
            return i;
            break;
        p = p -> next;
        i++;
    if(!p) return ERROR;
    }
}
//打印链表
void printList(Linkbook L){
    Linkbook p = L -> next;
    while(p){
        printf("name:%-15s title:%-15s time:%-15lf\n",p -> name,p -> title,p -> time);
        p = p -> next;
    }
}