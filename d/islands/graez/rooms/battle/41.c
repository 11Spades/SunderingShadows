
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"31",
"south" : FOREST"1",
"northeast" : ROOMS"42",
"southeast" : ROOMS"51",


]));


}

