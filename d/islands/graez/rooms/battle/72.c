
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"62",
"northeast" : ROOMS"73",
"southwest" : ROOMS"71",
"southeast" : ROOMS"82",


]));


}

