#include <stdbool.h>

typedef char* str;
typedef char* op;

/*
    bool streq(str a, strb)
    -- checks if two strings are equall and returns true or false.
    Wrote this because I do not like the strcmp function in 
    in string.h (returns 0 for true!).
*/

bool streq(str a, str b);

/*
    bool free_strlist(str* list)
    -- free a string list (str*) that terminates with a NULL pointer. 
*/

void free_strlist(str* list);

/*
    str stripnl(str abc)
    -- removes all '\n' characters in a string.
*/

str stripnl(str input);

/*
    bool vchar(char c, str vc)
    -- checks if char c is in in the string vc. 
*/

bool vchar(char c, str vc);

/*
    bool vstr(str s, str* vc)
    -- given a string s and a 2D char (string) array that ends with 
    NULL vc, checks if s is in vc. 
*/

bool vstr(str s, str* vc);

/*
    str str_malloc(str s)
    -- copies string s to the heap and returns the pointer.
*/

str str_malloc(str s);
