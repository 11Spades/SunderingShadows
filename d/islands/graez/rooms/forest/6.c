
#include <std.h>
#include "../../graez.h"

inherit STORAGE"heavy_forest.c";

void create() {
    ::create();

  set_long(::query_long()+"\nTo the southwest of you, in the %^C075%^water %^CRST%^and with no way to reach it, rises a %^C195%^massive lighthouse%^CRST%^.\n");

set_exits(([

"north" : FOREST"5",
"east" : FOREST"26",
"southeast" : FOREST"7",

]));

}

