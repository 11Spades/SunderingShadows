
#include <std.h>
#include "../../graez.h"

inherit STORAGE"citywall.c";

void create() {
    ::create();



set_exits(([

"northeast" : ROOMS"4",
"south" : BATTLE"12",
"west" : TOWN"21",
"southeast" : ROOMS"13",
"southwest" : ROOMS"2",

]));


}

