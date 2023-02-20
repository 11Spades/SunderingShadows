//short pathway to Tempus's temple ~Circe~ 4/1/05
#include <std.h>
#include "/d/dagger/road/short.h"

inherit ROOM;

void create(){
    ::create();
    set_terrain(OLD_MOUNTS);
    set_travel(DIRT_ROAD);
    set_property("light", 2);
    set_name("A Narrow Footpath");
    set_short("A Narrow Footpath");
    set_long(
      "%^ORANGE%^This narrow footpath leads away from the more "+
      "travelled road through the northern regions of the Dagger "+
      "area.  The path looks to have been worn by countless feet "+
      "visiting the impressive red stone building to the southeast.  "+
      "Back to the northwest is the main road, while the "+
      "pyramid of Nurval rises to the west.  Directly south "+
      "of here stands a drawbridge leading west through the gates "+
      "and into the city, while the magnificent building is to the "+
      "east.\n"
    );
    set_smell("default", "The scent of the marsh is mingled with that of sweat.");
    set_listen("default", "You can hear the occasional clang of steel against steel.");
    set_items( ([
	"plains" : "These emerald plains span a great distance.",
	({"trees", "forest"}) : "The tops of the great trees of the Kilkean forest are barely visible in the distance.",
    ({"pyramid"}):"Massive structure dominates landscape to the west",
    /*({"building","temple"}) : "The large red stone building "+
         "to the south looks to be some sort of military "+
         "compound.  Local talk informs you that it is actually "+
         "a grand temple dedicated to Tempus, the god of war."*/
    ]) );
    set_exits( ([
       "north" : RPATH"p6",
       "south" : RPATH"p8"
    ]) );
}

void reset()
{
    ::reset();
    if(!present("street_light",TO))
        new("/d/common/obj/misc/street_light")->move(TO);
}
