#include <stdio.h>

#define CORD_IMPLEMENTATION
#include "cord.h"

void debug(char *str, char *func)
{
    printf("f:%s :: l:%lu => v:`%s`\n", func, strlen(str), str);
}

int main(void)
{
    char *o = cord_new_string("  Hello    ");
    debug(o, "new_string");

    cord_ltrim(&o);
    debug(o, "ltrim");

    cord_rtrim(&o);
    debug(o, "rtrim");

    cord_append_char(&o, 'A');
    debug(o, "append_char");

    cord_append_string(&o, "BCD");
    debug(o, "append_string");

    cord_to_uppercase(&o);
    debug(o, "to_uppercase");

    cord_to_lowercase(&o);
    debug(o, "to_lowercase");

    printf("f:char_at char_at: %c\n", cord_char_at(&o, 3));
    printf("f:index_of index_of: %d\n", cord_index_of(&o, 'l'));

    cord_repeat_char(&o, 'X', 10);
    debug(o, "repeat_char");

    cord_reverse(&o);
    debug(o, "reverse");

    cord_replace_char(&o, 'X', '+');
    debug(o, "replace_char");

    cord_ireplace_char(&o, 'L', 'Q');
    debug(o, "ireplace_char");

    cord_pad_start(&o, '_', 5);
    debug(o, "pad_start");

    cord_pad_end(&o, '_', 5);
    debug(o, "pad_end");

    printf("f:starts_with (__): %d\n", cord_starts_with(&o, "__"));
    printf("f:starts_with ( ): %d\n", cord_starts_with(&o, " "));

    printf("f:ends_with (__): %d\n", cord_ends_with(&o, "__"));
    printf("f:ends_with ( ): %d\n", cord_ends_with(&o, " "));

    char *k = cord_new_string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    cord_wrap(&k, 80);
    printf("f:wrap (80): %s\n", k);

    cord_remove_char(&k, 'i');
    debug(k, "remove_char");

    cord_free_string(&o);
    cord_free_string(&k);

    return 0;
}
