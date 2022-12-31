# Small C library for handling strings

<p align="center">

![Hi](https://user-images.githubusercontent.com/296714/210126037-85383a55-1ee4-4128-bd0b-08d2a02a7062.png)

</p>

IMPORTANT! THIS LIBRARY IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS LIBRARY AT YOUR OWN RISK!

It's an STB style header which also includes the implementation part. You can enable the implementation part by defining `CORD_IMPLEMENTATION` before including the header.

Library is not using any external dependencies and uses only standards C libraries.

## Quick Example

```c
#define CORD_IMPLEMENTATION
#include "cord.h"

int main(void)
{
    char *str = cord_new_string("Some string");
    cord_append_char(&str, 'a');
    cord_append_string(&str, " and some more text    ");
    cord_trim(&str);
    cord_ireplace_char(&str, 'O', '-');
    cord_free_string(&str);
}
```

Because of the use of `realloc`, you must create new string with `malloc` or use the function that comes with the library called `cordc_new_string`.

## Current Features

- `char *cord_new_string(char *str);`
- `void cord_free_string(char **str);`
- `void cord_append_char(char **str, char c);`
- `void cord_append_string(char **str, char *str2);`
- `void cord_to_uppercase(char **str);`
- `void cord_to_lowercase(char **str);`
- `void cord_trim(char **str);`
- `void cord_ltrim(char **str);`
- `void cord_rtrim(char **str);`
- `char cord_char_at(char **str, int index);`
- `int cord_index_of(char **str, char c);`
- `void cord_repeat_char(char **str, char c, int count);`
- `void cord_reverse(char **str);`
- `void cord_replace_char(char **str, char c, char new_c);`
- `void cord_ireplace_char(char **str, char c, char new_c);`
- `void cord_pad_start(char **str, char c, int count);`
- `void cord_pad_end(char **str, char c, int count);`
- `bool cord_starts_with(char **str, char *start);`
- `bool cord_ends_with(char **str, char *end);`

## Planned Features

- [ ] wordwrap()
- [ ] split()
- [ ] join()

## Demo

By default it uses `clang` and you can change it by editing the `Makefile`, specifically `CC` variable.

```sh
make
```
