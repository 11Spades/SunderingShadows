
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"64",
"northeast" : ROOMS"75",
"southwest" : ROOMS"73",
"southeast" : ROOMS"84",


]));


}

