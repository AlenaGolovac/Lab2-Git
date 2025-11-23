#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // ВИПРАВЛЕНО: на Mac використовуємо stdlib.h замість malloc.h
#include <ctype.h>
#include <stdio.h>
#include "sort.h" 

#define STRING_MAX 512ull

// Реалізація strlenn (довжина рядка)
const size_t strlenn(const char* str)
{
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Реалізація strcopy (копіювання рядка)
void strcopy(char* fStr, char* sStr, size_t until)
{
    for (size_t i = 0; i < until; i++) {
        fStr[i] = sStr[i];
    }
    fStr[until] = '\0';
}

// Реалізація strcmpp (порівняння рядків)
int32_t strcmpp(const char* fStr, const char* sStr)
{
    while (*fStr && (*fStr == *sStr)) {
        fStr++;
        sStr++;
    }
    return *(const unsigned char*)fStr - *(const unsigned char*)sStr;
}

// Реалізація введення рядка
const int32_t get_str(const char* msg, char* str, const int32_t limit)
{
    printf("%s", msg);
    if (fgets(str, limit, stdin)) {
        size_t len = strlenn(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            return len - 1;
        }
        return len;
    }
    return 0;
}

// Додавання рядка до рядка
char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0')
    {
        *ptr++ = *sStr++;
    }
    *ptr = '\0';
    return fStr;
}

// Перевірка валідності рядка
bool is_string_valid(char* str)
{
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);
    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0ull)
        {
            return false;
        }
        if (str[i] == ':')
        {
            isThereColon = true;
        }
        else if (isThereColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' ')
                {
                    return false;
                }
                else
                {
                    isThereString = true;
                }
            }
            if (str[i] == ';')
            {
                if (!isThereString || (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' '))
                {
                    return false;
                }
                else
                {
                    isThereColon = false;
                }
            }
            if (str[i] == ':')
            {
                return false;
            }
        }
        else
        {
            isThereString = false;
        }
    }
    return true;
}

// Основна функція обробки
char* process_string(char* str)
{
    const size_t length = strlenn(str);
    char* result = (char*)calloc(length * 2, sizeof(char)); 
    
    if (!result) return NULL;

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        if (str[i + 1] != ' ')
        {
            free(result);
            return NULL;
        }
        strcatt(result, ": ");
        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
        }
        
        for (size_t j = i + 2ull, strRealCnt = 0ull; j < length; j++)
        {
            if (str[j] == ',')
            {
                ++strRealCnt;
                ++j; 
                if(str[j] == ' ') ++j; 
            }
            else if (str[j] == ';')
            {
                quick_sort(arr, strRealCnt + 1);
                
                for (size_t k = 0; k <= strRealCnt; k++)
                {
                    if (strlenn(arr[k]) > 0) { 
                        strcatt(result, arr[k]);
                        if (k == strRealCnt)
                        {
                            strcatt(result, ";");
                        }
                        else
                        {
                            strcatt(result, ", ");
                        }
                    }
                }
                i = j;
                break;
            }
            else
            {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            free(arr[strsCnt]);
        }
        free(arr);
    }
    return result;
}
#endif
