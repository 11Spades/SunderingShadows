
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

set_exits(([
"northwest" : MOUNT"7",
"east" : MOUNT"10",

]));

}

