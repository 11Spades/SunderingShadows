
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

set_exits(([
"east" : MOUNT"14",
"north" : MOUNT"16",

]));

}

