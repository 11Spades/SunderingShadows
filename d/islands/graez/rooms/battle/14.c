
#include <std.h>
#include "../../graez.h"

inherit STORAGE"scarred_battlefield.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"4",
"southeast" : ROOMS"24",
"southwest" : ROOMS"13",
"northeast" : ROOMS"15", 

]));


}

