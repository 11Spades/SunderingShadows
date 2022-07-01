


#include <std.h>
#include "../../graez.h"

inherit STORAGE"outerstreet.c";



void create(){
   ::create();
      set_long(::query_long()+"\nTo the north lays the "+
	  "%^C059%^city barracks%^CRST%^, the building large "+
	  "and %^C066%^grand%^CRST%^, but without any "+
	  "ornamentation . The %^C059%^road%^CRST%^ continues "+
	  "to the south and west.\n");


set_exits(([
"east" : BATTLE"3",
"west" : TOWN"17",
"south" : BATTLE"2",
"north" : TOWN"common",

]));

}
void reset(){
   ::reset();
   if(!present("ambiance device")){
      new(MOBS"poor_ambiance.c")->move(TO);
   }
}

