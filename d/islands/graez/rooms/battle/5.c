
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();



set_exits(([

"northeast" : ROOMS"6",
"southeast" : ROOMS"15",
"southwest" : ROOMS"4",

]));


}

