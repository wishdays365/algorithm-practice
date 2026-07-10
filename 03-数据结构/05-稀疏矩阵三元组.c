#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100  // 最大非零元素个数

typedef int ElemType;
typedef int Status;

// 三元组定义（存储非零元素的行、列、值）
typedef struct {
    int i, j;       // 行下标、列下标（从1开始）
    ElemType e;     // 元素值
} Triple;

// 稀疏矩阵的三元组顺序表存储结构
typedef struct {
    Triple data[MAXSIZE + 1];  // 存储三元组（下标从1开始使用）
    int mu, nu, tu;            // 矩阵的行数、列数、非零元素数
} TSMatrix;

// 改进后的创建稀疏矩阵函数 - 使用指针代替引用
Status CreateMatrix(TSMatrix *M, int mu, int nu) {
    if (mu <= 0 || nu <= 0) return ERROR;  // 行数和列数必须为正
    M->mu = mu;       // 初始化行数
    M->nu = nu;       // 初始化列数
    srand((unsigned)time(NULL));  // 初始化随机数种子
    
    // 随机生成非零元素个数（1~14，避免0个元素）
    M->tu = rand() % 14 + 1;
    
    // 标记已使用的位置，避免重复存储同一位置的元素
    int **used = (int**)malloc((mu + 1) * sizeof(int *));
    for (int i = 1; i <= mu; i++) {
        used[i] = (int *)calloc(nu + 1, sizeof(int));  // 初始化为0（未使用）
    }
    
    int k = 1;  // 三元组存储下标（从1开始）
    while (k <= M->tu) {
        // 随机生成行下标（1~mu）和列下标（1~nu）
        int i = rand() % mu + 1;
        int j = rand() % nu + 1;
        
        // 若该位置未使用且生成非零元素，则存储
        if (!used[i][j]) {
            ElemType e = rand() % 30;  // 随机生成0~29的元素值
            if (e != 0) {  // 只存储非零元素
                M->data[k].i = i;
                M->data[k].j = j;
                M->data[k].e = e;
                used[i][j] = 1;  // 标记为已使用
                k++;  // 存储下一个元素
            }
        }
    }
    
    // 释放标记数组
    for (int i = 1; i <= mu; i++) {
        free(used[i]);
    }
    free(used);
    return OK;
}

// 输出稀疏矩阵的三元组表
void print(TSMatrix M) {
    printf("行数mu=%d, 列数nu=%d, 非零元素数tu=%d\n", M.mu, M.nu, M.tu);
    for (int k = 1; k <= M.tu; k++) {
        printf("i=%d, j=%d, e=%d\n", M.data[k].i, M.data[k].j, M.data[k].e);
    }
}

// 基本转置算法：将M转置为T - 使用指针代替引用
Status TransposeSMatrix(TSMatrix M, TSMatrix *T) {
    T->mu = M.nu;  // 转置后行数 = 原矩阵列数
    T->nu = M.mu;  // 转置后列数 = 原矩阵行数
    T->tu = M.tu;  // 非零元素数不变
    
    if (T->tu > 0) {
        int q = 1;  // T的三元组存储下标（从1开始）
        // 按原矩阵的列序遍历，依次存储转置元素
        for (int col = 1; col <= M.nu; col++) {
            for (int p = 1; p <= M.tu; p++) {  // 遍历原矩阵所有非零元素
                if (M.data[p].j == col) {  // 找到属于当前列的元素
                    T->data[q].i = M.data[p].j;  // 行 = 原列
                    T->data[q].j = M.data[p].i;  // 列 = 原行
                    T->data[q].e = M.data[p].e;  // 元素值不变
                    q++;
                }
            }
        }
    }
    return OK;
}

// 快速转置算法：通过预处理加速转置 - 使用指针代替引用
Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T) {
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    
    if (T->tu > 0) {
        // num[col]：原矩阵第col列的非零元素个数
        int *num = (int *)malloc((M.nu + 1) * sizeof(int));
        // cpot[col]：原矩阵第col列第一个元素在T中的存储位置
        int *cpot = (int *)malloc((M.nu + 1) * sizeof(int));
        
        // 步骤1：统计每列的非零元素个数
        for (int col = 1; col <= M.nu; col++) {
            num[col] = 0;
        }
        for (int p = 1; p <= M.tu; p++) {
            int col = M.data[p].j;
            num[col]++;
        }
        
        // 步骤2：计算每列第一个元素在T中的位置
        cpot[1] = 1;
        for (int col = 2; col <= M.nu; col++) {
            cpot[col] = cpot[col - 1] + num[col - 1];
        }
        
        // 步骤3：直接放置转置元素（一次遍历完成）
        for (int p = 1; p <= M.tu; p++) {
            int col = M.data[p].j;  // 原元素的列
            int q = cpot[col];      // 转置后在T中的位置
            T->data[q].i = M.data[p].j;
            T->data[q].j = M.data[p].i;
            T->data[q].e = M.data[p].e;
            cpot[col]++;  // 更新该列下一个元素的位置
        }
        
        free(num);
        free(cpot);
    }
    return OK;
}

// 主函数测试
int main() {
    TSMatrix M, T1, T2;
    
    // 创建一个3行4列的稀疏矩阵M
    if (CreateMatrix(&M, 3, 4) != OK) {
        printf("创建矩阵M失败！\n");
        return 1;
    }
    
    // 输出原矩阵M
    printf("===== 原稀疏矩阵M =====\n");
    print(M);
    
    // 基本转置
    TransposeSMatrix(M, &T1);
    printf("\n===== 基本转置后的矩阵T1 =====\n");
    print(T1);
    
    // 快速转置
    FastTransposeSMatrix(M, &T2);
    printf("\n===== 快速转置后的矩阵T2 =====\n");
    print(T2);
    
    return 0;
}