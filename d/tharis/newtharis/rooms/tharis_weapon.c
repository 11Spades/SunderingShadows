#include <std.h>
#include "../tharis.h"

inherit ROOM;

void create(){
    ::create();
    set_indoors(1);
    set_light(1);
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_short("%^RESET%^%^C244%^Bergrom's Weaponsmithy%^CRST%^");
    set_long("%^RESET%^%^C144%^The walls of this building are constructed from %^RESET%^%^C246%^g%^C247%^r%^C248%^a%^C249%^n%^C248%^i%^C247%^t%^C246%^e b%^RESET%^%^C247%^r%^C248%^i%^C249%^c%^C247%^k%^RESET%^%^C246%^s%^RESET%^%^C144%^, precisely cut and stacked together. Sturdy %^RESET%^%^C241%^e%^C242%^b%^C243%^o%^C242%^n%^RESET%^%^C241%^y beams %^RESET%^%^C144%^and %^RESET%^%^C241%^posts %^RESET%^%^C144%^support the ceiling, and various %^RESET%^%^C102%^tools %^RESET%^%^C144%^of the trade hang from %^RESET%^%^C240%^iron hooks %^RESET%^%^C144%^along their wooden surfaces. A long %^RESET%^%^C094%^wooden worktable%^RESET%^%^C144%^ is located near the back of the shop, %^RESET%^%^C246%^w%^C247%^e%^C248%^a%^C249%^p%^C248%^o%^C247%^n%^C246%^s %^RESET%^%^C144%^in various states of creation and repair resting upon its surface. Along the eastern wall are multiple %^RESET%^%^C094%^weapon racks %^RESET%^%^C144%^and %^RESET%^%^C087%^d%^C123%^i%^C159%^s%^C195%^p%^C159%^l%^C123%^a%^C087%^y c%^RESET%^%^C123%^a%^C159%^s%^C123%^e%^RESET%^%^C087%^s%^RESET%^%^C144%^, razor-sharp %^RESET%^%^C136%^spears%^RESET%^%^C144%^, %^RESET%^%^C246%^axes%^RESET%^%^C144%^, %^RESET%^%^C252%^swords%^RESET%^%^C144%^, and much more resting within, awaiting their future owners. The shop is orderly and tidy, everything having its place and appearing well cared for. An %^RESET%^%^C246%^a%^C247%^r%^C248%^c%^C249%^h%^C248%^w%^C247%^a%^C246%^y %^RESET%^%^C144%^in the southeastern corner of the room leads to a %^RESET%^%^C088%^f%^C124%^o%^C160%^r%^C124%^g%^C088%^e %^RESET%^%^C144%^shared with the neighboring smithy.%^CRST%^");
    set_items(([
    ({"tools","worktable"}) : "%^RESET%^%^C249%^Metal ingots%^RESET%^%^C101%^, %^RESET%^%^C247%^moulds%^RESET%^%^C101%^, %^RESET%^%^C136%^wires%^RESET%^%^C101%^, %^RESET%^%^C245%^nails%^RESET%^%^C101%^, %^RESET%^%^C244%^bolts%^RESET%^%^C101%^, and strips of %^RESET%^%^C242%^leather %^RESET%^%^C101%^are separated and neatly stored into tightly %^RESET%^%^C144%^woven baskets%^RESET%^%^C101%^, while %^RESET%^%^C058%^wooden shafts %^RESET%^%^C101%^and handles of various lengths are neatly stacked underneath the %^RESET%^%^C094%^scarred worktable%^RESET%^%^C101%^. Other %^RESET%^%^C102%^tools %^RESET%^%^C101%^of the trade like %^RESET%^%^C248%^h%^C249%^a%^C250%^m%^C251%^m%^C250%^e%^C249%^r%^C248%^s %^RESET%^%^C101%^and %^RESET%^%^C244%^files %^RESET%^%^C101%^hang from %^RESET%^%^C240%^iron hooks %^RESET%^%^C101%^protruding from the %^RESET%^%^C241%^posts %^RESET%^%^C101%^that help support the ceiling.%^CRST%^",
    ({"cases","weapon racks", "racks"}) : "%^RESET%^%^C136%^Display cases made of %^RESET%^%^C087%^g%^C123%^l%^C159%^a%^C123%^s%^C087%^s %^RESET%^%^C136%^and %^RESET%^%^C248%^m%^C249%^e%^C250%^t%^C249%^a%^C248%^l %^RESET%^%^C136%^as well as %^RESET%^%^C094%^weapon racks %^RESET%^%^C136%^line the shop walls, exhibiting the various %^RESET%^%^C246%^w%^C247%^e%^C248%^a%^C249%^p%^C248%^o%^C247%^n%^C246%^s %^RESET%^%^C136%^for sale.%^CRST%^",
     ]));
    set_exits(([
      //"southeast" : ROOMS "forge",
      "west" : ROOMS "industry4"
   ]));
   
    set_smell("default","%^RESET%^%^C094%^The scent of various %^RESET%^%^C178%^m%^C184%^e%^C255%^t%^C249%^a%^C245%^l%^RESET%^%^C241%^s%^RESET%^%^C094%^, %^RESET%^%^C242%^leather%^RESET%^%^C094%^, and %^RESET%^%^C184%^oils %^RESET%^%^C094%^fills the room.%^CRST%^");
    set_listen("default","%^RESET%^%^C136%^You hear the crackle of %^RESET%^%^C088%^f%^C124%^i%^C160%^r%^C088%^e %^RESET%^%^C136%^and a %^RESET%^%^C249%^m%^C250%^u%^C251%^t%^C250%^e%^RESET%^%^C249%^d clanging %^RESET%^%^C136%^coming from the forge.%^CRST%^");
    
   //if(!present("bergrom"))
   //{
     // new(MOBS"bergrom.c")->move(TO);
  // }
}

//void reset()
//{
  // ::reset();
  // if(!present("bergrom"))
  // {
    //  new(MOBS"bergrom")->move(TO);
  // }
//}