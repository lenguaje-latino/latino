#ifndef _LATINO_H_
#define _LATINO_H_

#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
defined(__ELF__)
#define LAT_FUNC    __attribute__((visibility("hidden"))) extern
#else
#define LAT_FUNC    extern
#endif

/*isalpha, isnumber, etc...*/
#include<ctype.h>

/*data types*/
typedef unsigned char char_u;
typedef int lint;
typedef double ldecimal;
typedef char lchar;
typedef char *lstring;

#define ltrue 1
#define lfalse 0

#define lisalpha(c) (isalpha(c) || c == '_')
#define lisalnum(c) (isalnum(c))
#define lisdigit(c) (isdigit(c))

#define LAT_MAXWORD 32 /* maximum length to string word */

typedef struct lat_state {

} lat_state;

LAT_FUNC lint lat_init(lstring path);

#endif /*_LATINO_H_*/

