
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"25",
"northeast" : ROOMS"36",
"southwest" : ROOMS"34",
"southeast" : ROOMS"45",


]));


}

