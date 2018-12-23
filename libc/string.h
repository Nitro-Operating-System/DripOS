#ifndef STRING_H
#define STRING_H

void itoa(int n, char str[]);
int atoi(char *str);
void htoa(int n, char str[]);

void strrev(char s[]);

int strlen(char s[]);

void backspace(char s[]);

void append(char s[], char n);

int strcmp(char s1[], char s2[]);
int match(char s1[], char s2[]);

char *strcpy(char *dest, const char *src);
const char *afterSpace(const char* input);

#endif //STRING_H
