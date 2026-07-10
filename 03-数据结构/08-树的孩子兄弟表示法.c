#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node* child;
    struct Node* sibling;
};

int ind = 0;

struct Node* createTree(char* s) {
    if (s[ind] == '#') {
        ind++;
        return NULL;
    }
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = s[ind++];
    node->child = createTree(s);
    node->sibling = createTree(s);
    return node;
}

void preOrder(struct Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preOrder(root->child);
    preOrder(root->sibling);
}

void postOrder(struct Node* root) {
    if (root == NULL) return;
    postOrder(root->child);
    printf("%c", root->data);
    postOrder(root->sibling);
}

int main() {
    char s[1000];
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    ind = 0;
    struct Node* root = createTree(s);
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    return 0;
}
