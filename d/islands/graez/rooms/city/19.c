#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C111%^Water%^CRST%^ from the harbor laps up against the %^C095%^boardwalk %^CRST%^and you can see the %^C094%^galleons %^CRST%^and %^C094%^merchant ships%^CRST%^ off in the distance. The %^C059%^road %^CRST%^continues east and west from here.%^CRST%^\n");


set_exits(([
"east" : TOWN"20",
"west" : TOWN"18",
"northeast" : BATTLE"11",

]));

}

