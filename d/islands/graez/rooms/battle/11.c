
#include <std.h>
#include "../../graez.h"

inherit STORAGE"outerstreet.c";

void create() {
    ::create();

    set_name("battle field");

set_exits(([

"south" : TOWN"20",
"northwest" : ROOMS"1",
"north" : BATTLE"2",
"southeast" : ROOMS"21",
"northeast" : ROOMS"12",


]));


}
void reset(){
   ::reset();
   if(!present("ambiance device")){
      new(MOBS"poor_ambiance.c")->move(TO);
   }
}

