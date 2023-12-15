#ifndef CORD_H_
#define CORD_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef CORDDEF
#define CORDDEF static inline
#endif

#define CORD_STRING_HEADER(str) ((cordString_header*)(str) - 1)

#define CORD_STRING_LEN(str) CORD_STRING_HEADER((str))->len
#define CORD_STRING_CAP(str) CORD_STRING_HEADER((str))->cap

typedef struct cordString_header {
    size_t len, cap;
} cordString_header;

typedef char* cordString;

CORDDEF cordString cord_new_string_reserve(size_t len);
CORDDEF cordString cord_new_string_len(const char* str, size_t str_len);
CORDDEF  cordString cord_new_string(const char* str);
CORDDEF void cord_free_string(cordString* str);
CORDDEF size_t cord_string_len(cordString str);
CORDDEF cordString cord_realloc_string(cordString* str, size_t newSize);
CORDDEF void cord_append_char(cordString* str, char c);
CORDDEF void cord_append_string_len(cordString* str, const char* str2, size_t len);
CORDDEF void cord_append_string(cordString* str, const char* str2);
CORDDEF void cord_to_uppercase(cordString* str);
CORDDEF void cord_to_lowercase(cordString* str);
CORDDEF void cord_trim(cordString* str);
CORDDEF void cord_ltrim(cordString * str);
CORDDEF void cord_rtrim(cordString* str);
CORDDEF char cord_char_at(cordString* str, int index);
CORDDEF int cord_index_of(cordString* str, char c);
CORDDEF void cord_repeat_char(cordString* str, char c, int count);
CORDDEF void cord_reverse(cordString* str);
CORDDEF void cord_replace_char(cordString* str, char c, char new_c);
CORDDEF void cord_ireplace_char(cordString* str, char c, char new_c);
CORDDEF void cord_pad_start(cordString* str, char c, int count);
CORDDEF void cord_pad_end(cordString* str, char c, int count);
CORDDEF bool cord_starts_with_len(cordString* str, const char* start, size_t len);
CORDDEF bool cord_starts_with(cordString* str, const char* start);
CORDDEF bool cord_ends_with_len(cordString* str,  const char* end, size_t len);
CORDDEF bool cord_ends_with(cordString* str,  const char* end);
CORDDEF void cord_wrap(cordString* str, size_t length);
CORDDEF void cord_remove_char(cordString* str, char c);
CORDDEF void cord_iremove_char(cordString* str, char c);
CORDDEF bool cord_includes_len(cordString* str, const char* substr, size_t len);
CORDDEF bool cord_includes(cordString* str, const char* substr);

// CORDDEF void cord_ljust(char **str, char c, size_t length);
// CORDDEF void cord_rjust(char **str, char c, size_t length);

#endif // CORD_H_

#ifdef CORD_IMPLEMENTATION

// Create a new string.
CORDDEF char* cord_new_string(const char *str)
{
    return cord_new_string_len(str, strlen(str));
}

// create a new string (using a set length)
CORDDEF cordString cord_new_string_reserve(size_t len) 
{
	void* ptr = malloc(sizeof(cordString_header) + (len + 1));
	
	cordString res_str = (cordString)ptr + sizeof(cordString_header);
	res_str[len] = '\0';

	cordString_header* header = CORD_STRING_HEADER(res_str);
	header->len = 0;
	header->cap = len;

	return res_str;
}

// create a new string (using the string length)
CORDDEF cordString cord_new_string_len(const char* str, size_t str_len) 
{
	cordString res_str = cord_new_string_reserve(str_len);
	strncpy(res_str, str, str_len);

	cordString_header* header = CORD_STRING_HEADER(res_str);
	header->len = str_len;

	return res_str;
}

// Free a string.
CORDDEF void cord_free_string(cordString* str)
{
    if (*str == NULL)
        return; 
    
    free((CORD_STRING_HEADER(*str)));
    *str = NULL;
}

// realloc memory for a string
CORDDEF cordString cord_realloc_string(cordString* str, size_t newSize) 
{
    size_t len = cord_string_len(*str);

	cordString res_str = cord_new_string_reserve(newSize);
	strncpy(res_str, *str, len);

    cord_free_string(str);
    
    CORD_STRING_LEN(res_str) = len;

    if (res_str != NULL)
        return res_str;

    printf("realloc failed\n");
    exit(1);

    return NULL;
}

// get the string's length
CORDDEF size_t cord_string_len(cordString str) 
{
    return CORD_STRING_LEN(str);
}

// Append a character at the end of the string.
CORDDEF void cord_append_char(char **str, char c)
{
    return cord_append_string_len(str, &c, 1);
}

// Append a string at the end of the string.
CORDDEF void cord_append_string(cordString* str, const char *c) 
{
    cord_append_string_len(str, c, strlen(c));
}

// append a string at the end of a string (based on length)
CORDDEF void cord_append_string_len(cordString* str, const char *c, size_t size)
{
    size_t len = cord_string_len(*str);
    
    if (len + size + 1 >= CORD_STRING_CAP(*str))
        *str = cord_realloc_string(str, (len + size + 9));

    strncpy((*str) + len, c, size);
    (*str)[len + size] = '\0';
    CORD_STRING_LEN(*str) += size;
}

// Convert a string to uppercase.
CORDDEF void cord_to_uppercase(cordString* str)
{
    for (int i = 0; i < cord_string_len(*str); i++)
    {
        if ((*str)[i] >= 'a' && (*str)[i] <= 'z')
        {
            (*str)[i] -= 32;
        }
    }
}

// Convert a string to lowercase.
CORDDEF void cord_to_lowercase(cordString* str)
{
    for (int i = 0; i < cord_string_len(*str); i++)
    {
        if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
        {
            (*str)[i] += 32;
        }
    }
}

// Trim a string.
CORDDEF void cord_trim(cordString* str)
{
    size_t len = cord_string_len(*str);
    int start = 0;
    int end = len - 1;

    while ((*str)[start] == ' ')
    {
        start++;
    }

    while ((*str)[end] == ' ')
    {
        end--;
    }

    int new_len = end - start + 1;
    char *new_str = cord_new_string_reserve(new_len + 1);

    strncpy(new_str, *str + start, new_len);
    new_str[new_len] = '\0';
    cord_free_string(str);
    *str = new_str;

    CORD_STRING_LEN(*str) = new_len;
}

// Left trim a string.
CORDDEF void cord_ltrim(cordString* str)
{
    size_t len = cord_string_len(*str);
    int start = 0;

    while ((*str)[start] == ' ')
    {
        start++;
    }

    int new_len = len - start;

    cordString new_str = cord_new_string_len(*str + start, new_len);

    cord_free_string(str);
    *str = new_str;

    CORD_STRING_LEN(*str) = new_len;
}

// Right trim a string.
CORDDEF void cord_rtrim(cordString* str)
{
    size_t len = cord_string_len(*str);
    int end = len - 1;

    while ((*str)[end] == ' ')
    {
        end--;
    }

    int new_len = end + 1;
    cordString new_str = cord_new_string_len(*str, new_len);

    cord_free_string(str);
    *str = new_str;
    
    CORD_STRING_LEN(*str) = new_len;
}

// Get a character at a specific index.
CORDDEF char cord_char_at(cordString* str, int index)
{
    return (*str)[index];
}

// Get the index of a character.
CORDDEF int cord_index_of(cordString* str, char c)
{
    for (int i = 0; i < cord_string_len(*str); i++)
    {
        if ((*str)[i] == c)
        {
            return i;
        }
    }
    return -1;
}

// Repeat a character and append it to the string.
CORDDEF void cord_repeat_char(cordString* str, char c, int count)
{
    size_t len = cord_string_len(*str);
    
    if (len + count + 1 >= CORD_STRING_CAP(*str))
        *str = cord_realloc_string(str, (len + count + 1));

    for (int i = 0; i < count; i++)
    {
        (*str)[len + i] = c;
    }
    (*str)[len + count] = '\0';

    CORD_STRING_LEN(*str) += count;
}

// Reverse a string.
CORDDEF void cord_reverse(cordString* str)
{
    size_t len = cord_string_len(*str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = (*str)[i];
        (*str)[i] = (*str)[len - i - 1];
        (*str)[len - i - 1] = temp;
    }
}

// Replace a character with another character.
CORDDEF void cord_replace_char(cordString* str, char c, char new_c)
{
    for (int i = 0; i < cord_string_len(*str); i++)
    {
        if ((*str)[i] == c)
        {
            (*str)[i] = new_c;
        }
    }
}

// Replace a string with another string case insensitive.
CORDDEF void cord_ireplace_char(cordString* str, char c, char new_c)
{
    for (int i = 0; i < cord_string_len(*str); i++)
    {
        if ((*str)[i] == c || (*str)[i] == c + 32 || (*str)[i] == c - 32)
        {
            (*str)[i] = new_c;
        }
    }
}

// Pad a string with a character at the start.
CORDDEF void cord_pad_start(cordString* str, char c, int count)
{
    size_t len = cord_string_len(*str);
    
    if (len + count + 1 >= CORD_STRING_CAP(*str))
        *str = cord_realloc_string(str, (len + count + 1));

    for (int i = len - 1; i >= 0; i--)
    {
        (*str)[i + count] = (*str)[i];
    }
    for (int i = 0; i < count; i++)
    {
        (*str)[i] = c;
    }
    (*str)[len + count] = '\0';

    CORD_STRING_LEN(*str) += count;
}

// Pad a string with a character at the end.
CORDDEF void cord_pad_end(cordString* str, char c, int count)
{
    size_t len = cord_string_len(*str);
    
    if (len + count + 1 >= CORD_STRING_CAP(*str))
        *str = cord_realloc_string(str, (len + count + 1));

    for (int i = 0; i < count; i++)
    {
        (*str)[len + i] = c;
    }
    (*str)[len + count] = '\0';

    CORD_STRING_LEN(*str) += count;
}

// If the string starts with a specific string.
CORDDEF bool cord_starts_with(cordString* str, const char* start) 
{
    return cord_starts_with_len(str, start, strlen(start));
}

CORDDEF bool cord_starts_with_len(cordString* str, const char* start, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] != start[i])
        {
            return false;
        }
    }
    return true;
}

// If the string ends with a specific string.
CORDDEF bool cord_ends_with(cordString* str, const char *end)
{
    return cord_ends_with_len(str, end, strlen(end));
}

CORDDEF bool cord_ends_with_len(cordString* str, const char *end, size_t len)
{
    int str_len = cord_string_len(*str);
    for (int i = 0; i < len; i++)
    {
        if ((*str)[str_len - len + i] != end[i])
        {
            return false;
        }
    }
    return true;
}

// Wraps a string to a specific length.
CORDDEF void cord_wrap(cordString* str, size_t length)
{

    size_t len = cord_string_len(*str);
    int new_len = len + (len / length);

    cordString new_str = cord_new_string_reserve(new_len + 1);

    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (i % length == 0 && i != 0)
        {
            new_str[j] = '\n';
            j++;
        }
        new_str[j] = (*str)[i];
        j++;
    }
    new_str[new_len] = '\0';

    cord_free_string(str);
    *str = new_str;

    CORD_STRING_LEN(*str) = new_len;
}

// Remove a character from a string.
CORDDEF void cord_remove_char(cordString* str, char c)
{
    size_t len = cord_string_len(*str);
    int new_len = len;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] == c)
        {
            new_len--;
        }
    }

    cordString new_str = cord_new_string_reserve(new_len + 1);

    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] != c)
        {
            new_str[j] = (*str)[i];
            j++;
        }
    }
    new_str[new_len] = '\0';

    cord_free_string(str);
    *str = new_str;

    CORD_STRING_LEN(*str) = new_len;
}

// Remove a character from a string case insensitive.
CORDDEF void cord_iremove_char(cordString* str, char c)
{
    size_t len = cord_string_len(*str);

    int new_len = len;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] == c || (*str)[i] == c + 32 || (*str)[i] == c - 32)
        {
            new_len--;
        }
    }
    char *new_str = cord_new_string_reserve(new_len + 1);

    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] != c && (*str)[i] != c + 32 && (*str)[i] != c - 32)
        {
            new_str[j] = (*str)[i];
            j++;
        }
    }
    new_str[new_len] = '\0';
    cord_free_string(str);

    *str = new_str;

    CORD_STRING_LEN(*str) = new_len;
}

// If a string includes a substring.
CORDDEF bool cord_includes(cordString* str, const char* substr) 
{
    return cord_includes_len(str, substr, strlen(substr));
}

CORDDEF bool cord_includes_len(cordString* str, const char* substr, size_t substr_len)
{
    size_t len = cord_string_len(*str);
    for (int i = 0; i < len && (len - i) >= substr_len; i++)
    {
        if (strncmp(*str + i, substr, substr_len) == 0)
            return true;
    }
    return false;
}

#endif // CORD_IMPLEMENTATION
