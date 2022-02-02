#include <std.h>
#include "forest.h"
inherit ROOM;

void create()
{
   ::create();
   set_terrain(MEADOWLANDS);
   set_travel(DIRT_ROAD);
   set_property("light",2);
   set_property("indoors",0);
   set_short("Path through the Meadow Lands");
   set_long(
   "%^BOLD%^You are walking on a path through the meadowlands.%^RESET%^\n"+
   "The road stretches out to the north and south, running along the"+
   " edge of the meadow lands. It seems a peaceful enough path for the most"+
   " part, but being in the wilderness is always dangerous.\n"
   );
   set_smell("default","You smell the fresh air and the odor of %^GREEN%^w%^BOLD%^i%^MAGENTA%^l%^RESET%^%^MAGENTA%^d%^BOLD%^fl%^RESET%^%^MAGENTA%^o%^BOLD%^we%^RESET%^%^MAGENTA%^r%^BOLD%^s%^ORANGE%^.");
   set_listen("default","You can hear the birds singing.");
   set_items(([
   "road" : "This is really just a glorified dirt path, but someone keeps"+
   " it in good shape.",
   ({"flowers","%^GREEN%^w%^BOLD%^i%^MAGENTA%^l%^RESET%^%^MAGENTA%^d%^BOLD%^fl%^RESET%^%^MAGENTA%^o%^BOLD%^we%^RESET%^%^MAGENTA%^r%^BOLD%^s%^ORANGE%^"}) : "Wildflowers dot the meadowlands to"+
   " the west.",
   "birds" : "There are many birds singing in the trees in the meadow lands.",
   ]));
   set_exits(([
   "north" : FORESTDIR+"road34",
   "south" : FORESTDIR+"road36",
   "west" : MEADOWS+"meadow13",
   ]));
}
