
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();


set_exits(([

"northeast" : ROOMS"10",
"southeast" : ROOMS"19",
"southwest" : ROOMS"8",

]));


}

