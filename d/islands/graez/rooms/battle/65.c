
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"55",
"northeast" : ROOMS"66",
"southwest" : ROOMS"64",
"southeast" : ROOMS"75",


]));


}

