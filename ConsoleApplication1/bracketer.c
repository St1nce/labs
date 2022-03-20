#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int checkBrackets(char I[], char stack[], int stackSize) {
    for (int i=0; i<stackSize; i++) stack[i]='\0';
    int s=-1;
    for (int i=0; I[i]!='\0' && s<stackSize-1; i++) {
        if      (I[i] == '(') stack[++s] = ')';
        else if (I[i] == '[') stack[++s] = ']';
        else if (I[i] == '{') stack[++s] = '}';
        else if (
            I[i] == ')' ||
            I[i] == ']' ||
            I[i] == '}'
        ) {
            if (s < 0) return 0;
            if (I[i] == stack[s]) stack[s--] = '\0';
            else return 0;
        }
    }
    return 1;
}
int main() {
    char I[5][200] = {
        "asdfghj",//1
        "cxdfgh(ab)vcfgh",//1
        "vfgyh[()]bvgh",//1
        "vg({[aa]yh}v)gh",//1
        "vgh([ja)]sjdb"//0
    };
    char stack[200];
    for (int i=0; i<5; i++) printf("%d - %s\n",checkBrackets(I[i], stack, 200),I[i]);
    return 0;
}
