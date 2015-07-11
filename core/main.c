#include <stdio.h>
/* for system function */
#include <stdlib.h>
#include "latino.h"

int main(int argc, char *argv[])
{
    lstring path = NULL;
    if (argc == 1) {
        printf("%s\n", "especifique archivo con extension .lat");
    } else {
        path = argv[1];
        printf("escaneando archivo...%s\n", path);
        lint result = lat_init(path);
        printf("result=%i\n", result);
    }
    system("pause");
    return 0;
}
