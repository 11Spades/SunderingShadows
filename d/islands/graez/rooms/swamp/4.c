
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([

"north" : SWAM"9",
"northeast" : SWAM"8",
"south" : SWAM"2",


]));

}

