#include<stdio.h>
#include<stdlib.h>        //使用malloc函数以及exit函数
#include<string.h>

typedef struct COURSE     //记录各课程名称及其平均分的结构体
{
    char course_name[50];    //course_name代表该课程名称
    double course_ave;        //course_ave代表该课程的平均分
    char max_name[20];        //max_name代表该课程最高分的人名字
    double course_max;        //course_max该课程最高分
    int rank[5];            //学生优,良,中,及格,不及格的人数
} CLASS;
typedef struct course     //记录学生的课程名称和该课程分数的结构体
{
    char course_name[50];
    double course_score;
} COU;
typedef struct student     //记录学生信息的结构体
{
    int ID;                    //学生学号
    char name[20];                //学生姓名
    double ave;                    //学生平均分
    double sum;                    //学生总分
    COU course[20];                //学生考试各门课程情况
    struct student *next;        //next指针指向下一个结点
} STU;

int menu();     //菜单函数
STU *Creat_sutdent1(STU *head);      //从键盘中输入学生信息的函数
STU *Creat_sutdent2(STU *head);     //从文件中添加学生信息的函数
STU *Del_student1(STU *head);      //按学号删除学生信息的函数
STU *Del_student2(STU *head);      //按姓名删除学生信息的函数
STU *Insert_student1(STU *head);     //按学号插入学生信息的函数
STU *Insert_student2(STU *head);     //按姓名插入学生信息的函数
STU *Search_student1(STU *head);     //按学号查找学生信息的函数
STU *Search_student2(STU *head);     //按姓名查找学生信息的函数
void *Rank_student(STU *head);       //成绩排序函数
void BubbleSort1(STU *head, int score_num);      //按某门成绩冒泡排序函数
void BubbleSort2(STU *head);     //按总成绩冒泡排序函数
void print1(STU *head);     //显示学生信息到屏幕的函数
void print2(STU *head);        //显示学生信息到文件的函数
CLASS class_num[20];
int course_num;     //课程总数
int stu_num;     //学生总数

int main() {
    int select, op;     //select代表菜单中选项，op代表函数内部的某些选项
    STU *head;        //head头结点
    STU *p;            //函数中的临时结点
    head = NULL;        //head结点赋初值
    while (true) {
        system("CLS");    //清屏函数
        select = menu();        //调用菜单函数
        if (select == 0) break;
        switch (select) {
            case 1:
                system("CLS");    //清屏函数
                head = Creat_sutdent1(head);    //建立学生成绩系统
                break;
            case 2:
                system("CLS");    //清屏函数
                head = Creat_sutdent2(head);    //建立学生成绩系统
                break;
            case 3:
                system("CLS");    //清屏函数
                if (head == NULL) {  //如果成绩系统里没有学生信息,则提示用户先输入学生信息
                    printf("请先输入学生信息!\n");
                }
                else {
                    system("CLS");     //清屏函数
                    p = head->next;
                    print1(head);        //显示学生信息到屏幕
                }
                break;
            case 4:
                system("CLS");    //清屏函数
                if (head == NULL) {      //如果成绩系统里没有学生信息,则提示用户先输入学生信息
                    printf("请先输入学生信息!\n");
                }
                else {
                    system("CLS");     //清屏函数
                    p = head->next;
                    print2(head);        //显示学生信息到文件
                }
                break;
            case 5:
                system("CLS");    //清屏函数
                printf("请输入删除方式:\n");
                printf("1.按学号删除\n");
                printf("2.按姓名删除\n");
                scanf("%d", &op);
                if (op == 1){
                    head = Del_student1(head);     //按学号删除学生信息
                }
                else{
                    head = Del_student2(head);     //按姓名删除学生信息
                }
                break;
            case 6:
                system("CLS");    //清屏函数
                printf("请选择插入的方式:\n");
                printf("1.按学号插入\n");
                printf("2.按姓名插入\n");
                scanf("%d", &op);
                if (op == 1){
                    head = Insert_student1(head);     //按学号插入学生信息
                }
                else{
                    head = Insert_student2(head);     //按姓名插入学生信息
                }
                break;
            case 7:
                system("CLS");    //清屏函数
                printf("请选择查找的方式:\n");
                printf("1.按学号查找\n");
                printf("2.按姓名查找\n");
                scanf("%d", &op);
                if (op == 1){
                    head = Search_student1(head);     //按学号查找学生信息
                }
                else{
                    head = Search_student2(head);     //按姓名查找学生信息
                }
                break;
            case 8:
                system("CLS");    //清屏函数
                Rank_student(head);     //成绩排序函数
                break;
        }
        printf("请按Enter键继续\n");
        getchar();
    }
    return 0;
}

int menu()        //菜单函数
{
    int choice;
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("~*--------小型教务管理系统---------*~\n");
    printf("~*       1.从键盘添加学生信息      *~\n");
    printf("~*       2.从文件添加学生信息      *~\n");
    printf("~*       3.显示学生信息到屏幕      *~\n");
    printf("~*       4.显示学生信息到文件      *~\n");
    printf("~*       5.删除学生信息            *~\n");
    printf("~*       6.插入学生信息            *~\n");
    printf("~*       7.查找学生信息            *~\n");
    printf("~*       8.成绩排名                *~\n");
    printf("~*       0.退出                    *~\n");
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("请输入选项:");
    scanf("%d", &choice);
    getchar();
    return choice;
}

STU *Creat_sutdent1(STU *head)    //添加学生信息的函数
{
    STU *p1 = NULL;
    STU *p2 = NULL;
    int i, j, k;
    head = (STU *) malloc(sizeof(STU));
    p2 = head;
    printf("请先输入学生人数:");        //输入本次考试学生总人数
    scanf("%d", &stu_num);
    printf("请输入本次学生参加课程考试的数目:");    //输入本次考试课程总数
    scanf("%d", &course_num);
    getchar();
    printf("请输入本次各门课程考试的名称:\n");        //输入本次考试各课程名称
    for (i = 0; i < course_num; i++) {
        printf("第%d门课程:", i + 1);
        gets(class_num[i].course_name);
        class_num[i].course_ave = 0;        //初始化该课程的平均分
        class_num[i].course_max = 0;        //初始化该课程的最高分
        for (k = 0; k < 5; k++){
            class_num[i].rank[k] = 0;            //初始化该课程的各等级人数
        }
    }
    for (i = 0; i < stu_num; i++) {
        system("CLS");            //清屏函数
        p1 = (STU *) malloc(sizeof(STU));
        p2->next = p1;
        printf("请输入第%d个学生的信息:\n", i + 1);
        printf("学号:");
        scanf("%d", &p1->ID);
        printf("姓名:");
        getchar();
        gets(p1->name);
        p1->sum = 0;
        for (j = 0; j < course_num; j++) {
            printf("请输入%s成绩:", class_num[j].course_name);
            scanf("%lf", &p1->course[j].course_score);
            if (p1->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数加1
                class_num[j].rank[0]++;
            else if (p1->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数加1
                class_num[j].rank[1]++;
            else if (p1->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数加1
                class_num[j].rank[2]++;
            else if (p1->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数加1
                class_num[j].rank[3]++;
            else
                class_num[j].rank[4]++;                    //如果该学生该门成绩小于60分,则不及格的人数加1
            if (p1->course[j].course_score > class_num[j].course_max) {
                class_num[j].course_max = p1->course[j].course_score;
                strcpy(class_num[j].max_name, p1->name);
            }
            strcpy(p1->course[j].course_name, class_num[j].course_name);
            p1->sum += p1->course[j].course_score;
            class_num[j].course_ave += p1->course[j].course_score;

        }
        p1->ave = p1->sum / course_num;
        p2 = p1;
    }
    for (j = 0; j < course_num; j++) {
        class_num[j].course_ave /= stu_num;
    }
    p1->next = NULL;
    return head;
}

STU *Creat_sutdent2(STU *head)    //添加学生信息的函数
{
    FILE *fp;            //文件指针fp
    char file_name[100] = "\0";
    printf("请输入文件所在位置及名称\n");
    printf("(just like D:\\\\file.txt)\n");
    gets(file_name);    //读取一个指定的文本文件
    //如果文件无法正常打开，则fopen()函数返回NULL指针
    if ((fp = fopen(file_name, "r+")) == NULL) {
        printf("打开文件:%s 失败!!!\n", file_name);
        exit(0);        //exit(0)表示正常运行程序并退出程序
    }
    STU *p1 = NULL;
    STU *p2 = NULL;
    int i, j, k;
    head = (STU *) malloc(sizeof(STU));
    p2 = head;
    printf("请先输入学生人数:");        //输入本次考试学生总人数
    scanf("%d", &stu_num);
    printf("请输入本次学生参加课程考试的数目:");    //输入本次考试课程总数
    scanf("%d", &course_num);
    getchar();
    printf("请输入本次各门课程考试的名称:\n");        //输入本次考试各课程名称
    for (i = 0; i < course_num; i++) {
        printf("第%d门课程:", i + 1);
        gets(class_num[i].course_name);
        class_num[i].course_ave = 0;        //初始化该课程的平均分
        class_num[i].course_max = 0;        //初始化该课程的最高分
        for (k = 0; k < 5; k++) {
            class_num[i].rank[k] = 0;            //初始化该课程的各等级人数
        }
    }
    for (i = 0; i < stu_num; i++) {
        system("CLS");            //清屏函数
        p1 = (STU *) malloc(sizeof(STU));
        p2->next = p1;
        fscanf(fp, "%d", &p1->ID);
        fscanf(fp, "%s", p1->name);
        p1->sum = 0;
        for (j = 0; j < course_num; j++) {
            fscanf(fp, "%lf", &p1->course[j].course_score);
            if (p1->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数加1
                class_num[j].rank[0]++;
            else if (p1->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数加1
                class_num[j].rank[1]++;
            else if (p1->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数加1
                class_num[j].rank[2]++;
            else if (p1->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数加1
                class_num[j].rank[3]++;
            else
                class_num[j].rank[4]++;                    //如果该学生该门成绩小于60分,则不及格的人数加1
            //如果该学生该门成绩比最高分要高，则最高分为该学生
            if (p1->course[j].course_score > class_num[j].course_max) {
                class_num[j].course_max = p1->course[j].course_score;
                strcpy(class_num[j].max_name, p1->name);
            }
            strcpy(p1->course[j].course_name, class_num[j].course_name);
            p1->sum += p1->course[j].course_score;        //该学生当前总分加上此门课程分数
            class_num[j].course_ave += p1->course[j].course_score;    //该门课程平均分加上此学生该门成绩
        }
        p1->ave = p1->sum / course_num;        //计算该学生平均分
        p2 = p1;
    }
    for (j = 0; j < course_num; j++) {
        class_num[j].course_ave /= stu_num;        //计算所有课程的平均分
    }
    p1->next = NULL;
    fclose(fp);
    return head;
}

void print1(STU *head)            //显示学生信息到屏幕的函数
{
    STU *p;
    int j;
    int n = 9, i;
    p = head->next;
    printf("全体学生信息:\n");
    printf("---学号---------姓名-");
    for (j = 0; j < course_num; j++) {
        for (i = 0; i < n; i++)     //控制格式
            printf("-");
        printf("%s", class_num[j].course_name);
    }
    printf("---------总分--------平均分----");
    printf("\n");
    while (p != NULL)            //输出学生信息
    {
        printf("%11d", p->ID);
        printf("%10s", p->name);
        for (j = 0; j < course_num; j++){
            printf("%12.2lf", p->course[j].course_score);
        }
        printf("%13.2lf", p->sum);
        printf("%12.2lf", p->ave);
        p = p->next;
        printf("\n");
    }
    printf(" 各科平均分");            //输出各科平均分
    n = 17;     //控制格式
    for (j = 0; j < course_num; j++) {
        if (j > 0)     //控制格式
            n = 7;
        for (i = 0; i < n; i++)     //控制格式
            printf(" ");
        printf("%.2lf", class_num[j].course_ave);
    }
    printf("\n");
    printf("各科最高分:  ");
    for (j = 0; j < course_num; j++)        //输出各科最高分
    {
        printf("%s:%s(%.2lf)   ", class_num[j].course_name, class_num[j].max_name, class_num[j].course_max);
    }
    printf("\n");
    printf("各科各分数段人数情况:  \n");    //输出各科各分数段人数情况

    for (j = 0; j < course_num; j++) {
        int stu_pass = 0;
        for (int l = 0; l < 4; l++){
            stu_pass += class_num[j].rank[l];
        }
        printf("%s:     ", class_num[j].course_name);
        printf("优(%2d人)     良(%2d人)     ", class_num[j].rank[0], class_num[j].rank[1]);
        printf("中(%2d人)     及格(%2d人)     不及格(%2d人)     ", class_num[j].rank[2], class_num[j].rank[3],
               class_num[j].rank[4]);
        printf("总及格(%2d人)     及格率(%4.2lf%%)\n", stu_pass, stu_pass * 1.0 / stu_num * 100);
    }
}

void print2(STU *head)            //显示学生信息到文件的函数
{
    STU *p;
    FILE *fb;
    if ((fb = fopen("D:\\信息.txt", "w")) == NULL) {
        printf("打开文件: 信息.txt 失败!!!\n");
        exit(0);        //exit(0)表示正常运行程序并退出程序
    }
    int j;
    int n = 9, i;
    p = head->next;
    fprintf(fb, "全体学生信息:\n");
    fprintf(fb, "---学号---------姓名-");
    for (j = 0; j < course_num; j++) {
        for (i = 0; i < n; i++)     //控制格式
            fprintf(fb, "-");
        if (n < 9)     //控制格式
            n++;
        fprintf(fb, "%s", class_num[j].course_name);
    }
    fprintf(fb, "---------总分--------平均分----");
    fprintf(fb, "\n");
    while (p != NULL)                //输出学生信息
    {
        fprintf(fb, "%8d", p->ID);
        fprintf(fb, "%12s", p->name);
        for (j = 0; j < course_num; j++)
            fprintf(fb, "%13.2lf", p->course[j].course_score);
        fprintf(fb, "%13.2lf", p->sum);
        fprintf(fb, "%12.2lf", p->ave);
        p = p->next;
        fprintf(fb, "\n");
    }
    fprintf(fb, "各科平均分:  ");                //输出各科平均分
    for (j = 0; j < course_num; j++) {
        fprintf(fb, "%s(%.2lf)   ", class_num[j].course_name, class_num[j].course_ave);
    }
    fprintf(fb, "\n");
    fprintf(fb, "各科最高分:  ");                //输出各科最高分
    for (j = 0; j < course_num; j++) {
        fprintf(fb, "%s:%s(%.2lf)   ", class_num[j].course_name, class_num[j].max_name, class_num[j].course_max);
    }
    fprintf(fb, "\n");
    fprintf(fb, "各科各分数段人数情况:  \n");            //输出各科各分数段人数情况

    for (j = 0; j < course_num; j++) {
        int stu_pass = 0;
        for (int l = 0; l < 4; l++)
            stu_pass += class_num[j].rank[l];
        fprintf(fb, "%s:     ", class_num[j].course_name);
        fprintf(fb, "优(%2d人)     良(%2d人)     ", class_num[j].rank[0], class_num[j].rank[1]);
        fprintf(fb, "中(%2d人)     及格(%2d人)     不及格(%2d人)     ", class_num[j].rank[2], class_num[j].rank[3],
                class_num[j].rank[4]);
        fprintf(fb, "总及格(%2d人)     及格率(%4.2lf%%)\n", stu_pass, stu_pass * 1.0 / stu_num * 100);
    }
    fclose(fb);
}

STU *Del_student1(STU *head)     //按学号删除学生信息的函数
{
    struct student *p1;     //p1保存当前需要检查的节点的地址
    struct student *p2;     //p2保存当前检查过的节点的地址
    int ID;
    int j, op1 = 1;
    if (head == NULL)     //是空链表
    {
        printf("学生信息不存在!\n");
        return head;
    }
    while (op1) {
        printf("请输入要删除学生的学号:");
        scanf("%d", &ID);     //输入要删除学生的学号
        p1 = head;
        while (p1->ID != ID && p1->next != NULL)     //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
        {
            p2 = p1;     //保存当前节点的地址
            p1 = p1->next;     //后移一个节点
        }
        if (p1->ID == ID)     //找到了
        {
            if (p1 == head)      //如果要删除的节点是第一个节点
            {
                head = p1->next;     //头指针指向第一个节点的后一个节点，也就是第二个节点。这样第一个节点就不在链表中，即删除
            } else     //如果是其它节点，则让原来指向当前节点的指针，指向它的下一个节点，完成删除
            {
                p2->next = p1->next;
            }
            stu_num--;     //学生总数随之减一
            for (j = 0; j < course_num; j++)     //重新计算各门课程的平均分,最高分,各等级人数
            {
                if (strcmp(p1->name, class_num[j].max_name) == 0)        //如果删除的学生为某门课程的最高分
                {
                    class_num[j].course_max = 0;
                    STU *p2 = head;
                    while (p2->next != NULL)                        //重新寻找最高分的学生
                    {
                        if (p2->course[j].course_score > class_num[j].course_max) {
                            class_num[j].course_max = p2->course[j].course_score;
                            strcpy(class_num[j].max_name, p2->name);
                        }
                        p2 = p2->next;
                    }

                }
                if (p1->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数减1
                    class_num[j].rank[0]--;
                else if (p1->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数减1
                    class_num[j].rank[1]--;
                else if (p1->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数减1
                    class_num[j].rank[2]--;
                else if (p1->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数减1
                    class_num[j].rank[3]--;
                else
                    class_num[j].rank[4]--;                    //如果该学生该门成绩小于60分,则不及格的人数减1
                class_num[j].course_ave = class_num[j].course_ave * (stu_num + 1) - p1->course[j].course_score;
                class_num[j].course_ave = class_num[j].course_ave / stu_num;
            }
            printf("学生:%s(学号为%d)已经从该成绩管理系统中删除\n", p1->name, p1->ID);
            free(p1);     //释放当前节点
            p1 = NULL;
        } else     //没有找到，则输出学号不存在
        {
            printf("学号%d不存在", ID);
        }
        printf("是否还想继续删除?(若想继续删除则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }
    return head;
}

STU *Del_student2(STU *head)     //按姓名删除学生信息的函数
{
    struct student *p1;     //p1保存当前需要检查的节点的地址
    struct student *p2;     //p2保存当前检查过的节点的地址
    char name[20];
    int j, op1 = 1;
    if (head == NULL)     //是空链表
    {
        printf("链表建立失败!\n");
        return head;
    }
    while (op1) {
        printf("请输入要删除学生的姓名:");
        getchar();
        gets(name);     //输入要删除学生的姓名
        p1 = head;
        while (strcmp(p1->name, name) != 0 && p1->next != NULL)     //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
        {
            p2 = p1;     //保存当前节点的地址
            p1 = p1->next;     //后移一个节点
        }
        if (strcmp(p1->name, name) == 0)     //找到了
        {
            if (p1 == head)     //如果要删除的节点是第一个节点
            {
                head = p1->next;     //头指针指向第一个节点的后一个节点，也就是第二个节点。这样第一个节点就不在链表中，即删除
            } else     //如果是其它节点，则让原来指向当前节点的指针，指向它的下一个节点，完成删除
            {
                p2->next = p1->next;
            }
            stu_num--;     //学生总数随之减一
            for (j = 0; j < course_num; j++)     //重新计算各门课程的平均分,最高分,各等级人数
            {
                if (strcmp(p1->name, class_num[j].max_name) == 0)        //如果删除的学生为某门课程的最高分
                {
                    class_num[j].course_max = 0;
                    STU *p2 = head;
                    while (p2->next != NULL)                        //重新寻找最高分的学生
                    {
                        if (p2->course[j].course_score > class_num[j].course_max) {
                            class_num[j].course_max = p2->course[j].course_score;
                            strcpy(class_num[j].max_name, p2->name);
                        }
                        p2 = p2->next;
                    }

                }
                if (p1->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数减1
                    class_num[j].rank[0]--;
                else if (p1->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数减1
                    class_num[j].rank[1]--;
                else if (p1->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数减1
                    class_num[j].rank[2]--;
                else if (p1->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数减1
                    class_num[j].rank[3]--;
                else
                    class_num[j].rank[4]--;                    //如果该学生该门成绩小于60分,则不及格的人数减1
                class_num[j].course_ave = class_num[j].course_ave * (stu_num + 1) - p1->course[j].course_score;
                class_num[j].course_ave = class_num[j].course_ave / stu_num;
            }
            printf("学生:%s(学号为%d)已经从该成绩管理系统中删除\n", p1->name, p1->ID);
            free(p1);     //释放当前节点
            p1 = NULL;

        } else     //没有找到，则输出学号不存在
        {
            printf("姓名%s不存在", name);
        }
        printf("是否还想继续删除?(若想继续删除则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }
    return head;
}

STU *Insert_student1(STU *head)     //按学号插入学生信息的函数
{
    int ID, op, j, op1 = 1;
    while (op1) {
        STU *p1 = NULL, *p2 = NULL;     //p1保存当前需要检查的节点的地址
        STU *stu;
        stu = (STU *) malloc(sizeof(STU));
        printf("请输入要插入位置的学号:");
        scanf("%d", &ID);             //输入待插入位置的学号
        printf("你想插在该学号前面还是后面:");
        printf("1.前面:");
        printf("2.后面:");
        scanf("%d", &op);
        printf("请输入你想插入的学生的信息:\n");
        printf("学号:");
        scanf("%d", &stu->ID);
        getchar();
        printf("姓名:");
        gets(stu->name);
        stu->sum = 0;
        for (j = 0; j < course_num; j++)      //重新计算各门课程的平均分,最高分,各等级人数
        {
            printf("请输入%s分数:", class_num[j].course_name);
            scanf("%lf", &stu->course[j].course_score);
            strcpy(stu->course[j].course_name, class_num[j].course_name);
            stu->sum += stu->course[j].course_score;
            class_num[j].course_ave = class_num[j].course_ave * stu_num + stu->course[j].course_score;
            if (stu->course[j].course_score > class_num[j].course_max)        //如果新加入的学生该门成绩比之前最高成绩要高,则该学生为该门课程最高分
            {
                class_num[j].course_max = stu->course[j].course_score;
                strcpy(class_num[j].max_name, stu->name);
            }
            if (stu->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数加1
                class_num[j].rank[0]++;
            else if (stu->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数加1
                class_num[j].rank[1]++;
            else if (stu->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数加1
                class_num[j].rank[2]++;
            else if (stu->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数加1
                class_num[j].rank[3]++;
            else
                class_num[j].rank[4]++;                    //如果该学生该门成绩小于60分,则不及格的人数加1
        }
        stu->ave = stu->sum / course_num;
        stu_num++;     //学生人数随之加一
        for (j = 0; j < course_num; j++)
            class_num[j].course_ave /= stu_num;
        if (head == NULL)      //如果链表是空表，则直接插入
        {
            head = stu;
            stu->next = NULL;
        } else {
            p1 = head;
            while (p1->ID != ID && p1->next != NULL)     //p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找
            {
                p2 = p1;
                p1 = p1->next;     //后移一个节点
            }
            if (p1->ID == ID)      //找到了
            {
                if (op == 2)      //插入在后面
                {
                    stu->next = p1->next;      //显然stu的下一节点是原p1的next
                    p1->next = stu;      //插入后原p1的下一节点就是要插入的结点位置
                } else     //插入在前面
                {
                    stu->next = p1;
                    p2->next = stu;

                }

            } else                    //如果没找到该位置的学号,则询问是否插在最后一个
            {
                printf("没找到该位置的学号\n");
                printf("是否需要将该学生插入到最后一个？(是则输入1，否则输入0)\n");
                int op1;
                scanf("%d", &op1);
                if (op1) {
                    p1->next = stu;
                    stu->next = NULL;
                }

            }

        }
        printf("是否还想继续插入?(若想继续插入则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }

    return head;
}

STU *Insert_student2(STU *head)     //按姓名插入学生信息的函数
{
    int op, j, op1 = 1;
    while (op1) {
        STU *p1 = NULL, *p2 = NULL;     //p1保存当前需要检查的节点的地址
        STU *stu;
        stu = (STU *) malloc(sizeof(STU));
        printf("请输入要插入位置的姓名:");
        char name[20];
        getchar();
        gets(name);     //输入待插入位置的姓名
        printf("你想插在该姓名前面还是后面:");
        printf("1.前面:");
        printf("2.后面:");
        scanf("%d", &op);
        printf("请输入你想插入的学生的信息:\n");
        printf("学号:");
        scanf("%d", &stu->ID);
        getchar();
        printf("姓名:");
        gets(stu->name);
        stu->sum = 0;
        for (j = 0; j < course_num; j++)      //重新计算各门课程的平均分,最高分,各等级人数
        {
            printf("请输入%s分数:", class_num[j].course_name);
            scanf("%lf", &stu->course[j].course_score);
            strcpy(stu->course[j].course_name, class_num[j].course_name);
            stu->sum += stu->course[j].course_score;
            class_num[j].course_ave = class_num[j].course_ave * stu_num + stu->course[j].course_score;
            if (stu->course[j].course_score > class_num[j].course_max)        //如果新加入的学生该门成绩比之前最高成绩要高,则该学生为该门课程最高分
            {
                class_num[j].course_max = stu->course[j].course_score;
                strcpy(class_num[j].max_name, stu->name);
            }
            if (stu->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数加1
                class_num[j].rank[0]++;
            else if (stu->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数加1
                class_num[j].rank[1]++;
            else if (stu->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数加1
                class_num[j].rank[2]++;
            else if (stu->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数加1
                class_num[j].rank[3]++;
            else
                class_num[j].rank[4]++;                    //如果该学生该门成绩小于60分,则不及格的人数加1
        }
        stu->ave = stu->sum / course_num;
        stu_num++;     //学生人数随之加一
        for (j = 0; j < course_num; j++)
            class_num[j].course_ave /= stu_num;
        if (head == NULL)                  //如果链表是空表，则直接插入
        {
            head = stu;
            stu->next = NULL;
        } else {
            p1 = head;
            while (strcmp(p1->name, name) != 0 && p1->next != NULL)      //p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找
            {
                p2 = p1;
                p1 = p1->next;                //后移一个节点
            }
            if (strcmp(p1->name, name) == 0)      //找到了
            {
                if (op == 2) {
                    stu->next = p1->next;     //显然stu的下一节点是原p1的next
                    p1->next = stu;            //插入后，原p1的下一节点就是要插入的结点位置
                } else {
                    stu->next = p1;
                    p2->next = stu;

                }

            } else {

                printf("没找到该位置的姓名\n");                    //若没找到,则询问是否插入到最后面
                printf("是否需要将该学生插入到最后一个?(是则输入1，否则输入0)\n");
                int op1;
                scanf("%d", &op1);
                if (op1) {
                    p1->next = stu;
                    stu->next = NULL;
                }

            }
        }
        printf("是否还想继续插入?(若想继续插入则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }

    return head;
}

STU *Search_student1(STU *head)     //按学号查找学生信息的函数
{
    int ID, j = 0, op1 = 1;
    while (op1) {
        STU *p;
        p = head;
        printf("请输入要查找的学号:");
        scanf("%d", &ID);      //输入要查找的学号
        while (p->ID != ID && p->next != NULL)     //p指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
        {
            p = p->next;     //后移一个节点
        }
        if (p->ID == ID)     //找到了并显示该学生的基本信息
        {
            printf("以下是该学生的基本信息:\n");
            printf("学号:%d\n", p->ID);
            printf("姓名:%s\n", p->name);
            printf("以下是本次考试情况:\n");
            for (j = 0; j < course_num; j++)
                printf("%s成绩:%.2lf\n", class_num[j].course_name, p->course[j].course_score);
            printf("平均分:%.2lf\n", p->ave);
            printf("总分:%.2lf\n", p->sum);
            printf("是否要修改该考生的成绩(如需修改则输入1,否则输入0)");
            int op1;
            scanf("%d", &op1);
            while (op1)     //实现学生信息修改的功能
            {
                getchar();
                char cou_name[50];
                double score;
                printf("请输入要修改的课程名称:\n");
                gets(cou_name);
                printf("修改的分数:\n");
                scanf("%lf", &score);
                for (j = 0; j < course_num; j++)     //重新计算各门课程的平均分,最高分,各等级人数
                {
                    if (strcmp(class_num[j].course_name, cou_name) == 0) {
                        class_num[j].course_ave = class_num[j].course_ave * stu_num - p->course[j].course_score + score;
                        class_num[j].course_ave = class_num[j].course_ave / stu_num;
                        break;
                    }
                }
                if (p->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数减1
                    class_num[j].rank[0]--;
                else if (p->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数减1
                    class_num[j].rank[1]--;
                else if (p->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数减1
                    class_num[j].rank[2]--;
                else if (p->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数减1
                    class_num[j].rank[3]--;
                else
                    class_num[j].rank[4]--;                    //如果该学生该门成绩小于60分,则不及格的人数减1
                if (score >= 90)                                //如果该门成绩修改后大于等于90分,则优的人数加1
                    class_num[j].rank[0]++;
                else if (score >= 80)                            //如果该门成绩修改后大于等于80分,则良的人数加1
                    class_num[j].rank[1]++;
                else if (score >= 70)                            //如果该门成绩修改后大于等于70分,则中的人数加1
                    class_num[j].rank[2]++;
                else if (score >= 60)                            //如果该门成绩修改后大于等于60分,则及格的人数加1
                    class_num[j].rank[3]++;
                else
                    class_num[j].rank[4]++;                    //如果该门成绩修改后小于60分,则不及格的人数加1
                if (score > class_num[j].course_max)        //如果该门成绩修改后比之前最高成绩要高,则该学生为该门课程最高分
                {
                    class_num[j].course_max = p->course[j].course_score;
                    strcpy(class_num[j].max_name, p->name);

                }
                p->course[j].course_score = score;
                printf("是否要还需修改该考生的其他成绩(如需修改则输入1,否则输入0)");
                scanf("%d", &op1);
            }
        } else
            printf("该学生不在成绩管理系统内\n");    //没找到

        printf("是否还想继续查找?(若想继续查找则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }

    return head;
}

STU *Search_student2(STU *head)     //按姓名查找学生信息的函数
{
    int j = 0, op1 = 1;
    char name[20];
    while (op1) {
        STU *p;
        p = head;
        printf("请输入要查找的姓名:");
        getchar();
        gets(name);     //输入要查找的姓名
        while (strcmp(p->name, name) != 0 && p->next != NULL)     //p指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
        {
            p = p->next;     //后移一个节点
        }
        if (strcmp(p->name, name) == 0)     //找到了并显示该学生的基本信息
        {
            printf("以下是该学生的基本信息:\n");
            printf("学号:%d\n", p->ID);
            printf("姓名:%s\n", p->name);
            printf("以下是本次考试情况:\n");
            for (j = 0; j < course_num; j++)
                printf("%s成绩:%.2lf\n", class_num[j].course_name, p->course[j].course_score);
            printf("平均分:%.2lf\n", p->ave);
            printf("总分:%.2lf\n", p->sum);
            printf("是否要修改该考生的成绩(如需修改则输入1,否则输入0)");
            int op1;
            scanf("%d", &op1);
            while (op1)     //实现学生信息修改的功能
            {
                getchar();
                char cou_name[50];
                double score;
                printf("请输入要修改的课程名称:\n");
                gets(cou_name);
                printf("修改的分数:\n");
                scanf("%lf", &score);
                for (j = 0; j < course_num; j++)     //重新计算各门课程的平均分
                {
                    if (strcmp(class_num[j].course_name, cou_name) == 0) {
                        class_num[j].course_ave = class_num[j].course_ave * stu_num - p->course[j].course_score + score;
                        class_num[j].course_ave = class_num[j].course_ave / stu_num;
                        break;
                    }
                }
                if (p->course[j].course_score >= 90)            //如果该学生该门成绩大于等于90分,则优的人数减1
                    class_num[j].rank[0]--;
                else if (p->course[j].course_score >= 80)        //如果该学生该门成绩大于等于80分,则良的人数减1
                    class_num[j].rank[1]--;
                else if (p->course[j].course_score >= 70)        //如果该学生该门成绩大于等于70分,则中的人数减1
                    class_num[j].rank[2]--;
                else if (p->course[j].course_score >= 60)        //如果该学生该门成绩大于等于60分,则及格的人数减1
                    class_num[j].rank[3]--;
                else
                    class_num[j].rank[4]--;                    //如果该学生该门成绩小于60分,则不及格的人数减1
                if (score >= 90)                                //如果该门成绩修改后大于等于90分,则优的人数加1
                    class_num[j].rank[0]++;
                else if (score >= 80)                            //如果该门成绩修改后大于等于80分,则良的人数加1
                    class_num[j].rank[1]++;
                else if (score >= 70)                            //如果该门成绩修改后大于等于70分,则中的人数加1
                    class_num[j].rank[2]++;
                else if (score >= 60)                            //如果该门成绩修改后大于等于60分,则及格的人数加1
                    class_num[j].rank[3]++;
                else
                    class_num[j].rank[4]++;                    //如果该门成绩修改后小于60分,则不及格的人数加1
                if (score > class_num[j].course_max)        //如果该门成绩修改后比之前最高成绩要高,则该学生为该门课程最高分
                {
                    class_num[j].course_max = p->course[j].course_score;
                    strcpy(class_num[j].max_name, p->name);
                }
                p->course[j].course_score = score;
                printf("是否要还需修改该考生的其他成绩(如需修改则输入1,否则输入0)");
                scanf("%d", &op1);
            }
        } else
            printf("该学生不在成绩管理系统内\n");    //没找到
        printf("是否还想继续查找?(若想继续查找则输入1,否则输入0)");
        scanf("%d", &op1);
        system("CLS");    //清屏函数
    }

    return head;
}

void *Rank_student(STU *head)     //成绩排序函数
{
    char cou_name[50];
    int j, op1;
    printf("请输入想要的排名方式\n");     //选择排名方式
    printf("1.单科成绩排名\n");
    printf("2.总成绩排名\n");
    scanf("%d", &op1);
    getchar();
    if (op1 == 1) {
        printf("请输入要排名的课程名称:");
        gets(cou_name);
        for (j = 0; j < course_num; j++)      //寻找课程名称所在的下标
            if (strcmp(cou_name, class_num[j].course_name) == 0)
                break;
        BubbleSort1(head, j);
    } else
        BubbleSort2(head);
    return head;
}

void BubbleSort1(STU *head, int score_num)     //按某门成绩排序的函数
{
    STU *p, *prep, *temp, *tail;
    tail = NULL;
    while (head->next != tail) {
        prep = head;
        p = head->next;
        while (p->next != tail) {
            if (p->course[score_num].course_score < p->next->course[score_num].course_score) {
                temp = p->next;
                prep->next = p->next;
                p->next = p->next->next;
                prep->next->next = p;
                p = temp;
            }
            p = p->next;
            prep = prep->next;
        }
        tail = p;
    }
}

void BubbleSort2(STU *head)     //按总成绩排序的函数
{
    STU *p, *prep, *temp, *tail;
    tail = NULL;
    while (head->next != tail) {
        prep = head;
        p = head->next;
        while (p->next != tail) {
            if (p->sum < p->next->sum) {
                temp = p->next;
                prep->next = p->next;
                p->next = p->next->next;
                prep->next->next = p;
                p = temp;
            }
            p = p->next;
            prep = prep->next;
        }
        tail = p;
    }
}
