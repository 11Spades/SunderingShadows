
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"33",
"northeast" : ROOMS"44",
"southwest" : ROOMS"42",
"southeast" : ROOMS"53",


]));


}

