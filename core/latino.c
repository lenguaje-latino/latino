#include "latino.h"
#include "llex.h"
#include "lio.h"
#include "lparser.h"


LAT_FUNC lint lat_init(lstring path){
    lparser(path);
    return 0;
}
