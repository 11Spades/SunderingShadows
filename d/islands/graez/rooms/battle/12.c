
#include <std.h>
#include "../../graez.h"

inherit STORAGE"citywall.c";

void create() {
    ::create();

set_exits(([

"northwest" : ROOMS"2",
"north" : BATTLE"3",
"south" : BATTLE"21",
"southeast" : ROOMS"22",
"southwest" : ROOMS"11",
"northeast" : ROOMS"13", 

]));


}

