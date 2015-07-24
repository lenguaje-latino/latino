#include "latino.h"
#include "llex.h"
#include "lio.h"
#include "lparser.h"


LAT_FUNC int lat_init(lstring path){
    return lparser(path);
}
