
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"65",
"northeast" : ROOMS"76",
"southwest" : ROOMS"74",
"southeast" : ROOMS"85",


]));


}

