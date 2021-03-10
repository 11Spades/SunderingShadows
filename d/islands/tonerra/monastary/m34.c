//m2

#include <std.h>
#include "/d/islands/tonerra/areadefs.h"

inherit ROOM;

void create(){
   ::create();
   set_terrain(STONE_BUILDING);
   set_travel(PAVED_ROAD);
   set_short("An old alchemy lab");
   set_long(
@OLI
   %^MAGENTA%^An old alchemy lab%^RESET%^
%^BOLD%^%^WHITE%^This lab is a small area. Obviously the monks have tried
to store the knowledge of chemicals and such here. You see
%^RESET%^%^ORANGE%^%^BOLD%^%^WHITE%^ lining the walls with the bottles, vials, and beakers.
%^REST%^Dust%^BOLD%^%^WHITE%^ covers everything, and it's obvious that this is not a well
used area.%^RESET%^
OLI
   );
     set_properties((["indoors":1,"light":1]));
   set_items(([
      "shelves":"These are dusty and bent. They hold many cob webbed vials and flasks.The shelves to the west glimmer a little, as if not real.",
      "vials":"These vials contain many many colors and textures of things.",
      "beakers":"Some of these beakers contain the results of mixtures, some are empty.",
   ]));
   set_exits(([
      "west":MONASTERY+"hall13",
      "south":MONASTERY+"m35",
   ]));
   set_smell("default","Must and dust make you cough.");
   set_listen("default","Silemce, this must be a truly forgotten room.");
   set_invis_exits(({"west"}));
}

void reset(){
   ::reset();
   if(!present("blue liquid")){
      new(OBJ+"liquid2")->move(TO);
   }
}
