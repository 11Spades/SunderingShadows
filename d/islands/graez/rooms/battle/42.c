
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"32",
"northeast" : ROOMS"43",
"southwest" : ROOMS"41",
"southeast" : ROOMS"52",


]));


}

