
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"15",
"northeast" : ROOMS"26",
"southwest" : ROOMS"24",
"southeast" : ROOMS"35",


]));


}

