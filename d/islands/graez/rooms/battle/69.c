
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"59",
"northeast" : ROOMS"70",
"southwest" : ROOMS"68",
"southeast" : ROOMS"79",


]));


}

