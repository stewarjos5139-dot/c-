#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义状态码
#define OK 1
#define ERROR 0

// 定义单链表
typedef struct book {
    char name[50];
    char title[500];
    double time;
    struct book* next;
} book, *Linkbook;

// 声明函数
Linkbook qvZhi(Linkbook L, int i);                     // 取位置 i 的结点（返回指针）
Linkbook creatList(void);                              // 创建单链表（头结点）
Linkbook Listlnit(Linkbook L, int n);                 // 前插 n 个结点
Linkbook lnitList(Linkbook L, int n);                 // 后插 n 个结点
void printList(Linkbook L);                            // 打印链表（不输出头节点）
int chazhao(char* name, char* title, Linkbook L);     // 给值查找（名字, 标题，返回位置，找不到返回 ERROR）
int insertpoint(Linkbook L, int i);                   // 插入节点
int deletepoint(Linkbook L, int i);                   // 删除节点
int IfVoid(Linkbook L);                                // 判断链表是否为空
int destoryList(Linkbook L);                           // 销毁链表
int ClearList(Linkbook L);                             // 清空链表（保留头结点）
int lenlist(Linkbook L);                               // 求链表长度（不包括头结点）

// 主函数
int main() {
    // 创建并初始化链表（头结点）
    Linkbook a = creatList();
    a = lnitList(a, 2); // 后插 2 个节点

    strcpy(qvZhi(a, 2)->name, "hello world");
    qvZhi(a, 2)->time = 3.14;
    strcpy(qvZhi(a, 2)->title, "mengbaijiang");

    a = Listlnit(a, 3); // 前插 3 个节点
    printList(a);

    // 长度
    printf("链表长度为：%d\n", lenlist(a));

    // 查找
    int pos = chazhao("hello world", "", a);
    if (pos) {
        printf("查找到的位置为：%d\n", pos);
        printf("%s\n", qvZhi(a, pos)->title);
    } else {
        printf("未查找到该结点\n");
    }

    // 插入节点（在位置 3 前插一个新节点）
    insertpoint(a, 3);
    printList(a);

    // 销毁链表
    destoryList(a);
    return 0;
}

// 创建单链表（头结点）
Linkbook creatList(void) {
    Linkbook L = (Linkbook)malloc(sizeof(book));
    if (!L) return NULL;
    strcpy(L->name, "name");
    strcpy(L->title, "title");
    L->time = 0.0;
    L->next = NULL;
    return L;
}

// 后插 n 个节点
Linkbook lnitList(Linkbook L, int n) {
    Linkbook p = L;
    // 遍历到最后一个节点（p->next == NULL）
    while (p->next) { p = p->next; }
    for (int i = 0; i < n; i++) {
        p->next = creatList();
        p = p->next;
    }
    return L;
}

// 前插 n 个节点
Linkbook Listlnit(Linkbook L, int n) {
    for (int i = 0; i < n; i++) {
        Linkbook s = creatList();
        s->next = L->next;
        L->next = s;
    }
    return L;
}

// 插入节点（在第 i 个位置插入新节点，i 从 1 开始，插到末尾可用 len+1）
int insertpoint(Linkbook L, int i) {
    Linkbook p = qvZhi(L, i - 1);
    if (!p) {
        printf("插入位置不合法\n");
        return ERROR;
    }
    Linkbook s = creatList();
    s->next = p->next; // 顺序不可互换
    p->next = s;
    return OK;
}

// 删除第 i 个节点
int deletepoint(Linkbook L, int i) {
    Linkbook p = qvZhi(L, i - 1);
    if (!p) {
        printf("删除位置不合法\n");
        return ERROR;
    }
    Linkbook q = p->next;
    if (!q) {
        printf("删除位置不合法\n");
        return ERROR;
    }
    p->next = q->next;
    free(q);
    return OK;
}

// 判断链表是否为空（头结点不算）
int IfVoid(Linkbook L) {
    if (L->next == NULL)
        return OK;
    else
        return ERROR;
}

// 销毁链表（释放包括头结点）
int destoryList(Linkbook L) {
    Linkbook p;
    while (L) {
        p = L;
        L = L->next;
        free(p);
    }
    return OK;
}

// 清空链表（释放所有非头结点，保留头结点）
int ClearList(Linkbook L) {
    Linkbook p, q;
    p = L->next;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    L->next = NULL;
    return OK;
}

// 计算链表长度（不包括头结点）
int lenlist(Linkbook L) {
    int i = 0;
    Linkbook p = L->next;
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

// 取位置 i 的结点（返回指针，i=0 返回头结点）
Linkbook qvZhi(Linkbook L, int i) {
    if (i == 0) return L;
    int j = 1;
    int len = lenlist(L);
    if (i < 1 || i > len) {
        printf("位置不合法\n");
        return NULL;
    }
    Linkbook p = L->next;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 给值查找（按 name 或 title 查找，传入空字符串表示不比较该字段）
int chazhao(char* name, char* title, Linkbook L) {
    Linkbook p = L->next;
    int i = 1;
    while (p) {
        if ((name != NULL && name[0] != '\0' && strcmp(p->name, name) == 0) ||
            (title != NULL && title[0] != '\0' && strcmp(p->title, title) == 0)) {
            return i;
        }
        p = p->next;
        i++;
    }
    return ERROR;
}

// 打印链表
void printList(Linkbook L) {
    Linkbook p = L->next;
    while (p) {
        printf("name:%-15s title:%-15s time:%-15lf\n", p->name, p->title, p->time);
        p = p->next;
    }
}