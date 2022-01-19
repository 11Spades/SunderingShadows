//Coded by Bane//
#include <std.h>
#include "/d/laerad/laerad.h"

inherit ASGARD;

void create(){
    ::create();
/*
   set_terrain(WOOD_BUILDING);
   set_travel(PAVED_ROAD);
    set_name("Guard tower");
    set_short("Guard tower");
    set_long(
	"%^BOLD%^Guard tower%^RESET%^
You are standing in a guard tower.  The walls are lined with bows and swords "+
	"incase of an invasion.  A few tables and chairs a spread throughout "+
	"the circular room.  An exit to the southwest leads back into the "+
	"central market square while an exit to the southeast leads "+
	"to another guard tower."
    );
    set_property("indoors",1);
    set_property("light",2);
    set_property("no bump",1);
    set_smell("default","The tower smells of old food and sweat.");
    set_listen("default","You hear the chatter of the city guards.");
*/
    set_long(::query_long()+"\nThis is the ruins of one of the guard "
       "towers surrounding the city.  It has faired better than the "
       "city itself, but not by much.  The walls rise only a few feet "
       "into the air, and the top has been sheared off, littering the "
       "floor with broken stone and wood.\n");
    set_exits( ([
	"southwest":"/d/laerad/parnelli/asgard/as73",
	"southeast":"/d/laerad/parnelli/asgard/tower11"
    ]) );
}
/*
void reset(){
    ::reset();
    if(!present("guard")){
	new("/d/laerad/mon/guard1")->move(this_object());
	new("/d/laerad/mon/guard1")->move(this_object());
    }
}
*/
