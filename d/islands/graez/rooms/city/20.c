


#include <std.h>
#include "../../graez.h"

inherit STORAGE"outerstreet.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C111%^Water %^CRST%^from the harbor laps up against the
%^C094%^boardwalk %^CRST%^and you can see the %^C094%^galleons %^CRST%^and %^C094%^merchant 
ships%^CRST%^ off in the distance. The %^C059%^road %^CRST%^continues east and north from here.\n");


set_exits(([
"east" : BATTLE"21",
"west" : TOWN"19",
"north" : BATTLE"11",

]));

}
