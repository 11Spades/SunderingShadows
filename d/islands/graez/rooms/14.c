
#include <std.h>
#include "../../graez.h"

inherit STORAGE"heavy_forest.c";

void create() {
    ::create();

set_exits(([

"south" : FOREST"13",
"north" : BATTLE"87",

]));

   set_post_exit_functions(({"north"}), ({"GoThroughDoor"}));

}

int GoThroughDoor(){
   tell_object(TP,"\n%^C028%^You push your way through the forest. It is hard to know how far as the trail twists and turns, and you enter into the desert%^CRST%^\n");
   return 1;
}
