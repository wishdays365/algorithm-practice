#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

// 数组的顺序存储结构表示（基于书上第93页定义）
typedef struct {
    ElemType *base;   // 数组元素基地址
    int dim;          // 数组维数
    int *bounds;      // 各维长度数组
    int *constants;   // 各维常数因子（用于地址计算）
} Array;

/**
 * 基本操作1：构造数组
 * 初始化一个dim维数组，各维长度由bounds数组指定
 */
Status InitArray(Array *A, int dim, int *bounds) {
    if (dim < 1 || dim > 10) return ERROR;  // 维数范围检查
    if (!bounds) return ERROR;              // 边界数组为空检查
    
    A->dim = dim;
    
    // 分配并初始化各维长度数组
    A->bounds = (int *)malloc(dim * sizeof(int));
    if (!A->bounds) exit(OVERFLOW);
    
    // 计算总元素个数并检查各维长度
    int total = 1;
    for (int i = 0; i < dim; i++) {
        if (bounds[i] <= 0) {
            free(A->bounds);
            A->bounds = NULL;
            return ERROR;  // 维度长度必须为正
        }
        A->bounds[i] = bounds[i];
        total *= bounds[i];
    }
    
    // 分配数组元素存储空间
    if (total == 0) {
        A->base = NULL;
        A->constants = NULL;
        return OK;
    }
    
    A->base = (ElemType *)malloc(total * sizeof(ElemType));
    if (!A->base) {
        free(A->bounds);
        A->bounds = NULL;
        exit(OVERFLOW);
    }
    
    // 初始化数组元素为0
    for (int i = 0; i < total; i++) {
        A->base[i] = 0;
    }
    
    // 计算各维常数因子（用于地址映射）
    A->constants = (int *)malloc(dim * sizeof(int));
    if (!A->constants) {
        free(A->base);
        free(A->bounds);
        A->base = A->bounds = NULL;
        exit(OVERFLOW);
    }
    
    // 计算常数因子：constants[i] = bounds[i+1] * bounds[i+2] * ... * bounds[dim-1]
    A->constants[dim - 1] = 1;  // 最后一维常数因子为1
    for (int i = dim - 2; i >= 0; i--) {
        A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];
    }
    
    printf("数组构造成功：%d维数组，总元素个数：%d\n", dim, total);
    return OK;
}

/**
 * 基本操作2：销毁数组
 * 释放数组占用的所有内存空间
 */
Status DestroyArray(Array *A) {
    if (!A) return ERROR;
    
    if (A->base) {
        free(A->base);
        A->base = NULL;
    }
    if (A->bounds) {
        free(A->bounds);
        A->bounds = NULL;
    }
    if (A->constants) {
        free(A->constants);
        A->constants = NULL;
    }
    
    A->dim = 0;
    printf("数组销毁成功\n");
    return OK;
}

/**
 * 基本操作3：取数组元素值
 * 根据下标indices获取指定位置的元素值
 */
Status Value(Array A, ElemType *e, int *indices) {
    if (!e || !indices) return ERROR;
    
    // 检查下标合法性
    for (int i = 0; i < A.dim; i++) {
        if (indices[i] < 0 || indices[i] >= A.bounds[i]) {
            printf("错误：下标越界！第%d维下标%d超出范围[0, %d]\n", 
                   i + 1, indices[i], A.bounds[i] - 1);
            return ERROR;
        }
    }
    
    // 计算一维索引：使用行主序映射公式
    // LOC(i₁, i₂, ..., iₙ) = i₁ × c₁ + i₂ × c₂ + ... + iₙ × cₙ
    int index = 0;
    for (int i = 0; i < A.dim; i++) {
        index += indices[i] * A.constants[i];
    }
    
    *e = A.base[index];
    printf("获取元素值：A[");
    for (int i = 0; i < A.dim; i++) {
        printf("%d", indices[i]);
        if (i < A.dim - 1) printf(",");
    }
    printf("] = %d\n", *e);
    
    return OK;
}

/**
 * 基本操作4：给数组元素赋值
 * 根据下标indices设置指定位置的元素值
 */
Status Assign(Array *A, ElemType e, int *indices) {
    if (!A || !indices) return ERROR;
    
    // 检查下标合法性
    for (int i = 0; i < A->dim; i++) {
        if (indices[i] < 0 || indices[i] >= A->bounds[i]) {
            printf("错误：下标越界！第%d维下标%d超出范围[0, %d]\n", 
                   i + 1, indices[i], A->bounds[i] - 1);
            return ERROR;
        }
    }
    
    // 计算一维索引
    int index = 0;
    for (int i = 0; i < A->dim; i++) {
        index += indices[i] * A->constants[i];
    }
    
    A->base[index] = e;
    printf("设置元素值：A[");
    for (int i = 0; i < A->dim; i++) {
        printf("%d", indices[i]);
        if (i < A->dim - 1) printf(",");
    }
    printf("] = %d\n", e);
    
    return OK;
}

/**
 * 辅助函数：打印数组信息
 */
void PrintArrayInfo(Array A) {
    printf("\n=== 数组信息 ===\n");
    printf("维数: %d\n", A.dim);
    
    printf("各维长度: [");
    for (int i = 0; i < A.dim; i++) {
        printf("%d", A.bounds[i]);
        if (i < A.dim - 1) printf(", ");
    }
    printf("]\n");
    
    printf("常数因子: [");
    for (int i = 0; i < A.dim; i++) {
        printf("%d", A.constants[i]);
        if (i < A.dim - 1) printf(", ");
    }
    printf("]\n");
    
    int total = 1;
    for (int i = 0; i < A.dim; i++) {
        total *= A.bounds[i];
    }
    printf("总元素个数: %d\n", total);
}

// 主函数测试
int main() {
    Array A;
    ElemType value;
    
    printf("=== 数组顺序存储操作演示 ===\n\n");
    
    // 测试用例1：三维数组
    printf("测试用例1：三维数组 2×3×4\n");
    int bounds1[] = {2, 3, 4};
    
    // 1. 构造数组
    if (InitArray(&A, 3, bounds1) != OK) {
        printf("数组初始化失败！\n");
        return 1;
    }
    PrintArrayInfo(A);
    
    // 2. 给数组元素赋值
    int indices1[] = {1, 2, 3};
    if (Assign(&A, 100, indices1) != OK) {
        printf("赋值失败！\n");
        DestroyArray(&A);
        return 1;
    }
    
    int indices2[] = {0, 1, 2};
    Assign(&A, 50, indices2);
    
    // 3. 取数组元素值
    if (Value(A, &value, indices1) == OK) {
        printf("验证取值：%d\n", value);
    }
    
    Value(A, &value, indices2);
    
    // 4. 销毁数组
    DestroyArray(&A);
    
    printf("\n----------------------------------------\n");
    
    // 测试用例2：二维数组
    printf("测试用例2：二维数组 3×4\n");
    int bounds2[] = {3, 4};
    
    // 构造数组
    if (InitArray(&A, 2, bounds2) != OK) {
        printf("数组初始化失败！\n");
        return 1;
    }
    PrintArrayInfo(A);
    
    // 赋值操作
    int indices3[] = {2, 3};
    Assign(&A, 200, indices3);
    
    int indices4[] = {1, 1};
    Assign(&A, 150, indices4);
    
    // 取值操作
    Value(A, &value, indices3);
    Value(A, &value, indices4);
    
    // 测试错误情况：下标越界
    int indices5[] = {3, 2};  // 第一维越界
    Value(A, &value, indices5);
    
    // 销毁数组
    DestroyArray(&A);
    
    return 0;
}