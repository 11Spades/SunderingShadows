#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C111%^Water %^CRST%^from the harbor laps up against the %^C094%^boardwalk %^CRST%^and you can see the %^C094%^galleons %^CRST%^and %^C094%^merchant ships%^CRST%^ off in the distance. To the west are newly constructed buildings that are home to the %^C174%^middle%^CRST%^ and %^C220%^upper class%^CRST%^ people in the city. The %^C059%^road %^CRST%^continues east and north from here.\n");


set_exits(([
"east" : TOWN"7",
"north" : TOWN"9",

]));
}

void reset(){
   ::reset();
   if(!present("ambiance device")){
      new(MOBS"harbor_ambiance.c")->move(TO);
   }
}
