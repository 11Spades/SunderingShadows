//Coded by Bane//
#include <std.h>
inherit CROOM;

void create(){
    //set_monsters(({"/d/laerad/mon/bugbear"}),({1}));
    ::create();
    set_terrain(VILLAGE);
    set_travel(DIRT_ROAD);
    set_name("Main street");
    set_short("Main street");
    set_long(
	"%^BOLD%^Main street%^RESET%^
You are standing on the central road of Systyquah.  The street "+
	"forks to the southeast and southwest here, leading into "+
	"the inner streets in the city.  You can see a few huts off to either "+
	"side of the road.  A few bonfires are lit near by, smoke pouring "+
	"into the sky."
    );
    set_property("indoors",0);
    set_property("light",2);
    set_smell("default","The breeze carries a rank, nauseating smell.");
    set_listen("default","You hear the occasional scream of a troll war party.");
    set_exits( ([
	"north":"/d/laerad/parnelli/systyquah/sys004",
	"southeast":"/d/laerad/parnelli/systyquah/sys007",
	"southwest":"/d/laerad/parnelli/systyquah/sys006"
    ]) );
}
void reset(){
    ::reset();
/* changed to use CROOM  *Styx* 7/2002
if(!present("bugbear")){
	new("/d/laerad/mon/bugbear")->move(TO);
    }
*/
}
