#include "forest.h"

inherit "/d/shadow/room/forest/road1";

void create(){
    ::create();
   set_terrain(LIGHT_FOREST);
   set_travel(DIRT_ROAD);
    set_property("light" , 2);
    set_property("indoors" , 0);
    set_short("%^RESET%^%^GREEN%^On the Quiet %^BOLD%^%^GREEN%^Fo%^RESET%^%^GREEN%^r%^GREEN%^e%^BOLD%^%^GREEN%^s%^RESET%^%^GREEN%^t %^ORANGE%^R%^BOLD%^%^ORANGE%^o%^ORANGE%^a%^ORANGE%^d%^RESET%^");
    set_items(([
	"road":"This dirt road cuts through a quiet forest.",
	"forest":"This is an aptly named road through a quiet forest. You hear only the occasional bird song."
      ]));

    set_exits(([
   "west" : "/d/shadow/room/forest/road32",
   "east" : FORESTDIR+"road30"
       ]));
    set_smell("default","You smell fresh air and the odor of %^GREEN%^w%^BOLD%^i%^MAGENTA%^l%^RESET%^%^MAGENTA%^d%^BOLD%^fl%^RESET%^%^MAGENTA%^o%^BOLD%^we%^RESET%^%^MAGENTA%^r%^BOLD%^s%^ORANGE%^.");
    set_listen("default","You can hear birds singing.");    

    if(base_name(TO) == "/d/shadow/room/forest/road31")
    {
        if(!present("shopkeeper"))  new("/d/token_hunt/low_vendor")->move(TO);
        if(!present("dino"))        new("/d/token_hunt/low_dino")->move(TO);
        if(!present("wagon"))       new("/d/token_hunt/wagon")->move(TO);
    }
}

void reset()
{
    ::reset();

    if(base_name(TO) == "/d/shadow/room/forest/road31")
    {
        if(!present("shopkeeper"))  new("/d/token_hunt/low_vendor")->move(TO);
        if(!present("dino"))        new("/d/token_hunt/low_dino")->move(TO);
        if(!present("wagon"))       new("/d/token_hunt/wagon")->move(TO);
    }
}
