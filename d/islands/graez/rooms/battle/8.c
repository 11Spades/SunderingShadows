
#include <std.h>
#include "../../graez.h"

inherit STORAGE"light_forest.c";

void create() {
    ::create();
   set_long(::query_long()+"\nTo the northwest a %^C059%^trail %^CRST%^leads up the %^C240%^mountain%^CRST%^.\n");



set_exits(([

"northeast" : ROOMS"9",
"southeast" : ROOMS"18",
"southwest" : ROOMS"7",
"northwest" : MOUNT"1",

]));


}

