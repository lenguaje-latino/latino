#ifndef __lapi_h
#define __lapi_h

#include <stdlib.h>

#ifndef FALSE
# define FALSE 0
#elif FALSE
# error FALSE must be false
#endif
#ifndef TRUE
# define TRUE 1
#elif !TRUE
# error TRUE must be true
#endif

#define LOGICO int
#define ENTERO int
#define DECIMAL long
#define CARACTER char
#define CADENA char*

typedef LOGICO llogico;
typedef ENTERO lentero;
typedef DECIMAL  ldecimal;
typedef CARACTER lcaracter;

typedef struct lcadena{
	CADENA cadena;	
	size_t longitud;
}lcadena;

#endif
