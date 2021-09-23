#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;
int a[N], b[N];
int com, mov;   //比较次数,移动次数
int n = 1000;

//选择排序:每次从序列中选择一个最大的数放到最后面,重复执行
int findmaxpos(int arr[], int n)     // 找到最大值
{
    int pos = 1;
    for (int i = 2; i <= n; i++) {
        com++;
        if (arr[i] > arr[pos]) {
            pos = i;
        }
    }
    return pos;
}
void selection_sort(int arr[], int n) {
    while (n > 1)    //处理n个数
    {
        int pos = findmaxpos(arr, n);
        if (pos != n)mov++;
        int temp = arr[pos];
        arr[pos] = arr[n];
        arr[n] = temp;
        n--;
    }
}

//插入排序:假设前k个已经排好序,我们就可以找到新的数插进去
void insert(int arr[], int i)    //插入
{
    int key = arr[i];
    int j = i;
    while (j > 1 && arr[j - 1] > key) {
        com++;
        arr[j] = arr[j - 1];
        j--;
    }
    if (j != i)mov++;
    arr[j] = key;
}
void insert_sort(int arr[], int n)   //插入排序
{
    for (int i = 1; i <= n; i++)
        insert(arr, i);
}

//冒泡排序
void bubble(int arr[], int n)  //冒泡
{
    for (int i = 1; i < n; i++) {
        com++;
        if (arr[i] > arr[i + 1]) {
            mov++;
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}
void bubble_sort(int arr[], int n) //冒泡排序
{
    for (int i = 1; i < n; i++)
        bubble(arr, n);
}

//希尔排序
void shell_sort(int arr[], int n) {
    for (int ins = n >> 1; ins; ins >>= 1) {
        for (int i = ins; i < n; i++) {
            for (int j = i - ins + 1; ++com, j >= 1 && arr[j] > arr[j + ins]; j -= ins, mov++)
                swap(arr[j], arr[j + ins]);
        }
    }
}

//快速排序
void quick_sort(int arr[], int L, int R) {
    int pivot = arr[(L + R) >> 1];
    int i = L, j = R;
    while (i <= j) {
        while (arr[i] < pivot)i++, com++;
        while (arr[j] > pivot)j--, com++;
        if (i <= j)swap(arr[i++], arr[j--]), mov++;
    }
    if (L < j)quick_sort(arr, L, j);
    if (i < R)quick_sort(arr, i, R);
}

//堆排序
void heap_sort(int arr[], int n) {
    for (int i = 1; i <= n; i++) {
        int len = i;
        while (len != 1) {
            com++;
            if (arr[len] > arr[len >> 1])swap(arr[len], arr[len >> 1]), mov++;
            else break;
            len >>= 1;
        }
    }
    for (int i = n; i >= 1; i--) {
        mov++;
        swap(arr[i], arr[1]);
        int len = 1;
        while ((len << 1) < i) {
            int nex = len << 1;
            com++;
            if ((nex + 1 < i) && (arr[nex] < arr[nex + 1]))nex++;
            com++;
            if (arr[len] >= arr[nex])break;
            mov++;
            swap(arr[len], arr[nex]);
            len = nex;
        }
    }
}

int menu()    //菜单函数
{
    int choice;
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("~*-----------排序算法--------------*~\n");
    printf("~*          1.选择排序             *~\n");
    printf("~*          2.插入排序             *~\n");
    printf("~*          3.冒泡排序             *~\n");
    printf("~*          4.希尔排序             *~\n");
    printf("~*          5.快速排序             *~\n");
    printf("~*          6.堆排序               *~\n");
    printf("~*          0.退出                 *~\n");
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    printf("请输入选项:");
    scanf("%d", &choice);
    getchar();
    return choice;
}

void print() {
    printf("排序后的数组为:\n");
    for (int i = 1; i <= n; i++) {
        printf("%5d ", b[i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("比较次数为:%d次,移动次数为:%d次\n", com, mov);
}

int main() {
    ifstream infile;
    infile.open("C://Users//A//Desktop//data.txt");
    for (int i = 1; i <= n; i++)infile >> a[i];
    infile.close();
    int select, op;     //select代表菜单中选项，op代表函数内部的某些选项
    while (true) {
        com = 0;
        mov = 0;
        memcpy(b, a, sizeof(a));
        system("CLS");    //清屏函数
        select = menu();        //调用菜单函数
        if (select == 0)break;
        switch (select) {
            case 1:
                system("CLS");    //清屏函数
                selection_sort(b, n);    //选择排序
                print();
                break;
            case 2:
                system("CLS");    //清屏函数
                insert_sort(b, n);    //插入排序
                print();
                break;
            case 3:
                system("CLS");    //清屏函数
                bubble_sort(b, n);    //冒泡排序
                print();
                break;
            case 4:
                system("CLS");    //清屏函数
                shell_sort(b, n);    //希尔排序
                print();
                break;
            case 5:
                system("CLS");    //清屏函数
                quick_sort(b, 1, n);  //快速排序
                print();
                break;
            case 6:
                system("CLS");    //清屏函数
                heap_sort(b, n);   //堆排序
                print();
                break;
        }
        printf("请按Enter键继续\n");
        getchar();
    }
    return 0;
}

产生随机数函数

#include<bits/stdc++.h>

#define ll long long
#define random(a, b) ((a)+rand()%((b)-(a)+1))
using namespace std;

int main() {
    freopen("C://Users//A//Desktop//data.txt", "w", stdout);
    srand((unsigned) time(0));
    int n = 100;
    for (int i = 0; i < n; i++)
        printf("%d ", random(1, 1000000));
    printf("\n");
}
