
#include <std.h>
#include "../puppet.h"

inherit STORAGE"passageway.c";



void create(){
   ::create();


set_exits(([

"northwest" : ROOMS"3",
"south" : ROOMS"1",

]));

}

