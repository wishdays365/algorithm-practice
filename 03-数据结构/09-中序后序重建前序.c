#include <stdio.h>
#include <string.h>

// 存储前序遍历结果（全局变量方便递归修改）
char pre[100];
int pre_idx = 0;

// 递归构建前序遍历：参数为中序/后序序列，及当前子树在序列中的范围
void buildPre(char in[], char post[], int inS, int inE, int postS, int postE) {
    if (inS > inE) return; // 子树为空，直接返回
    
    // 后序遍历的最后一个元素是当前子树的根
    char root = post[postE];
    pre[pre_idx++] = root; // 前序遍历先记录根
    
    // 在中序序列中找到根的位置，分割左/右子树
    int rootPos = inS;
    while (rootPos <= inE && in[rootPos] != root) {
        rootPos++;
    }
    
    // 左子树的节点数量
    int leftLen = rootPos - inS;
    
    // 递归处理左子树
    buildPre(in, post, inS, rootPos - 1, postS, postS + leftLen - 1);
    // 递归处理右子树
    buildPre(in, post, rootPos + 1, inE, postS + leftLen, postE - 1);
}

int main() {
    char in[100], post[100];
    scanf("%s %s", in, post); // 读取中序、后序序列
    
    int len = strlen(in);
    pre_idx = 0;
    // 初始范围：中序[0, len-1]，后序[0, len-1]
    buildPre(in, post, 0, len - 1, 0, len - 1);
    
    pre[pre_idx] = '\0'; // 字符串结尾
    printf("%s\n", pre); // 输出前序序列
    return 0;
}
