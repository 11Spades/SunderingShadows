
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([

"east" : SWAM"11",
"south" : SWAM"5",
"southwest" : SWAM"4",


]));

}

