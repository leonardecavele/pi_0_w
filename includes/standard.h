#ifndef STANDARD_H
#define STANDARD_H

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

typedef unsigned int uint_t;

uint32_t strlen(const uint8_t *s);
int strcmp(const uint8_t *s1, const uint8_t *s2);
int strncmp(const uint8_t *s1, const uint8_t *s2, uint32_t len);
void *memset(void *s, int c, uint32_t n);

#endif
