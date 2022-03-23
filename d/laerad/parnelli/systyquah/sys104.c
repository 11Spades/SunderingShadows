//Coded by Bane//
#include <std.h>
inherit ROOM;
void create(){
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
	"slots, making sure the city's defenses are sound."
    );
    set_property("indoors",1);
    set_property("light",2);
    set_smell("default","A terrible odor fills the narrow hall.");
    set_listen("default","You hear the occasional scream of a troll war party.");
    set_exits( ([
	"north":"/d/laerad/parnelli/systyquah/sys105",
	"south":"/d/laerad/parnelli/systyquah/sys103"
    ]) );
}
