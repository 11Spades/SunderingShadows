
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"48",
"northeast" : ROOMS"59",
"southwest" : ROOMS"57",
"southeast" : ROOMS"68",


]));


}

