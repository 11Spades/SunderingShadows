
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
   ::create();

set_exits(([

"north" : SWAM"7",
"west" : SWAM"3",
"southeast" : SWAM"14",


]));

}

