#ifndef __WS9_H__
#define __WS9_H__

#include <stddef.h> /* size_t */

#define WORD_SIZE sizeof(size_t)
#define BYTE char
#define BYTE_SIZE 8

void *Memset(void *s, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);
#endif /*__WS9__*/

