
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();

   set_long(::query_long()+"\nTo the southeast through the %^C059%^open gates%^CRST%^ is the %^C239%^mountain trail%^CRST%^.\n");


set_exits(([
"southeast" : MOUNT"17",
"north" : HAVEN"17",
"west" : HAVEN"2",

]));

}

