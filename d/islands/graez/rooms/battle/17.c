
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";


void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"7",
"southeast" : ROOMS"27",
"southwest" : ROOMS"16",
"northeast" : ROOMS"18", 

]));


}

