
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"53",
"northeast" : ROOMS"64",
"southwest" : ROOMS"62",
"southeast" : ROOMS"73",


]));


}

