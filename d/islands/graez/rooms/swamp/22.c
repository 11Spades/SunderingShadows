
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([

"south" : SWAM"23",
"southeast" : SWAM"24",


]));

}

