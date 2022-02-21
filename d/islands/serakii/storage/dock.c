#include <std.h>
#include "../serakii.h"

inherit CROOM;
void pick_critters();

string seas;

void create() {
    ::create();
    set_terrain(VILLAGE);
    set_travel(RUTTED_TRACK);
    set_property("indoors",0);
    set_name("abandoned docks");
    set_property("light",2);
    set_short("%^RESET%^%^ORANGE%^abandoned docks%^RESET%^");
    seas = season(time());
    set_long("blah");
    switch(seas){
    case "summer": 
        set_long("%^RESET%^%^ORANGE%^The docks stretch out for miles both "+
		"north and south along the crescent of the cove. %^RED%^Massive wooden "+
		"constructs%^RESET%^%^ORANGE%^ form docks fit for the largest of "+
		"%^GREEN%^galleons%^RESET%^%^ORANGE%^ and is spectacular as a deep water "+
		"port. The %^RED%^%^BOLD%^burning sun%^RESET%^%^ORANGE%^. heats a busy dock "+
		"filled with fishing vessels and trade ships. Everywhere you walk there are crowds of workers. "+
		"Bundles of %^GREEN%^ropes%^RESET%^%^ORANGE%^ lay in coils ready for pulling in ships "+
        "and crates sit in neat stacks covered in cargo netting. "+
		"To the east a road passes lively buildings and into the city.\n%^RESET%^");
    break;
    
    case "spring": 
        set_long("%^RESET%^%^GREEN%^The docks stretch out for miles both north and "+
		"south along the crescent of the cove. %^RESET%^%^ORANGE%^Massive wooden "+
		"constructs%^RESET%^%^GREEN%^ form docks fit for the largest of "+
		"%^ORANGE%^galleons%^RESET%^%^GREEN%^ and is spectacular as a deep water "+
		"port with ships dotting the harbor and docked. Newly created %^RESET%^birds. "+
		"nests%^RESET%^%^GREEN%^ dot the eaves of buildings and you can hear "+
		"the %^YELLOW%^chirping%^RESET%^%^GREEN%^ across the harbor of the newly "+
		"hatched birds. %^RESET%^%^ORANGE%^Bundles of ropes%^RESET%^%^GREEN%^ "+
		"lay in coils ready for usage and newly mended fishing nets lay ready. %^ORANGE%^Crates"+
		"%^RESET%^%^GREEN%^ sit in neat stacks covered in cargo netting. The "+
		"smell of %^RED%^%^BOLD%^flowers%^RESET%^%^GREEN%^ wafts in from the east "+
		"and the %^CYAN%^water%^RESET%^%^GREEN%^, while no longer frozen, still "+
		"holds a chill that rises. To the east a road passes lively buildings "+
                "and into the remains of a city.\n%^RESET%^");
    break;

    case "winter":
        set_long("%^RESET%^%^BOLD%^The docks stretch out for miles both north and "+
		"south along the crescent of the cove. Massive snow covered "+
		"%^RESET%^%^ORANGE%^wooden constructs%^RESET%^%^BOLD%^ form docks fit for "+
		"the largest of %^BLACK%^%^BOLD%^galleons%^RESET%^%^BOLD%^ and is spectacular "+
		"as a deep water port. The water has a broken %^CYAN%^cover of ice%^RESET%^%^BOLD%^ "+
		"where the constant traffic of merchant ships and fishing vessels has "+
		"carved a path. Bundles of frost covered ropes lay in coils ready for usage. "+
		"%^RESET%^%^ORANGE%^Crates%^RESET%^%^BOLD%^ sit in neat stacks covered in "+
		"cargo netting. To the east a road passes lively buildings and into the "+
		"city. The snow has been shovelled from the paths yet still collects "+
		"against the buildings.\n%^RESET%^");
    break;

    case "autumn":
        set_long("%^RESET%^%^ORANGE%^The docks stretch out for miles both north and "+
		"south along the crescent of the cove. %^RESET%^%^RED%^Massive wooden "+
		"constructs%^RESET%^%^ORANGE%^ form docks fit for the largest of "+
		"%^RESET%^galleons%^RESET%^%^ORANGE%^ and is spectacular as a deep water "+
		"port. But what is odd is that there isn.t a single ship, nor signs there "+
		"have been ships in some time. The water is covered in a carpet of "+
		"%^RED%^fallen leaves%^RESET%^%^ORANGE%^ that must have collected from all "+
		"across the island and dropped here by the prevailing winds. Bundles of "+
		"ropes lay in coils almost %^BLACK%^%^BOLD%^decayed%^RESET%^%^ORANGE%^ "+
		"into solid heaps. And crates sit in neat stacks covered in cargo netting. "+
		"To the east a road passes shuttered buildings and a westerly wind drives "+
		"through it back to the harbor with a hint of cold on its way. The path is "+
		"likewise covered in %^RED%^leaves%^RESET%^%^ORANGE%^  and leads into the "+
                "remains of a city.\n%^RESET%^");
    break;
	
    }   
    set_items(([
        ({"docks"}) : "%^RESET%^%^ORANGE%^The massive docks spread out to the "+
		"north and south along the cove.%^RESET%^",
		({"rope"}) : "%^RESET%^%^ORANGE%^There is enough coiled rope here to bind a "+
		"wing of dragons. It is used when a galleon docks to keep it secure.%^RESET%^.",
		({"water"}) : "%^RESET%^%^BLUE%^The water is brackish, salty and deep as "+
		"the ocean%^RESET%^",
        ({"buildings"}) : "%^RESET%^%^ORANGE%^The buildings along the dock have different "+
		"merchant businesses in them and the government functions of a dock.%^RESET%^",
    ]));

set_smell("default","%^RESET%^You smell the sea.");
set_listen("default","%^RESET%^You hear waves and a very busy dock around you.");


}

void reset() {
   int active;
   active = has_mobs();

   if(!active) {
     if(mons) mons = ([]);
     pick_critters();
   }
   ::reset();
}

   void pick_critters(){
   switch(random(5)){
      case 0..2: break;
      case 3..4: set_monsters( ({MOBS"seagull"}),({1}) );
               break;
}
}

