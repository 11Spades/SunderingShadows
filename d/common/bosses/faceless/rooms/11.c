
#include <std.h>
#include "../puppet.h"

inherit STORAGE"passageway.c";



void create(){
   ::create();

   set_long(::query_long()+"%^C058%^\nA smaller entrance here leads to a stage.%^CRST%^\n");

set_exits(([


"south" : ROOMS"10",
"stage" : STORAGE"stage",

]));

}

