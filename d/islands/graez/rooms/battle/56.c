
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"46",
"northeast" : ROOMS"57",
"southwest" : ROOMS"55",
"southeast" : ROOMS"66",


]));


}

