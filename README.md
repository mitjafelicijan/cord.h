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
    cordString str = cord_new_string("Some string");
    cord_append_char(&str, 'a');
    cord_append_string(&str, " and some more text    ");
    cord_trim(&str);
    cord_ireplace_char(&str, 'O', '-');
    cord_free_string(&str);

    // And so on...
}
```

Because of the use of `realloc` and the string header, you use the function that comes with the library called `cord_new_string` and `cord_free_string` to free the string. Other than that, the string behaves like a normal C string. So all the function that come with `string.h` can be used with it.

## Current Features
- `cordString cord_new_string(char *str);`
- `cordString cord_new_string_reserve(size_t len);`
- `void cord_free_string(cordString* str);`
- `cordString cord_realloc_string(cordString* str, size_t newSize);`
- `size_t cord_string_len(cordString str);`
- `void cord_append_char(cordString* str, char c);`
- `void cord_append_string(cordString* str, char *str2);`
- `void cord_to_uppercase(cordString* str);`
- `void cord_to_lowercase(cordString* str);`
- `void cord_trim(cordString* str);`
- `void cord_ltrim(cordString* str);`
- `void cord_rtrim(cordString* str);`
- `char cord_char_at(cordString* str, size_t index);`
- `size_t cord_index_of(cordString* str, char c);`
- `void cord_repeat_char(cordString* str, char c, size_t count);`
- `void cord_reverse(cordString* str);`
- `void cord_replace_char(cordString* str, char c, char new_c);`
- `void cord_ireplace_char(cordString* str, char c, char new_c);`
- `void cord_pad_start(cordString* str, char c, size_t count);`
- `void cord_pad_end(cordString* str, char c, size_t count);`
- `bool cord_starts_with(cordString* str, char *start);`
- `bool cord_ends_with(cordString* str, char *end);`
- `void cord_wrap(cordString* str, size_t length);`
- `void cord_remove_char(cordString* str, char c);`
- `void cord_iremove_char(cordString* str, char c);`
- `bool cord_includes(cordString* str, char *substr);`

NOTE : all functions with c-string (char*) input have their own respective `_len()` functions\
eg. `bool cord_includes(cordString* str, char *substr);` -> `bool cord_includes_len(cordString* str, const char* substr, size_t len);`

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
f:cord_includes (c): 1
f:cord_includes (::): 0
```

## Alternative Libraries
- [EimaMei/sili - a cross-platform standard library for modern C programming (including string manipulation)](https://github.com/EimaMei/sili)
- [antirez/sds - Simple Dynamic Strings library for C](https://github.com/antirez/sds)
- [tsoding/sv - Simple String_View implementation for C programming language.](https://github.com/tsoding/sv)
- [MichaelJWelsh/SmartString - A Lightweight, Fast, and Safe C Library Meant to Mimic String Functionality Present in C++](https://github.com/MichaelJWelsh/SmartString)

## License

[cord.h](https://github.com/mitjafelicijan/cord.h) was written by [Mitja Felicijan](https://mitjafelicijan.com/) and is released under the BSD two-clause license, see the LICENSE file for more information.
