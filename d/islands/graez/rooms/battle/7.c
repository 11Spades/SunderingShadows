
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();



set_exits(([

"northeast" : ROOMS"8",
"southeast" : ROOMS"17",
"southwest" : ROOMS"6",

]));


}

