#include "latino.h"

#ifdef LATINO_HUGE
typedef long int varinteger_T;
typedef long double vardecimal_T;
else
typedef int varinteger_T;
typedef double vardecimal_T;
#endif

/*
 * This file contains various definitions of structures that are used by Latino
 */

typedef unsigned char	char_u;

typedef struct
{
    char         v_type;
    varinteger_T v_integer;
    vardecimal_T v_decimal;
    char_u       *v_string;
} typeval_T;

/* Values for "v_type". */
#define VAR_UNKNOWN 0
#define VAR_INTEGER 1	/* "v_integer" is used */
#define VAR_STRING  2	/* "v_string" is used */
#define VAR_FUNC    3	/* "v_string" is function name */
#define VAR_LIST    4	/* "v_list" is used */
#define VAR_DICT    5	/* "v_dict" is used */
#define VAR_DECIMAL 6	/* "v_decimal" is used */
