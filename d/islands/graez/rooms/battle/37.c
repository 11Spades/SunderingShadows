
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"27",
"northeast" : ROOMS"38",
"southwest" : ROOMS"36",
"southeast" : ROOMS"47",


]));


}

