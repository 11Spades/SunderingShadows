
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"68",
"northeast" : ROOMS"79",
"southwest" : ROOMS"77",
"southeast" : ROOMS"88",


]));


}

