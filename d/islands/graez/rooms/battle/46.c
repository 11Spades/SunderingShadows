
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"36",
"northeast" : ROOMS"47",
"southwest" : ROOMS"45",
"southeast" : ROOMS"56",


]));


}

