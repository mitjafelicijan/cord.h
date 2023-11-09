# Small C library for handling strings

**Table of Contents**

- [Quick Example](#quick-example)
- [Current Features](#current-features)
- [Observations \& Critics](#observations--critics)
- [Planned Features](#planned-features)
- [Demo](#demo)
- [Alternative Libraries](#alternative-libraries)
- [License](#license)


**IMPORTANT! THIS LIBRARY IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS LIBRARY AT YOUR OWN RISK!**

This is a STB style header which also includes the implementation part. You can enable the implementation part by defining `CORD_IMPLEMENTATION` before including the header. It does not [follow strict STB style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt), but it is close enough.

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

    // And so on...
}
```

Because of the use of `realloc`, you must create a new string with `malloc` or use the function that comes with the library called `cordc_new_string`. Other than that, the string behaves like a normal C string. So all the function that come with `string.h` can be used with it.

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
- `void cord_wrap(char **str, int length);`
- `void cord_remove_char(char **str, char c);`
- `void cord_iremove_char(char **str, char c);`
- `bool cord_includes(char **str, char *substr);`

## Observations & Critics

- `cord_includes` should probably return the index of the first occurrence instead of `true` or `false`.
- `cord_pad_start` and `cord_pad_end` are weird and should be fixed to be more like `ljust` and `rjust` from Ruby.

## Planned Features

- `split()`
- `join()`

## Demo

By default it uses `clang` and you can change it by editing the `Makefile`, specifically `CC` variable. Or you can also override it by passing it as an argument to `make` command like `make CC=gcc`.

```sh
make # will use clang

make CC=gcc # will use gcc

./test # will run the test program
```

This will run the test program and print the output to the console. The output should look like this:

```text
f:new_string :: l:11 => v:`  Hello    `
f:ltrim :: l:9 => v:`Hello    `
f:rtrim :: l:5 => v:`Hello`
f:append_char :: l:6 => v:`HelloA`
f:append_string :: l:9 => v:`HelloABCD`
f:to_uppercase :: l:9 => v:`HELLOABCD`
f:to_lowercase :: l:9 => v:`helloabcd`
f:char_at char_at: l
f:index_of index_of: 2
f:repeat_char :: l:19 => v:`helloabcdXXXXXXXXXX`
f:reverse :: l:19 => v:`XXXXXXXXXXdcbaolleh`
f:replace_char :: l:19 => v:`++++++++++dcbaolleh`
f:ireplace_char :: l:19 => v:`++++++++++dcbaoQQeh`
f:pad_start :: l:24 => v:`_____++++++++++dcbaoQQeh`
f:pad_end :: l:29 => v:`_____++++++++++dcbaoQQeh_____`
f:starts_with (__): 1
f:starts_with ( ): 0
f:ends_with (__): 1
f:ends_with ( ): 0
f:wrap (80): Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor i
ncididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostru
d exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aut
e irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat n
ulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui
 officia deserunt mollit anim id est laborum.
f:remove_char :: l:408 => v:`Lorem psum dolor st amet, consectetur adpscng elt, sed do eusmod tempor 
ncddunt ut labore et dolore magna alqua. Ut enm ad mnm venam, qus nostru
d exerctaton ullamco labors ns ut alqup ex ea commodo consequat. Dus aut
e rure dolor n reprehendert n voluptate velt esse cllum dolore eu fugat n
ulla paratur. Excepteur snt occaecat cupdatat non prodent, sunt n culpa qu
 offca deserunt mollt anm d est laborum.`
```

## Alternative Libraries

- [antirez/sds - Simple Dynamic Strings library for C](https://github.com/antirez/sds)
- [tsoding/sv - Simple String_View implementation for C programming language.](https://github.com/tsoding/sv)
- [MichaelJWelsh/SmartString - A Lightweight, Fast, and Safe C Library Meant to Mimic String Functionality Present in C++](https://github.com/MichaelJWelsh/SmartString)

## License

[cord.h](https://github.com/mitjafelicijan/cord.h) was written by [Mitja Felicijan](https://mitjafelicijan.com/) and is released under the BSD two-clause license, see the LICENSE file for more information.
