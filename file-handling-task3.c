#include <stdio.h>
#include <ctype.h>
#include <string.h>


char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};


int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[50];
    FILE *fp;
    int i, j = 0;

    
    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        if (isalnum(ch) || ch == '_') {
            buffer[j++] = ch;
        } else {
    
            if (j != 0) {
                buffer[j] = '\0';
                j = 0;

                if (isKeyword(buffer))
                    printf("[Keyword] %s\n", buffer);
                else
                    printf("[Identifier] %s\n", buffer);
            }

            
            if (ch == '+' || ch == '-' || ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '&' || ch == '|') {
                char next_ch = fgetc(fp);
                if ((ch == '+' && next_ch == '+') ||
                    (ch == '-' && next_ch == '-') ||
                    (ch == '=' && next_ch == '=') ||
                    (ch == '!' && next_ch == '=') ||
                    (ch == '<' && next_ch == '=') ||
                    (ch == '>' && next_ch == '=') ||
                    (ch == '&' && next_ch == '&') ||
                    (ch == '|' && next_ch == '|')) {
                    printf("[Operator] %c%c\n", ch, next_ch);
                } else {
                    if (next_ch != EOF) {
                        ungetc(next_ch, fp);
                    }
                    printf("[Operator] %c\n", ch);
                }
            }
            
            else if (ch == '*' || ch == '/' || ch == '%' ) {
                printf("[Operator] %c\n", ch);
            }
        }
    }

    fclose(fp);
    return 0;
}
