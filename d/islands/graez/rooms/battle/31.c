
#include <std.h>
#include "../../graez.h"

inherit STORAGE"beforewall.c";

void create() {
    ::create();

set_exits(([

"northeast" : ROOMS"32",
"northwest" : ROOMS"21",
"southeast" : ROOMS"41",


]));


}

