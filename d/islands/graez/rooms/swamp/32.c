
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([

"east" : SWAM"31",
"north" : SWAM"34",
"northwest" : SWAM"33",

]));

}

