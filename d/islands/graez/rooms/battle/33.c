
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"23",
"northeast" : ROOMS"34",
"southwest" : ROOMS"32",
"southeast" : ROOMS"43",


]));


}

