#include <std.h>
#include "../serakii.h"

inherit CVAULT;

void pick_critters();


void create() {
    ::create();
    pick_critters();
    set_repop(35);
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);

    set_property("indoors",1);
    set_short("%^C231%^whi%^C252%^t%^C231%^e "+
	"wal%^C249%^l%^C231%^ed k%^C250%^e%^C231%^ep "+
	"hal%^C251%^l%^C231%^way%^CRST%^");
    set_name("white walled keep hallway");
    set_long("%^C248%^The halls inside the keep are wide "+
	"enough for seven %^C245%^armored men%^C248%^ to march "+
	"side by side without touching and have obviously been "+
	"designed for %^C101%^military %^C248%^means over "+
	"comfort. The floors are a %^C245%^heavy flagstone%^C248%^ "+
	"with a threadbare %^C116%^blue carpet%^C248%^. The walls "+
	"are %^C231%^giant white stones%^C248%^, set perfectly "+
	"together without any need for %^C243%^mortar%^C248%^, "+
	"belying the masterful original construction. Along the "+
	"walls %^C242%^iron sconces%^C248%^ hold torches. Every "+
	"once and awhile in the hallway there are %^C100%^"+
	"crates%^C248%^, or %^C058%^supplies%^C248%^, but "+
	"everything has been arranged in %^C214%^military %^C248%^"+
	"precision.%^CRST%^\n");

   set_items(([
      ({"walls"}) : "%^C231%^The walls here are set with giant "+
	  "white stones, each one would have taken a team to even "+
	  "think to move into place.%^CRST%^",
	  ({"carpet"}) : "%^C116%^This rich blue carpet has seen better days. It still muffles the sound of marching, but isn't much for comfort.%^CRST%^",
      ({"sconces"}) : "%^C241%^Simple in design and implementation, these heavy iron sconces can hold a torch to light the hallway.%^CRST%^",
      ({"floor","floors"}) : "%^C246%^The floors here are heavy flagstone.%^CRST%^",
	  ({"crates","supplies"}) : "%^C100%^There are random crates and supplies tucked away in the hallway. Looking over them there isn't anything valuable in them. Each crate is marked with a white sphere over a tower, marking them as Legion of Pearl proerty.%^CRST%^",
    ]));

set_smell("default","%^C247%^You smell %^C244%^dust %^C247%^and %^C100%^torch %^C242%^smoke%^CRST%^");
set_listen("default","%^C058%^You hear activity all around you%^CRST%^");

}

void pick_critters(){
   switch(random(6)){
         case 0:   set_monsters(
({MOBS"legion",MOBS"construct"}),({random(4),random(2)}) );
                   break;
         case 1:   set_monsters(
({MOBS"legion"}),({random(5)}) );
                   break;
         case 2:   set_monsters(
({MOBS"legionoff",MOBS"construct"}),({1,random(1)+1}) );
                   break;
         case 3:   set_monsters(
({MOBS"legion"}),({random(5)}) );
                   break;
         case 4..5: break;
   }
}
