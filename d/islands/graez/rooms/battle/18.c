
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"8",
"southeast" : ROOMS"28",
"southwest" : ROOMS"17",
"northeast" : ROOMS"19", 

]));


}

