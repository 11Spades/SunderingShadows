
#include <std.h>
#include "../../graez.h"

inherit STORAGE"heavy_forest.c";

void create() {
    ::create();

set_exits(([

"east" : FOREST"18",
"west" : FOREST"20b",
"south" : FOREST"20",
"north" : BATTLE"81",


]));

   set_post_exit_functions(({"north"}), ({"GoThroughDoor"}));

}

int GoThroughDoor(){
   tell_object(TP,"\n%^C028%^You push your way through the forset. It is hard to know how far as the trail twists and turns, and you enter into the light forest%^CRST%^\n");
   return 1;
}

