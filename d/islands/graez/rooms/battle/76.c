
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"66",
"northeast" : ROOMS"77",
"southwest" : ROOMS"75",
"southeast" : ROOMS"86",


]));


}

