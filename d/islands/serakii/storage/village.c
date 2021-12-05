#include <std.h>
#include "../serakii.h"

inherit CROOM;

string seas;

void create() {
    ::create();
    set_terrain(VILLAGE);
    set_travel(RUTTED_TRACK);
    set_property("indoors",0);
    set_name("cramped town street");
    set_property("light",2);
    set_short("%^RESET%^%^ORANGE%^cramped town street%^RESET%^");
    seas = season(time());
    set_long("blah");
new(OBJ"brazier.c");
    switch(seas){
    case "summer": 
        set_long("%^RESET%^%^ORANGE%^The streets of the town are cramped and "+
		"dominated on either side by %^RESET%^%^RED%^massive wooden buildings"+
		"%^RESET%^%^ORANGE%^ five or six stories high. Most of the buildings "+
		"have been shuttered and %^BLACK%^%^BOLD%^closed%^RESET%^%^ORANGE%^ "+
		"but you see no damage anywhere. The cramped space is %^RED%^sweltering"+
		"%^RESET%^%^ORANGE%^ in the %^RESET%^%^RED%^summer heat "+
		"%^RESET%^%^ORANGE%^and in corners small heat mirages form. The roads "+
		"are %^RESET%^bone dry cobblestone%^RESET%^%^ORANGE%^ and along both "+
		"sides are the rutted tracks where a thousand carts must have passed. "+
                "The streets themselves are quiet though.%^RESET%^\n");
    break;
    
    case "spring": 
        set_long("%^RESET%^%^ORANGE%^The streets of the town are cramped and "+
		"dominated on either side by %^RESET%^%^RED%^massive wooden "+
		"buildings%^RESET%^%^ORANGE%^ five or six stories high. Most of the "+
		"buildings have been shuttered and %^BLACK%^%^BOLD%^closed"+
		"%^RESET%^%^ORANGE%^ but you see no damage anywhere. The roads are "+
		"%^BLUE%^%^BOLD%^damp cobblestone%^RESET%^%^ORANGE%^ and along both "+
		"sides are the rutted tracks where a thousand carts must have passed. "+
		"The ruts themselves have been filled with the water from the "+
		"%^BLUE%^spring rains%^RESET%^%^ORANGE%^ but the streets themselves "+
                "are quiet.%^RESET%^\n");
    break;

    case "winter":
        set_long("%^RESET%^%^BOLD%^The streets of the town are cramped and "+
		"dominated on either side by %^RESET%^%^ORANGE%^massive wooden "+
		"buildings%^RESET%^%^BOLD%^ five or six stories high. Making it even "+
		"more cramped is a pile up of %^RESET%^snow%^RESET%^%^BOLD%^ on the "+
		"roof tops. Most of the buildings have been shuttered and "+
		"%^BLACK%^%^BOLD%^closed%^RESET%^%^BOLD%^ but you see no damage "+
		"anywhere. %^CYAN%^Massive icicles%^RESET%^%^BOLD%^ grow along the "+
		"eaves of buildings and a %^CYAN%^wicked cold%^RESET%^%^BOLD%^ wind "+
		"races down the %^RESET%^cobblestone road%^RESET%^%^BOLD%^. It is "+
		"obvious though that whoever lived in the city though isnt concerned "+
		"with clearing the snow.%^RESET%^\n\n");
    break;

    case "autumn":
        set_long("%^RESET%^%^RED%^The streets of the town are cramped and "+
		"dominated on either side by %^RESET%^%^ORANGE%^massive wooden "+
		"buildings%^RESET%^%^RED%^ five or six stories high. There is a "+
		"%^BLUE%^%^BOLD%^damp chill%^RESET%^%^RED%^ to the air. Most of the "+
		"buildings have been shuttered and closed but you see no damage "+
		"anywhere. Everywhere %^BOLD%^damp autumn leaves%^RESET%^%^RED%^ "+
		"lay and plaster the walls and rutted track of the %^RESET%^cold "+
		"cobblestone road%^RESET%^%^RED%^. Along both sides of the road are "+
		"the rutted tracks where a thousand carts must have passed. The "+
		"streets themselves are earily quiet.%^RESET%^\n");
    break;
	
    }   
    set_items(([
({"road","cobblestone"}) : "%^RESET%^the street has been paved with well set cobblestones. The road is old, old enough that deep ruts where wagon wheels traveled line both sides of the roads",
		({"buildings"}) : "%^RESET%^%^ORANGE%^Flanking both side of the road are tall multi story wood buildings. Most of the doors are barred and the windows shuttered.",
    ]));

set_smell("default","%^RESET%^You smell the sea.");
set_listen("default","%^RESET%^You hear waves.");

}

void reset(){
   ::reset();
   if(!present("heavy iron brazier")){
      new(OBJ"brazier.c")->move(TO);
   }
}
