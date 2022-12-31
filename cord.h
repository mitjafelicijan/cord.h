#ifndef CORD_H_
#define CORD_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef CORDDEF
#define CORDDEF static inline
#endif

CORDDEF char *cord_new_string(char *str);
CORDDEF void cord_free_string(char **str);
CORDDEF void cord_append_char(char **str, char c);
CORDDEF void cord_append_string(char **str, char *str2);
CORDDEF void cord_to_uppercase(char **str);
CORDDEF void cord_to_lowercase(char **str);
CORDDEF void cord_trim(char **str);
CORDDEF void cord_ltrim(char **str);
CORDDEF void cord_rtrim(char **str);
CORDDEF char cord_char_at(char **str, int index);
CORDDEF int cord_index_of(char **str, char c);
CORDDEF void cord_repeat_char(char **str, char c, int count);
CORDDEF void cord_reverse(char **str);
CORDDEF void cord_replace_char(char **str, char c, char new_c);
CORDDEF void cord_ireplace_char(char **str, char c, char new_c);
CORDDEF void cord_pad_start(char **str, char c, int count);
CORDDEF void cord_pad_end(char **str, char c, int count);
CORDDEF bool cord_starts_with(char **str, char *start);
CORDDEF bool cord_ends_with(char **str, char *end);
CORDDEF void cord_wrap(char **str, int length);
CORDDEF void cord_remove_char(char **str, char c);
CORDDEF void cord_iremove_char(char **str, char c);
CORDDEF bool cord_includes(char **str, char *substr);

// CORDDEF void cord_ljust(char **str, char c, int length);
// CORDDEF void cord_rjust(char **str, char c, int length);

#endif // CORD_H_

#ifdef CORD_IMPLEMENTATION

// Create a new string.
CORDDEF char *cord_new_string(char *str)
{
    char *new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str);
    return new_str;
}

// Free a string.
CORDDEF void cord_free_string(char **str)
{
    free(*str);
    *str = NULL;
}

// Append a character at the end of the string.
CORDDEF void cord_append_char(char **str, char c)
{
    int len = strlen(*str);
    *str = realloc(*str, (len + 3) * sizeof(char));
    if (*str == NULL)
    {
        printf("realloc failed\n");
        exit(1);
    }
    (*str)[len] = c;
    (*str)[len + 1] = '\0';
}

// Append a string at the end of the string.
CORDDEF void cord_append_string(char **str, char *c)
{
    int len = strlen(*str);
    *str = realloc(*str, (len + strlen(c) + 1) * sizeof(char));
    if (*str == NULL)
    {
        printf("realloc failed\n");
        exit(1);
    }
    strcat(*str, c);
}

// Convert a string to uppercase.
CORDDEF void cord_to_uppercase(char **str)
{
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] >= 'a' && (*str)[i] <= 'z')
        {
            (*str)[i] -= 32;
        }
    }
}

// Convert a string to lowercase.
CORDDEF void cord_to_lowercase(char **str)
{
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
        {
            (*str)[i] += 32;
        }
    }
}

// Trim a string.
CORDDEF void cord_trim(char **str)
{
    int len = strlen(*str);
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
    char *new_str = malloc(new_len + 1);
    strncpy(new_str, *str + start, new_len);
    new_str[new_len] = '\0';
    free(*str);
    *str = new_str;
}

// Left trim a string.
CORDDEF void cord_ltrim(char **str)
{
    int len = strlen(*str);
    int start = 0;

    while ((*str)[start] == ' ')
    {
        start++;
    }

    int new_len = len - start;
    char *new_str = malloc(new_len + 1);
    strncpy(new_str, *str + start, new_len);
    new_str[new_len] = '\0';
    free(*str);
    *str = new_str;
}

// Right trim a string.
CORDDEF void cord_rtrim(char **str)
{
    int len = strlen(*str);
    int end = len - 1;

    while ((*str)[end] == ' ')
    {
        end--;
    }

    int new_len = end + 1;
    char *new_str = malloc(new_len + 1);
    strncpy(new_str, *str, new_len);
    new_str[new_len] = '\0';
    free(*str);
    *str = new_str;
}

// Get a character at a specific index.
CORDDEF char cord_char_at(char **str, int index)
{
    return (*str)[index];
}

// Get the index of a character.
CORDDEF int cord_index_of(char **str, char c)
{
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] == c)
        {
            return i;
        }
    }
    return -1;
}

// Repeat a character and append it to the string.
CORDDEF void cord_repeat_char(char **str, char c, int count)
{
    int len = strlen(*str);
    *str = realloc(*str, (len + count + 1) * sizeof(char));
    if (*str == NULL)
    {
        printf("realloc failed\n");
        exit(1);
    }
    for (int i = 0; i < count; i++)
    {
        (*str)[len + i] = c;
    }
    (*str)[len + count] = '\0';
}

// Reverse a string.
CORDDEF void cord_reverse(char **str)
{
    int len = strlen(*str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = (*str)[i];
        (*str)[i] = (*str)[len - i - 1];
        (*str)[len - i - 1] = temp;
    }
}

// Replace a character with another character.
CORDDEF void cord_replace_char(char **str, char c, char new_c)
{
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] == c)
        {
            (*str)[i] = new_c;
        }
    }
}

// Replace a string with another string case insensitive.
CORDDEF void cord_ireplace_char(char **str, char c, char new_c)
{
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] == c || (*str)[i] == c + 32 || (*str)[i] == c - 32)
        {
            (*str)[i] = new_c;
        }
    }
}

// Pad a string with a character at the start.
CORDDEF void cord_pad_start(char **str, char c, int count)
{
    int len = strlen(*str);
    *str = realloc(*str, (len + count + 1) * sizeof(char));
    if (*str == NULL)
    {
        printf("realloc failed\n");
        exit(1);
    }
    for (int i = len - 1; i >= 0; i--)
    {
        (*str)[i + count] = (*str)[i];
    }
    for (int i = 0; i < count; i++)
    {
        (*str)[i] = c;
    }
    (*str)[len + count] = '\0';
}

// Pad a string with a character at the end.
CORDDEF void cord_pad_end(char **str, char c, int count)
{
    int len = strlen(*str);
    *str = realloc(*str, (len + count + 1) * sizeof(char));
    if (*str == NULL)
    {
        printf("realloc failed\n");
        exit(1);
    }
    for (int i = 0; i < count; i++)
    {
        (*str)[len + i] = c;
    }
    (*str)[len + count] = '\0';
}

// If the string starts with a specific string.
CORDDEF bool cord_starts_with(char **str, char *start)
{
    int len = strlen(start);
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
CORDDEF bool cord_ends_with(char **str, char *end)
{
    int len = strlen(end);
    int str_len = strlen(*str);
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
CORDDEF void cord_wrap(char **str, int length)
{
    int len = strlen(*str);
    int new_len = len + (len / length);
    char *new_str = malloc(new_len + 1);
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
    free(*str);
    *str = new_str;
}

// Remove a character from a string.
CORDDEF void cord_remove_char(char **str, char c)
{
    int len = strlen(*str);
    int new_len = len;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] == c)
        {
            new_len--;
        }
    }
    char *new_str = malloc(new_len + 1);
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
    free(*str);
    *str = new_str;
}

// Remove a character from a string case insensitive.
CORDDEF void cord_iremove_char(char **str, char c)
{
    int len = strlen(*str);
    int new_len = len;
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] == c || (*str)[i] == c + 32 || (*str)[i] == c - 32)
        {
            new_len--;
        }
    }
    char *new_str = malloc(new_len + 1);
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
    free(*str);
    *str = new_str;
}

// If a string includes a substring.
CORDDEF bool cord_includes(char **str, char *substr)
{
    int len = strlen(*str);
    int substr_len = strlen(substr);
    for (int i = 0; i < len; i++)
    {
        if ((*str)[i] == substr[0])
        {
            bool found = true;
            for (int j = 0; j < substr_len; j++)
            {
                if ((*str)[i + j] != substr[j])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return true;
            }
        }
    }
    return false;
}

#endif // CORD_IMPLEMENTATION
