
#include <std.h>
#include "../../graez.h"

inherit STORAGE"beforewall.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"3",
"southeast" : ROOMS"23",
"southwest" : ROOMS"12",
"northeast" : ROOMS"14", 

]));


}

