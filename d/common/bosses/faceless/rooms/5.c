
#include <std.h>
#include "../puppet.h"

inherit STORAGE"banquet.c";



void create(){
   ::create();


set_exits(([

"east" : ROOMS"4",
"south" : ROOMS"7",
"north" : ROOMS"6",

]));

}

