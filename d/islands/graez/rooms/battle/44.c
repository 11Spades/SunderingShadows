
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scrubland.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"34",
"northeast" : ROOMS"45",
"southwest" : ROOMS"43",
"southeast" : ROOMS"54",


]));


}

