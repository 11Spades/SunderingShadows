
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"42",
"northeast" : ROOMS"53",
"southwest" : ROOMS"51",
"southeast" : ROOMS"62",


]));


}

