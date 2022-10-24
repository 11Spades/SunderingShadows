#include <std.h>
#include "../tharis.h"

inherit ROOM;

void create(){
    ::create();
    set_indoors(1);
    set_light(1);
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_short("%^RESET%^%^C244%^Gulthrun's Armorsmithy%^CRST%^");
    set_long("%^RESET%^%^C058%^The walls of this building are constructed from %^RESET%^%^C246%^g%^C247%^r%^C248%^a%^C249%^n%^C248%^i%^C247%^t%^C246%^e b%^RESET%^%^C247%^r%^C248%^i%^C249%^c%^C247%^k%^RESET%^%^C246%^s%^RESET%^%^C058%^, precisely cut and stacked together. Sturdy %^RESET%^%^C241%^e%^C242%^b%^C243%^o%^C242%^n%^RESET%^%^C241%^y beams %^RESET%^%^C058%^and %^RESET%^%^C241%^posts %^RESET%^%^C058%^support the ceiling, and various %^RESET%^%^C102%^tools %^RESET%^%^C058%^of the trade hang from %^RESET%^%^C240%^iron hooks %^RESET%^%^C058%^along their wooden surfaces. A long %^RESET%^%^C144%^maple worktable %^RESET%^%^C058%^against the back of the shop, covered with armor in various states of creation and repair. On the wall above the table is a %^RESET%^%^C088%^s%^C124%^c%^C160%^a%^C196%^n%^C160%^d%^C124%^a%^C088%^l%^C124%^o%^C160%^u%^C196%^s %^RESET%^%^C230%^poster %^RESET%^%^C058%^featuring a female %^RESET%^%^C102%^Duergar%^RESET%^%^C058%^. Along the perimeter of the room are several stands outfitted in many types of armor, ranging from simple %^RESET%^%^C242%^leather %^RESET%^%^C058%^to %^RESET%^%^C220%^g%^C226%^l%^C227%^e%^C228%^a%^C229%^m%^C227%^i%^C226%^n%^C220%^g f%^RESET%^%^C226%^u%^C227%^l%^C220%^l p%^RESET%^%^C226%^l%^C227%^a%^C226%^t%^C220%^e%^RESET%^%^C058%^. The shop has a sort of orderly chaos about it, clean but a bit disorganized. An %^RESET%^%^C246%^a%^C247%^r%^C248%^c%^C249%^h%^C248%^w%^C247%^a%^C246%^y %^RESET%^%^C058%^in the northeastern corner of the room leads to a %^RESET%^%^C088%^f%^C124%^o%^C160%^r%^C124%^g%^C088%^e %^RESET%^%^C058%^shared with the neighboring smithy.%^CRST%^");
    set_items(([
    ({"tools","worktable"}) : "%^RESET%^%^C124%^P%^C202%^a%^C226%^i%^C046%^n%^C027%^t%^C057%^s%^RESET%^%^C101%^, %^RESET%^%^C094%^d%^C130%^y%^C136%^e%^C241%^s%^RESET%^%^C101%^, %^RESET%^%^C230%^glues%^RESET%^%^C101%^, %^RESET%^%^C130%^corks%^RESET%^%^C101%^, %^RESET%^%^C015%^thread%^RESET%^%^C101%^, and %^RESET%^%^C252%^needles %^RESET%^%^C101%^have been tossed into tightly %^RESET%^%^C144%^woven baskets%^RESET%^%^C101%^, while %^RESET%^%^C094%^bolts of leather %^RESET%^%^C101%^rest beneath the %^RESET%^%^C144%^scarred worktable %^RESET%^%^C101%^and %^RESET%^%^C244%^s%^C245%^c%^C247%^r%^C246%^a%^C245%^p%^RESET%^%^C244%^s of m%^RESET%^%^C245%^e%^C246%^t%^C245%^a%^C244%^l %^RESET%^%^C101%^have been piled in the northwestern corner of the room. Other %^RESET%^%^C102%^tools %^RESET%^%^C101%^of the trade like %^RESET%^%^C248%^s%^C249%^h%^C250%^e%^C251%^a%^C250%^r%^C248%^s %^RESET%^%^C101%^and %^RESET%^%^C244%^hole punches %^RESET%^%^C101%^hang from %^RESET%^%^C240%^iron hooks %^RESET%^%^C101%^protruding from the %^RESET%^%^C241%^posts %^RESET%^%^C101%^that help support the ceiling.%^CRST%^",
    "stands" : "%^RESET%^%^C094%^These sturdy %^RESET%^%^C058%^stands %^RESET%^%^C094%^hold all manner of armor, from a suit of %^RESET%^%^C240%^m%^C241%^a%^C242%^t%^C241%^t%^RESET%^%^C240%^e-black leather%^RESET%^%^C094%^ so dark it seems to absorb all the %^RESET%^%^C228%^l%^C229%^i%^C230%^g%^C229%^h%^C228%^t %^RESET%^%^C094%^around it, to an exquisite shirt of %^RESET%^%^C220%^g%^C226%^o%^C227%^l%^C220%^d%^RESET%^%^C094%^-dipped %^RESET%^%^C248%^chainmail%^RESET%^%^C094%^.%^CRST%^",
    "poster" : "%^RESET%^%^C230%^This %^RESET%^%^C144%^weathered poster %^RESET%^%^C230%^features a very detailed depiction of a %^RESET%^%^C102%^d%^RESET%^%^C103%^u%^C104%^s%^C103%^k%^RESET%^%^C102%^y-skinned Duergar %^RESET%^%^C230%^woman, her %^RESET%^%^C015%^platinum hair %^RESET%^%^C230%^and %^RESET%^%^C015%^beard %^RESET%^%^C230%^meticulously curled. Her plump form is clad only in a %^RESET%^%^C094%^leather apron%^RESET%^%^C230%^, her %^RESET%^%^C103%^voluptuous breasts %^RESET%^%^C230%^barely contained as she hefts a %^RESET%^%^C248%^h%^C249%^a%^C250%^m%^C251%^m%^C250%^e%^C249%^r %^RESET%^%^C230%^in one hand, readying to pound away at a %^RESET%^%^C124%^h%^C160%^o%^C196%^t %^RESET%^%^C202%^i%^C226%^r%^C202%^o%^C196%^n %^RESET%^%^C196%^r%^C160%^o%^C124%^d %^RESET%^%^C230%^she holds against an %^RESET%^%^C247%^anvil%^RESET%^%^C230%^ with a pair of %^RESET%^%^C241%^tongs%^RESET%^%^C230%^. Her %^RESET%^%^C182%^tongue %^RESET%^%^C230%^plays across her %^RESET%^%^C105%^pillow-soft lips %^RESET%^%^C230%^and she winks one heavy-lidded, %^RESET%^%^C231%^milky white eye%^RESET%^%^C230%^.%^CRST%^\n\n                           %^RESET%^%^C160%^Smith's Illustrated%^CRST%^\n                             %^RESET%^%^C160%^A%^C166%^u%^C172%^t%^C178%^u%^C184%^m%^C190%^n%^C226%^s%^C220%^t%^C214%^i%^C208%^m%^C202%^e %^RESET%^%^C196%^7%^C160%^5%^C166%^7%^CRST%^",
     ]));
    set_exits(([
     // "northeast" : ROOMS"forge",
      "west" : ROOMS"industry2"
   ]));
   
    set_smell("default","%^RESET%^%^C101%^The scent of various %^RESET%^%^C178%^m%^C184%^e%^C255%^t%^C249%^a%^C245%^l%^RESET%^%^C241%^s%^RESET%^%^C101%^, %^RESET%^%^C242%^leather%^RESET%^%^C101%^, and %^RESET%^%^C184%^oils %^RESET%^%^C101%^fills the room.%^CRST%^");
    set_listen("default","%^RESET%^%^C144%^You hear the crackle of %^RESET%^%^C088%^f%^C124%^i%^C160%^r%^C088%^e %^RESET%^%^C144%^and a %^RESET%^%^C249%^m%^C250%^u%^C251%^t%^C250%^e%^RESET%^%^C249%^d clanging %^RESET%^%^C144%^coming from the forge.%^CRST%^");
    
    //if(!present("gulthrun"))
   //{
    // new(MOBS"gulthrun_armor.c")->move(TO);
   //}
}

//void reset()
//{
  //::reset();
 // if(!present("gulthrun"))
  //{
   // new(MOBS"gulthrun_armor")->move(TO);
   //}
//}