
#include <std.h>
#include "../../graez.h"

inherit STORAGE"heavy_forest.c";

void create() {
   ::create();
   set_long(::query_long()+"\nThe %^C065%^forest%^CRST%^ ends abruptly here, "+
   "ending in %^C060%^jagged rocks%^CRST%^ and a %^C060%^cliffside%^CRST%^ "+
   "down to the %^C081%^sea%^CRST%^ below. Getting down to the "+
   "%^C075%^water%^CRST%^ would be near impossible safely..\n");

set_exits(([

"southwest" : FOREST"12",
"north" : FOREST"14",

]));

}

