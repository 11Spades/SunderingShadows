
#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the west are newly constructed buildings that are home to the %^C174%^middle%^CRST%^ and %^C220%^upper class%^CRST%^ people in the city. To the east is a %^C028%^small square%^CRST%^ for public gatherings. The %^C059%^road%^CRST%^ continues east and north from here.\n");


set_exits(([
"east" : TOWN"square",
"north" : TOWN"10",
"south" : TOWN"8",

]));

}

