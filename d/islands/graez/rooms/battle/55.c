
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"45",
"northeast" : ROOMS"56",
"southwest" : ROOMS"54",
"southeast" : ROOMS"65",


]));


}

