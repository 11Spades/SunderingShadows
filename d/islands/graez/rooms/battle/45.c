
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"35",
"northeast" : ROOMS"46",
"southwest" : ROOMS"44",
"southeast" : ROOMS"55",


]));


}

