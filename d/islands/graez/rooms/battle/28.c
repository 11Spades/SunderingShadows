
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"18",
"northeast" : ROOMS"29",
"southwest" : ROOMS"27",
"southeast" : ROOMS"38",


]));


}

