
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"54",
"northeast" : ROOMS"65",
"southwest" : ROOMS"63",
"southeast" : ROOMS"74",


]));


}

