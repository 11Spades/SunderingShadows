
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"17",
"northeast" : ROOMS"28",
"southwest" : ROOMS"26",
"southeast" : ROOMS"37",


]));


}

