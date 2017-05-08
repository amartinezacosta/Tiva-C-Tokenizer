#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE  16
#define MAX_TOKENS      5

uint8_t TokenizeString(const char *string, const char *delim, char tokens[MAX_TOKENS][MAX_TOKEN_SIZE]);

#endif /* TOKENIZER_H_ */
