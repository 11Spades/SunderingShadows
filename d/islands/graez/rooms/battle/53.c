
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"43",
"northeast" : ROOMS"54",
"southwest" : ROOMS"52",
"southeast" : ROOMS"63",


]));


}

