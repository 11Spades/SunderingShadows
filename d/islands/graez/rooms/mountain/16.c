
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

   set_long(::query_long()+"\nTo the northwest you see the %^C100%^tall wooden palisades%^CRST%^ of a %^C059%^settlement%^CRST%^.\n");

set_exits(([
"south" : MOUNT"15",
"northwest" : MOUNT"17",

]));

}

