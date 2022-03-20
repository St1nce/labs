#include <stdio.h>
char* testBracket(char *I, char closer) {
    for (; *I != '\0'; I++) {
        if (*I >= 'a' && *I <= 'z') continue;
        else if (*I >= 'A' && *I <= 'Z') continue;
        else if (*I >= '0' && *I <= '9') continue;
        else if (*I == closer) break;
        else if (*I == '(') {
            char *T = testBracket(I+1, ')');
            if (T == NULL) return NULL;
            else if (*T == '\0') return NULL;
            else I = T;
        }
        else if (*I == '[') {
            char *T = testBracket(I+1, ']');
            if (T == NULL) return NULL;
            else if (*T == '\0') return NULL;
            else I = T;
        }
        else if (*I == '{') {
            char *T = testBracket(I+1, '}');
            if (T == NULL) return NULL;
            else if (*T == '\0') return NULL;
            else I = T;
        }
        else return NULL;
    }
    return I;
}
int main() {
    char I[1000];
    scanf("%[^\n]", I);
    char* X = testBracket(I, '\n');
    if (X == NULL) printf("не работает(\n");
    else           printf("е, работает) %c\n", *X);
    return 0;
}
