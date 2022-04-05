// Port Serith Grocer


#include <std.h>
#include <daemons.h>
#include "../../serakii.h"

inherit ROOM;

string night_long, day_long;

void create() {
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",0);
    set_name("open air market");
    set_short("open air market");
    set_long("market\n");
    day_long = "This %^C059%^square %^CRST%^of the city has been cleared of its previous %^C059%^buildings %^CRST%^and is an busy %^C075%^open air market%^CRST%^ packed with %^C215%^villagers%^CRST%^. %^C094%^Individual stalls%^CRST%^ are everywhere however a %^C094%^large stall%^CRST%^ dominates the northern section with a variety of %^C070%^foodstuff %^CRST%^for sale. %^C094%^Tables %^CRST%^have been set up for people to rest and eat %^C140%^treats %^CRST%^they have purchased. %^C142%^Canvas %^CRST%^drapes from high points to protect from the weather and the mood here is %^C141%^jovial%^CRST%^.\n";
    night_long = "This %^C059%^square %^CRST%^of the city has been cleared of its previous %^C060%^buildings%^CRST%^ and is an %^C057%^open air market%^CRST%^ with a large stall dominating the northern section. %^C094%^Individual stalls%^CRST%^ are everywhere however a %^C094%^large stall%^CRST%^ dominates the northern section with a variety of %^C077%^foodstuff %^CRST%^for sale. In the %^C066%^quiet of night%^CRST%^ time the market is empty though there is room in the %^C094%^stand %^CRST%^to sell a great many things. A couple of %^C094%^tables %^CRST%^are set up though most are set off to the side. %^C143%^Canvas %^CRST%^drapes from high points that protect from the weather.\n";
    set_items(([
        ({"ground","stones"}) : "The %^C058%^ground %^CRST%^here is newly laid %^C241%^cobblestone%^CRST%^.",
        ({"cart","carts"}) : "The whole market square is filled with %^C094%^individual stalls%^CRST%^ however one larger one on the north side catches your eye. It has room for many products and an outside %^C243%^brick oven%^CRST%^ for baking bread.",
        ({"tables","table"}) : "The %^C094%^tables %^CRST%^here are perfect for a quick rest.",
        ({"oven","brick oven"}) : "A large %^C242%^brick oven%^CRST%^ sits behind the %^C094%^large stall%^CRST%^. In the evening the next day's bread is cooked. .",
        ({"canvas"}) : "%^C143%^Canvas sheets%^CRST%^ have been tied off from taller points along buildings and to %^C094%^poles %^CRST%^so provide some relief from the %^C190%^sun %^CRST%^during the day, and %^C243%^weather %^CRST%^when it is inclement.",


    ]));




   set_exits(([

          "south" : TOWN"14",
   ]));

}

void reset()
{
    ::reset();
    if(!present("shopkeep"))
		{
			new(MOBS"market_keeper.c")->move(TO);
		}
}

void init() {
    string tod;
    ::init(); 
    if(!interactive(TP)) return;
    tod = EVENTS_D->query_time_of_day();
    if(tod == "night"){

        set_long(night_long);
		set_smell("default","You smell %^C094%^bread %^CRST%^baking.");
		set_listen("default","The market is quiet at %^C062%^night%^CRST%^.");		
    }
    if(tod != "night"){
        set_long(day_long);
    set_smell("default","You smell %^C137%^cooked foods%^CRST%^ all around you.");
    set_listen("default","The sounds of the %^C058%^busy market%^CRST%^ are almost overwhelming.");
    }
}

void close_shop(){ 
    set_long(night_long);
    tell_room(EETO, "\n%^C062%^Villagers leave the market as it is shut down.%^CRST%^\n");
	set_smell("default","You smell %^C094%^bread %^CRST%^baking.");
	set_listen("default","The market is quiet at %^C062%^night%^CRST%^.");	
return;
}

void open_shop(){
    set_long(day_long);
    tell_room(EETO, "Villagers arrive as the market opens.");
    set_smell("default","You smell %^C137%^cooked foods%^CRST%^ all around you.");
    set_listen("default","The sounds of the %^C058%^busy market%^CRST%^ are almost overwhelming.");
	return;
}

