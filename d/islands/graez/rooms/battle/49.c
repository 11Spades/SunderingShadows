
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"39",
"northeast" : ROOMS"50",
"southwest" : ROOMS"48",
"southeast" : ROOMS"59",


]));


}

