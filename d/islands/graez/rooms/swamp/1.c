
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([
"southwest" : MOUNT"13",
"northeast" : SWAM"2",
"east" : SWAM"3",


]));

}

