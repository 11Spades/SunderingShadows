// Swamp - LoKi 2022

#include <std.h>
#include "../graez.h"

inherit CROOM;

void create() {

   pick_critters();
   set_repop(60);

   set_terrain(SWAMP);
   set_travel(DECAYED_FLOOR);
   set_property("indoors",0);

   set_name("fetid swamp");
   set_short("fetid swamp");

   set_long("The %^C062%^swamp %^CRST%^stretches out across your vision. The %^C065%^fetid water%^CRST%^ is %^C243%^dark %^CRST%^and you cannot see what might %^C059%^lurk underneath%^CRST%^. %^C064%^Reeds %^CRST%^and %^C034%^lily pads%^CRST%^ extend from the %^C074%^water %^CRST%^showing there is some life here though with the %^C061%^wicked swamp vapors%^CRST%^ around you it is clear you could not survive here for long. Whole swaths of the %^C061%^swamp %^CRST%^as well have been %^C240%^scorched %^CRST%^by what looks like %^C088%^dragon fire%^CRST%^, and in those places life has been laid to %^C059%^waste%^CRST%^. There are %^C060%^ridges %^CRST%^and %^C058%^valleys %^CRST%^everywhere that make passage difficult. The %^C062%^vapor %^CRST%^makes it hard to see too far in the distance but you sense that the whole %^C060%^swamp %^CRST%^is surrounded by %^C240%^mountain ranges%^CRST%^.\n");

   set_items(([
   ({"water","fetid water"}) : "The water around you is only a foot deep but murky the point it is impossible to know what could lurk underneath.\n",
   ({"reeds"}) : "Thick reeds grow from the swamp, scorched here and there where dragon fire has laid them bare but otherwise thriving in the fetid water.\n",
   ({"lily pads"}) : "Large lily pads dot the landscape, providing a splash of vibrant green among the dull grays.\n",

   ]));


   set_smell("default","%^C065%^You smell fetid water and rot.%^CRST%^");
   set_listen("default","%^C060%^You hear the swamp all around you.%^CRST%^");

}

void pick_critters(){
   switch(random(5)){
         case 0:   set_monsters(
({MOBS"hand",MOBS"wolf"}),({random(2),random(3)}) );
                   break;
         case 1:   set_monsters(
({MOBS"wolf"}),({random(3)}) );
                   break;
         case 2:   set_monsters(
({MOBS"hand"}),({random(2)+2}) );
                   break;
         case 3..4: break;
   }
}


