
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"24",
"northeast" : ROOMS"35",
"southwest" : ROOMS"33",
"southeast" : ROOMS"44",


]));


}

