
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();



set_exits(([

"northeast" : ROOMS"7",
"southeast" : ROOMS"16",
"southwest" : ROOMS"5",

]));


}

