//Coded by Bane//
#include <std.h>
inherit CROOM;

void create(){
    set_monsters(({"/d/laerad/mon/trollg2", "/d/laerad/mon/trollt"}),({1, 1}));
    ::create();
    set_terrain(WOOD_BUILDING);
    set_travel(FOOT_PATH);
    set_name("Systyquah's city wall");
    set_short("Systyquah's city wall");
    set_long(
	"%^BOLD%^Inside the city walls%^RESET%^
You have walked into the city walls of Systyquah.  A narrow pathway "+
	"continues to the north and south.  Troll guards run up and down the "+
	"pathway, keeping watch on the outside through peep holes and arrow "+
	"slots, making sure the city's defenses are sound.  A gate to the "+
	"east leads into the city."
    );
    set_property("indoors",1);
    set_property("light",2);
    set_smell("default","A terrible odor fills the narrow hall.");
    set_listen("default","You hear the occasional scream of a troll war party.");
    set_exits( ([
	"east":"/d/laerad/parnelli/systyquah/sys044",
	"north":"/d/laerad/parnelli/systyquah/sys084",
	"south":"/d/laerad/parnelli/systyquah/sys086"
    ]) );
}

void reset(){
    ::reset();
}
