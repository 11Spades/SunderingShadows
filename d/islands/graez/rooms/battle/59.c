
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"49",
"northeast" : ROOMS"60",
"southwest" : ROOMS"58",
"southeast" : ROOMS"69",


]));


}

