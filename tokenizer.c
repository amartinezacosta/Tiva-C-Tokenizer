#include "tokenizer.h"

static bool IS_IN(const char c, const char *string){
    while(*string){
        if(c == *string){ return true; }
        string++;
    }

    return false;
}

static bool IS_DELIM(const char c, const char *delim){
    if(IS_IN(c, delim) || c == ' ' || c == '\n' || c == '\r' || c == '\0'){
        return true;
    }

    return false;
}

static bool IS_WHITE(const char c){
    if(c == ' '){
        return true;
    }

    return false;
}


static bool GetToken(const char *string, const char *delim, char *token, uint8_t *count){
    char *temp = (char*)string;

    while(IS_WHITE(*temp)){
        temp++;
    }

    if(IS_IN(*temp, delim)){
        temp++;
        while(!IS_DELIM(*temp, delim)){
            temp++;
        }
    }

    *count = temp - string;
    if(*count > MAX_TOKEN_SIZE){
        return true;
    }
    memcpy(token, string, *count);

    return false;
}


uint8_t TokenizeString(const char *string, const char *delim, char tokens[MAX_TOKENS][MAX_TOKEN_SIZE]){
    uint8_t i = 0;
    uint8_t count;
    char token[MAX_TOKEN_SIZE];
    bool error;

    while(*string){
        error = GetToken(string, delim, token, &count);

        if(error){
            return 0;
        }
        else{
            if(i > MAX_TOKENS){
                return 0;
            }
            else{
                memcpy(tokens[i++], token, count);
            }
        }
        string += count;
    }

    return i;
}


