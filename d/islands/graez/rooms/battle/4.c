
#include <std.h>
#include "../../graez.h"

inherit STORAGE"beforewall.c";

void create() {
    ::create();



set_exits(([

"northeast" : ROOMS"5",
"southeast" : ROOMS"14",
"southwest" : ROOMS"3",

]));


}

