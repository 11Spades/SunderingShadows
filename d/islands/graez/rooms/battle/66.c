
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"56",
"northeast" : ROOMS"67",
"southwest" : ROOMS"65",
"southeast" : ROOMS"76",


]));


}

