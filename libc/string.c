#include "string.h"
#include "types.h"

void itoa(int n, char str[]) {
    int sign;

    if((sign = n) < 0) n = -n;

    int i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0) str[i++] = '-';
    str[i] = '\0';

    strrev(str);
}

int atoi(char *str) {
    int result = 0;

    int i;
    for(i = 0; str[i] != '\0'; i++) {
        result = result * 10 + str[i] - '0';
    }

    return result;
}

void htoa(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    sint32_t tmp;

    int i;
    for(i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;

        if(tmp == 0 && zeros == 0) continue;
        zeros = 1;

        if(tmp > 0xA) {
            append(str, tmp - 0xA + 'a');
        } else {
            append(str, tmp + '0');
        }
    }

    tmp = n & 0xF;

    if(tmp >= 0xA) {
        append(str, tmp - 0xA + 'a');
    } else {
        append(str, tmp + '0');
    }
}

void strrev(char s[]) {
    int c, j;

    int i;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i = 0;
    while(s[i] != '\0') i++;
    return i;
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len - 1] = '\0';
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int match(char s1[], char s2[]) { //how many characters match, before the first unmatching character
    int ret;
    for (int i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0' || s2[i] == '\0') return i - 1;
        ret = i;
    }
    if (strcmp(s1, s2) == 0) {
        return -2;
    }
    return ret;
}

char *strcpy(char *dest, const char *src) {
    unsigned i;

    for (i=0; src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }

    dest[i]= '\0';

    return dest;
}

const char* afterSpace(const char* input) {
    const char* starting = input;

    while (*starting != ' ') {
        starting++;
    }

    starting++;
    return starting;
}