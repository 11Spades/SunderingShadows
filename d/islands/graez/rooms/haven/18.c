
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();

   set_long(::query_long()+"\nThis looks to have been where a square would be, with %^C100%^roads%^CRST%^ leading north and west through the %^C059%^settlement%^CRST%^.\n");

set_exits(([
"west" : HAVEN"19",
"east" : HAVEN"17",
"south" : HAVEN"2",

]));

}

