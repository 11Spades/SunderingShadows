#include <std.h>
#include "../../serakii.h"

inherit STORAGE"bone_tower.c";

void create(){
   ::create();

set_exits(([
"gate" : BONE"1",
"northwest" : BONE"3",

]));

	add_item("statue","Before the gate is a %^C072%^large statue%^CRST%^ of "+
		"a %^C246%^magical construct%^CRST%^, both its humanoid arms raised "+
		"in combat. It has been formed from %^C071%^jade%^CRST%^ and is in "+
		"such perfect detail that you find it hard to believe it was %^C246%^carved%^CRST%^.");
   set_long(::query_long()+"\nIn the centre of the room is a %^C072%^large "+
   	"statue%^CRST%^ of a %^C245%^construct%^CRST%^.\n");

set_door("heavy gate",BONE"1","gate",0);
set_door_description("heavy gate","%^C058%^Formed from solid "+
    "wood, this door looks very "+
    "heavy. An iron ring hangs from it to allow it "+
    "to be opened.%^RESET%^");
set_string("heavy gate", "open", "%^C058%^The door opens silently.%^RESET%^");
set_string("heavy gate", "close", "%^C058%^The door closes silently.%^RESET%^");



}
