
#include <std.h>
#include "../../graez.h"

inherit STORAGE"desert.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"20",
"southeast" : ROOMS"40",
"southwest" : ROOMS"29",


]));


}

