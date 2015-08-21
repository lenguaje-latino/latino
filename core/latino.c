#include <stdlib.h>

#include "latino.h"
#include "llex.h"
#include "lio.h"
#include "lparser.h"

#include "llist.h"
#include "lmem.h"

static void freelist (void *data){
    /*printf("%s\n", "limpiando lista");*/
    /*printf("%s=%i\n", "limpiando lista", *((int*)data));*/
    /*lfree(data);*/
}

static void test_list(){
    list l;
    list_new(&l, sizeof(int), &freelist);
    /*list_new(&l, sizeof(int), NULL);*/

    int i;
    for(i = 0; i < 32000; i++) {
        list_append(&l, &i);
        /*list_push(&l, &i);*/
    }
    int value;
    list_first(&l, &value, 0);
    printf("first=%i\n", value );
    list_last(&l, &value);
    printf("last=%i\n", value );
    list_nth(&l, 0, &value);
    printf("nth(0)=%i\n", value );
    list_nth(&l, 9, &value); //return last
    printf("nth(10)=%i\n", value );
    list_nth(&l, 5, &value); //return last
    printf("nth(5)=%i\n", value );
    list_nth(&l, -1, &value); //return last - 1
    printf("nth(-1)=%i\n", value );

    list rst;
    list_rest(&l, &rst);
    list_first(&rst, &value, 0);
    printf("first=%i\n", value );

    /*list *rst = lmalloc(sizeof(list));*/
    /*list_rest(&l, rst);*/
    /*list_first(rst, &value, 0);*/
    /*printf("first=%i\n", value );*/

    list_first(&l, &value, 0);
    printf("first=%i\n", value );

    list_nth(&rst, 5, &value); //return last
    printf("nth(5)=%i\n", value );

    list_destroy(&l);
    list_destroy(&rst);
}

LAT_FUNC int lat_init(lstring path){
    parser_init(path);

    test_list();
    return EXIT_SUCCESS;
}
