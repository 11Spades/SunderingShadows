
#include <std.h>
#include "../../graez.h"

inherit STORAGE"heavy_forest.c";

void create() {
    ::create();

set_exits(([

"east" : FOREST"17",
"north" : FOREST"19",
"southwest" : FOREST"23",
"south" : FOREST"24"



]));

}

