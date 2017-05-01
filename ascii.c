#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iAscii(const char *strText)
{
	char texto;
	short i,longitud;
	longitud=strlen(strText);

	for(i=0;i<longitud;i++)
{
	texto=strText[i];
	switch(texto)
{
case 'á':
 printf("\240");
	break;

	case 'é':
 printf("\202");
	break;

	case 'í':
 printf("\241");
	break;

	case 'ó':
 printf("\242");
	break;

 case 'ú':
 printf("\243");
 break;

 case 'ñ':
 printf("%c",-92);
 break;

	case 'Ñ':
	printf("%c",-91);
	break;

	case 'Á':
	printf("%c",-75);
	break;

	case 'É':
	printf("%c",-112);
	break;

	case 'Í':
	printf("%c",-42);
	break;

	case 'Ó':
	printf("%c",-32);
	break;

	case 'Ú':
	printf("%c",-23);
	break;

	default:
	printf("%c",texto);
	break;
}
}
}

int main()
{
	iAscii("Ú ñoño\n");
	return 0;
}
