
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"22",
"northeast" : ROOMS"33",
"southwest" : ROOMS"31",
"southeast" : ROOMS"42",


]));


}

