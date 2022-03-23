
#include <std.h>
inherit "/d/attaya/base/spec/oubliette";

void create() {
    ::create();
    set_properties( ([ "light" : 1, "indoors" : 1 ]) );
    set_short("Inside the walls of the South Wall Fortress.");
    set_long("
    You are in a dark stone passageway.  Rotting tapestries accent cold brick.  This area is in tremendous contrast to the central hall!
    The passage is ancient.  You can feel the history in the walls around you.
");
    set_smell("default","The air smells of mildew and decay.");
    set_listen("default","Your footsteps echo loudly through the halls.");

    set_exits( ([
    "west" : "/d/attaya/base/lookout6",
    "east" : "/d/attaya/base/lookout8",
        ]) );
    set_items(([
    "windows" : "The entire inner wall is made of glass to display the beautiful crystalline tower outside.",
    "walls" : "The walls are built of ancient stone bricks that crumble and crack now beneath the weight of the fortress.",
    "floor" : "The floor, made of granite tiles, is covered by rotten decaying masses of black carpet.",
    "carpet" : "It is completely decayed.",
    "pool" : "The reflecting pool is crystal clear and reflects the crystalline tower."
    ]));

}
void reset(){
   object mon;
   ::reset();

    if(!present("archer")) {
         mon = new("/d/attaya/mon/archer");
	mon->set_id( ({"archer", "guard"}) );
	mon->move(this_object());
   }

}
