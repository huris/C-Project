#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;    //定义数据类型,可以根据需要进行其他类型的定义
typedef struct LNode      //定义链表结点
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/**
  创建链表函数
 */
LinkList creat() {
    int node_num;         //结点个数
    int i, x;
    LinkList head, p, Newnode;
    head = (LinkList) malloc(sizeof(LNode));  //产生一个头结点
    if (head == NULL)      //判断是否分配成功
    {
        printf("空间分配失败!\n");
        exit(-1);
    }
    p = head;       //令p初始为head
    printf("请输入结点个数:");
    scanf("%d", &node_num);
    for (i = 0; i < node_num; i++) {
        printf("请输入你要插入的元素:");
        scanf("%d", &x);
        Newnode = (LinkList) malloc(sizeof(LNode));
        if (Newnode == NULL)       //判断是否分配成功
        {
            printf("空间分配失败!\n");
            exit(-1);
        }
        Newnode->data = x;     //赋值数据
        p->next = Newnode;    //将新的结点连上链表
        p = Newnode;        //令p指向下一个结点
    }
    p->next = NULL;      //使最后一个结点的next为NULL
    printf("创建链表成功!\n");
    return head;
}

/**
  遍历链表函数
  */
void print(LinkList head) {
    LinkList p = head->next;  //令p等于头结点的下一个结点
    while (p != NULL)      //如果p不等于NULL,输出数值
    {
        printf("%d ", p->data);
        p = p->next;      //令p指向下一个结点
    }
    printf("\n");
}

/**
  链表元素置逆
  */
void reverse(LinkList head) {
    LinkList p, q;   //临时结点p,q
    p = head->next;   //首先令p等于head->next
    q = p->next;
    while (q != NULL)  //结点往前抛
    {
        p->next = q->next;
        q->next = head->next;
        head->next = q;
        q = p->next;
    }
}

/**
  删除偶数元素结点
  */
void del_even(LinkList head) {
    LinkList p, q;
    p = head;
    q = head->next;
    while (q != NULL) {
        if ((q->data) % 2 == 0)      //如果当前元素为偶数
        {
            p->next = q->next;    //令p的下一个结点为q的下一个结点
            free(q);        //释放q结点
            q = p->next;      //将q作为p的下一个结点
        } else            //如果是奇数,则继续遍历下一对数
        {
            q = q->next;
            p = p->next;
        }
    }
}

/**
  非递减有序链表中插入一个元素
  */
void insert(LinkList head) {
    int x;
    LinkList p, q, tmp;
    printf("请输入你要插入的元素:");
    scanf("%d", &x);
    tmp = (LinkList) malloc(sizeof(LNode));
    if (tmp == NULL)       //判断是否分配成功
    {
        printf("空间分配失败!\n");
        exit(-1);
    }
    tmp->data = x;
    tmp->next = NULL;
    p = head;
    q = head->next;
    while (q != NULL) {
        if (q->data > x)    //如果当前元素比x大,则将x插入
        {
            p->next = tmp;
            tmp->next = q;
            break;
        } else {
            p = p->next;
            q = q->next;
        }
    }
    if (q == NULL)  //如果所有元素都比x小,则把tmp插到最后面
    {
        p->next = tmp;
        tmp->next = NULL;
    }
    p = head->next;
}

/**
  生成一个元素插入,形成非递减有序链表
  */
LinkList ins1() {
    int node_num;
    int i;
    LinkList head;
    head = (LinkList) malloc(sizeof(LNode));
    head->next = NULL;
    if (head == NULL)      //判断是否分配成功
    {
        printf("空间分配失败!\n");
        exit(-1);
    }
    printf("请输入结点个数:");
    scanf("%d", &node_num);
    for (i = 0; i < node_num; i++) {
        insert(head);
    }
    return head;
}

/**
  产生两个非递减有序链表,
  然后合成一个非递增链表
  */
LinkList ins2() {
    int node_num1, node_num2;
    int i;
    LinkList head, head1, head2;
    LinkList p, q, r;
    head = (LinkList) malloc(sizeof(LNode));
    head1 = ins1();   //生成一个head1非递减有序链表
    head2 = ins1();   //生成一个head2非递减有序链表
    head->next = NULL;
    r = head;
    reverse(head1);     //将head1反转
    reverse(head2);     //将head2反转
    p = head1->next;
    q = head2->next;
    while (p != NULL || q != NULL) //将head1和head2元素放到head中
    {
        if (p == NULL) {
            r->next = q;
            q = q->next;
        } else if (q == NULL) {
            r->next = p;
            p = p->next;
        } else if (p->data < q->data) {
            r->next = q;
            q = q->next;
        } else {
            r->next = p;
            p = p->next;
        }
        r = r->next;
    }
    return head;
}

/**
  产生两个非递减有序链表,
  然后合成一个非递减链表
  */
LinkList ins3() {
    int node_num1, node_num2;
    int i;
    LinkList head, head1, head2;
    LinkList p, q, r;
    head = (LinkList) malloc(sizeof(LNode));
    head1 = ins1();   //生成一个head1非递减有序链表
    head2 = ins1();   //生成一个head2非递减有序链表
    head->next = NULL;
    r = head;
    p = head1->next;
    q = head2->next;
    while (p != NULL || q != NULL) //将head1和head2元素放到head中
    {
        if (p == NULL) {
            r->next = q;
            q = q->next;
        } else if (q == NULL) {
            r->next = p;
            p = p->next;
        } else if (p->data > q->data) {
            r->next = q;
            q = q->next;
        } else {
            r->next = p;
            p = p->next;
        }
        r = r->next;
    }
    return head;
}

/**
  将链表按照奇偶性分开形成两个链表
  */
void depart(LinkList head) {
    LinkList even, odd;  //even存放偶数链表,odd存放奇数链表
    LinkList p, q, r;
    even = (LinkList) malloc(sizeof(LNode));
    odd = (LinkList) malloc(sizeof(LNode));
    even->next = NULL;
    odd->next = NULL;
    p = head->next;
    q = even;
    r = odd;
    while (p != NULL)     //遍历原链表
    {
        if ((p->data) % 2 == 0)  //如果是偶数,则放到even链表中
        {
            q->next = p;
            q = q->next;
        } else        //否则,放到odd链表中
        {
            r->next = p;
            r = r->next;
        }
        p = p->next;
    }
    q->next = NULL;
    r->next = NULL;
    printf("链表中的偶数有:\n");   //输出偶数链表
    print(even);
    printf("链表中的奇数有:\n");   //输出奇数链表
    print(odd);
}

/**
  菜单
  */
int menu()        //菜单函数
{
    int choice;
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("~*-------动态链表的设计与应用------*~\n");
    printf("~*       1.创建链表                *~\n");
    printf("~*       2.输出链表                *~\n");
    printf("~*       3.链表元素置逆            *~\n");
    printf("~*       4.删除偶数元素结点        *~\n");
    printf("~*       5.非递减有序链表中插入元素*~\n");
    printf("~*       6.生成一个非递减有序链表  *~\n");
    printf("~*       7.生成两个非递减链表,     *~\n");
    printf("~*         合成一个非递增链表      *~\n");
    printf("~*       8.生成两个非递减链表,     *~\n");
    printf("~*         合成一个非递减链表      *~\n");
    printf("~*       9.将链表按照奇偶性分开    *~\n");
    printf("~*         形成两个链表            *~\n");
    printf("~*       0.退出                    *~\n");
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("请输入选项:");
    scanf("%d", &choice);
    return choice;
}

int main() {
    int select;
    LinkList head;
    while (true) {
        select = menu();
        if (select == 1) {
            system("CLS");
            head = creat();
        } else if (select == 2) {
            system("CLS");
            print(head);
        } else if (select == 3) {
            system("CLS");
            reverse(head);
        } else if (select == 4) {
            system("CLS");
            del_even(head);
        } else if (select == 5) {
            system("CLS");
            insert(head);
        } else if (select == 6) {
            system("CLS");
            head = ins1();
        } else if (select == 7) {
            system("CLS");
            head = ins2();
        } else if (select == 8) {
            system("CLS");
            head = ins3();
        } else if (select == 9) {
            system("CLS");
            depart(head);
        } else if (select == 0) {
            system("CLS");
            printf("欢迎使用,再见!\n");
            break;
        }
    }
}
