
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

   set_long(::query_long()+"\nTo the northeast, the %^C242%^mountain path%^CRST%^ declines sharply into a %^C029%^fetid swamp land%^CRST%^.\n");

set_exits(([
"southwest" : MOUNT"12",
"northeast" : SWAM"1",

]));

}

