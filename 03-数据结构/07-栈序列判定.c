#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);  
    int in[1000], out[1000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &out[i]);
    }
    int stack[1000];  
    int top = -1;     
    int i = 0;        
    int j = 0;        
    int count = 0;    
    while (i < n) {
        stack[++top] = in[i];  
        
        while (top != -1 && stack[top] == out[j]) {
            top--;  
            j++;    
            count++; 
        }
    }
    while (top != -1 && stack[top] == out[j]) {
        top--;
        j++;
        count++;
    }
    if (j == n) {
        printf("%d\n", count);
    } else {
        printf("0\n");
    }
    return 0;
}
