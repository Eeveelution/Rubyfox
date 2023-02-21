#ifndef __KERNEL_STRING_H_
#define __KERNEL_STRING_H_

#include <stddef.h>

size_t strlen(const char* str);
unsigned char strncmp(const char* str1, const char* str2, unsigned int length);

#endif