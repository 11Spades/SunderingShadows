
#include <std.h>
#include "../../serakii.h"

inherit ROOM;

void create() {
    ::create();
    set_light(2);
    set_indoors(1);
    set_terrain(WOOD_BUILDING);
    set_travel(DIRT_ROAD);
    set_short("General Store");
    set_long("%^C094%^This shop is a small %^C244%^cramped %^C094%^building lit by a %^C255%^single candle%^C094%^ on the %^C058%^counter%^C094%^. There are %^C058%^shelves %^C094%^lining every wall and are stocked with %^C113%^items%^C094%^. The construction is simple, rustic, and cozy, yet there is also an air of %^C001%^poverty %^C094%^here. There are more empty spots on the shelves than full.\n%^CRST%^");
    set_exits(([

          "north" : TOWN"8",
	]));

     set_items(([
       "shelves":"These shelves are stocked with goods for adventuring."
     ] ));
    if(!present("Atesos"))
    {
      new(MOBS"atesos.c")->move(TO);
    }
}

void reset()
{
    ::reset();
    if(!present("clerk"))
    {
      new(MOBS"atesos.c")->move(TO);
    }
}
