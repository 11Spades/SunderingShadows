
#include <std.h>
#include "../../graez.h"

inherit STORAGE"ruins.c";


void create(){
   ::create();

   set_long(::query_long()+"%^C058%^\nThis building was part of the city's barracks that have been destroyed. There are scattered destroyed weapons and shattered armor laying everywhere.%^CRST%^\n");

   set_exits(([
        "east":OLD"/town/street17",
        "south":TOWN"forge",
        "southwest":TOWN"trader",
    ]));

}
