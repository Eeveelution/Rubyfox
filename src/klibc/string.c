#ifndef __STRING_C_
#define __STRING_C_

#include <stddef.h>

size_t strlen(const char* str) {
    size_t length = 0;

    while(str[length]) {
        length++;
    }

    return length;
}

unsigned char strncmp(const char* str1, const char* str2, unsigned int length) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 != len2) {
        return 0;
    }

    for(unsigned int i = 0; i != length; i++) {
        if(str1[i] != str2[i]) {
            return 0;
        }

        if(str1[i] == 0) {
            return 1;
        }
    }

    return 1;
}

#endif