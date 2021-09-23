#include <stdio.h>
#include <stdlib.h>

const int N = 1e6 + 9;
typedef struct node {
    int coe;    //系数
    int index;  //指数
    struct node *next;
} node;
node *polynode_one;   //多项式A
node *polynode_two;   //多项式B
node *polynode_plus;  //多项式A+B

//多项式初始化
void Unary_polynomial_init(node *&polynode) {
    polynode = (node *) malloc(sizeof(node));
    polynode->coe = 0;    //令第一个头结点系数为0
    polynode->index = 0;  //令第一个头结点指数为0
    polynode->next = NULL;
}

//一元多项式输入
void Unary_polynomial_input(node *polynode, int coe) {
    int index;
    node *tempnode = NULL;    //初始化临时结点
    node *currentnode = polynode;     //将头结点赋值给当前结点
    while (coe != -9999)     //如果系数不为-9999,则继续输入多项式
    {
        scanf("%d", &index);
        if (coe != 0)   //如果系数为0时,相当于无关项,项数不用加1,将该项接到链表中
        {
            tempnode = (node *) malloc(sizeof(node));
            tempnode->coe = coe;
            tempnode->index = index;
            tempnode->next = NULL;
            currentnode->next = tempnode;
            currentnode = currentnode->next;      //当前结点要转移到下一结点
        }
        scanf("%d", &coe);
    }
}

//一元多项式加法
void Unary_polynomial_add(node *polynode_one, node *polynode_two, node *polynode_plus) {
    node *tempnode = NULL;
    node *current_one = polynode_one;   //第一个多项式的当前结点
    node *current_two = polynode_two;     //第二个多项式的当前结点
    node *current_plus = polynode_plus;   //和多项式的当前结点
    while (current_one && current_two)//先将两个多项式按照指数大小分配给和多项式
    {
        //每次分配都将指数大的那一项分给和多项式,如果指数大小相等,则将系数和跟指数分配给和多项式
        if (current_one->index > current_two->index) {
            tempnode = (node *) malloc(sizeof(node));
            tempnode->coe = current_one->coe;
            tempnode->index = current_one->index;
            tempnode->next = NULL;
            current_plus->next = tempnode;
            current_plus = current_plus->next;
            current_one = current_one->next;
        } else if (current_one->index < current_two->index) {
            tempnode = (node *) malloc(sizeof(node));
            tempnode->coe = current_two->coe;
            tempnode->index = current_two->index;
            tempnode->next = NULL;
            current_plus->next = tempnode;
            current_plus = current_plus->next;
            current_two = current_two->next;
        } else if (current_one->index == current_two->index) {
            int coe_sum = current_one->coe + current_two->coe;
            if (coe_sum != 0) {
                tempnode = (node *) malloc(sizeof(node));
                tempnode->coe = coe_sum;
                tempnode->index = current_two->index;
                tempnode->next = NULL;
                current_plus->next = tempnode;
                current_plus = current_plus->next;
            }
            current_one = current_one->next;
            current_two = current_two->next;
        }
    }
    while (current_one)    //如果分配完还有多项式,则继续分配给和多项式
    {
        tempnode = (node *) malloc(sizeof(node));
        tempnode->coe = current_one->coe;
        tempnode->index = current_one->index;
        tempnode->next = NULL;
        current_plus->next = tempnode;
        current_plus = current_plus->next;
        current_one = current_one->next;
    }
    while (current_two) {
        tempnode = (node *) malloc(sizeof(node));
        tempnode->coe = current_two->coe;
        tempnode->index = current_two->index;
        tempnode->next = NULL;
        current_plus->next = tempnode;
        current_plus = current_plus->next;
        current_two = current_two->next;
    }
}

//一元多项式输出
void Unary_polynomial_output(node *polynode) {
    int flag_one = 0;   //flag_one判断多项式是否只有一个数字0
    int flag_two = 0;    //flag_two判断当前是否为第一项
    node *currentnode = polynode; //将头结点赋值给当前结点
    while (polynode) {
        if (flag_two != 0 && polynode->coe > 0) //如果不为第一项且为正数,则输出'+'号
        {
            printf("+");
            flag_one = 1;     //表示已经有输入不为0了,因此令flag为1
        }
        if (polynode->index == 0 && polynode->coe != 0)//输出常数项
        {
            printf("%d", polynode->coe);
            flag_one = 1;         //表示已经有输入不为0了,因此令flag_one为1
        } else if (polynode->coe != 0)  //如果系数不为0
        {
            flag_one = 1;          //表示已经有输入不为0了,因此令flag_one为1
            if (polynode->coe == 1)     //如果系数为1,只需要输出一个'x'即可
                printf("x");
            else if (polynode->coe == -1) //如果系数为-1,只需要输出一个'-x'即可
                printf("-x");
            else                //其他情况下,输出系数和一个'x'
                printf("%dx", polynode->coe);
            if (polynode->index != 1)    //如果指数不为1,需要输出指数
                printf("^%d", polynode->index);
        }
        flag_two = 1;     //表明已处理完第一项
        polynode = polynode->next;    //处理下一项
        free(currentnode);      //释放内存
        currentnode = polynode;
    }
    if (flag_one)        //如果输入不为0,则输出一个换行
        printf("\n");
    else
        printf("0\n");  //如果输入为0,则输出0和一个换行
}

int main() {

    int coe;
    while (~scanf("%d", &coe))    //多组输入
    {
        Unary_polynomial_init(polynode_one);    //初始化第一个多项式
        Unary_polynomial_init(polynode_two);    //初始化第二个多项式
        Unary_polynomial_init(polynode_plus);   //初始化和多项式
        Unary_polynomial_input(polynode_one, coe);  //输入多项式A
        scanf("%d", &coe);   //输入多项式B的第一项系数
        Unary_polynomial_input(polynode_two, coe); //输入多项式B
        //将两个一元多项式相加
        Unary_polynomial_add(polynode_one, polynode_two, polynode_plus);
        //开始输出
        printf("A:");   //输出多项式A
        Unary_polynomial_output(polynode_one->next);
        printf("B:");   //输出多项式B
        Unary_polynomial_output(polynode_two->next);
        printf("A+B:");     //输出和多项式A+B
        Unary_polynomial_output(polynode_plus->next);
    }
    return 0;
}
