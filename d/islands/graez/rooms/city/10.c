
#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the west are newly constructed buildings that are home to the %^C174%^middle%^CRST%^ and %^C220%^upper class%^CRST%^ people in the city. The %^C059%^road%^CRST%^ continues north and south from here.\n");


set_exits(([
"north" : TOWN"12",
"south" : TOWN"9",

]));

}

