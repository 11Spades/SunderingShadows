
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"26",
"northeast" : ROOMS"37",
"southwest" : ROOMS"35",
"southeast" : ROOMS"46",


]));


}

