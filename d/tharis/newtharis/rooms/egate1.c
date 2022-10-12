#include <std.h>
#include "../tharis.h"
inherit CROOM;

void create(){
    ::create();
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",0);
    set_property("light",1);
    set_name("City Gates");
    set_short("%^RESET%^%^C244%^City Gates%^CRST%^");
    set_long("%^RESET%^%^C244%^The %^RESET%^%^C246%^c%^C249%^i%^C252%^t%^C246%^y w%^RESET%^%^C249%^a%^C252%^l%^C249%^l%^RESET%^%^C246%^s %^RESET%^%^C244%^loom high above you, the stones worn smooth with age, making it impossible to find purchase to climb. There are %^RESET%^%^C252%^lighter spots %^RESET%^%^C244%^amongst the massive %^RESET%^%^C246%^s%^C249%^t%^C252%^o%^C250%^n%^RESET%^%^C249%^e%^RESET%^%^C246%^s %^RESET%^%^C244%^where damage has been repaired, %^RESET%^%^C052%^s%^C088%^c%^C124%^a%^C088%^r%^C052%^s %^RESET%^%^C244%^of battles fought long ago. %^RESET%^%^C022%^S%^C028%^p%^C034%^a%^C040%^r%^C028%^s%^C022%^e %^RESET%^%^C022%^v%^C028%^e%^C034%^g%^C040%^e%^C046%^t%^C082%^a%^C040%^t%^C034%^i%^C028%^o%^C022%^n %^RESET%^%^C244%^fights for survival along the base of the walls, which are manned by %^RESET%^%^C240%^soldiers%^RESET%^%^C244%^, %^RESET%^%^C058%^archers%^RESET%^%^C244%^, and %^RESET%^%^C045%^g%^C051%^o%^C087%^l%^C123%^e%^C051%^m%^C045%^s %^RESET%^%^C244%^that keep an eye out for any signs of trouble around the perimeter of the city and the %^RESET%^%^C240%^i%^C241%^m%^C242%^p%^C243%^o%^C244%^s%^C242%^i%^C241%^n%^C240%^g g%^RESET%^%^C241%^a%^C242%^t%^C241%^e%^C240%^s%^RESET%^%^C244%^.%^CRST%^\n");
    set_smell("default","%^RESET%^%^CRST%^%^C141%^The air carries a thousand scents of a busy city.%^CRST%^");
    set_listen("default","%^RESET%^%^CRST%^%^C099%^You hear the bustle of the citizens going about their day.%^CRST%^");

    set_exits(([
      "east" : ROOMS"egate2",
      "west" : ROOMS"elf4",
    ]));
    set_items (([
      "fortress" : "%^RESET%^%^C244%^Above the city looms the ever-present %^RESET%^%^C241%^Shadovar fortress%^RESET%^%^C244%^, casting the entire area into a state of perpetual %^RESET%^%^C057%^t%^C056%^w%^C055%^i%^C063%^l%^C062%^i%^C063%^g%^C055%^h%^C057%^t%^RESET%^%^C244%^.%^CRST%^",
      "walls" : "%^RESET%^%^C244%^The walls themselves are old but sturdy, made up from giant blocks of %^RESET%^%^C246%^g%^C247%^r%^C248%^a%^C249%^n%^C248%^i%^C247%^t%^C246%^e %^RESET%^%^C244%^precisely cut and fit together.%^CRST%^",
      ({"cobblestones", "street", "road", "ground"}): "%^RESET%^%^CRST%^%^C244%^The streets here are freshly lain %^RESET%^%^C249%^cobblestones%^RESET%^%^C244%^, mostly in m%^RESET%^%^C246%^o%^C247%^t%^C249%^t%^C247%^l%^C246%^e%^C244%^d shades of %^RESET%^%^C249%^gray%^RESET%^%^C244%^. However, swaths of them have been painted with a %^RESET%^%^C022%^v%^C028%^e%^C029%^r%^C035%^d%^C041%^a%^C035%^n%^C029%^t %^RESET%^%^C028%^g%^C022%^l%^C028%^a%^C029%^z%^C035%^e%^RESET%^%^C244%^, making them stand out amongst the rest.%^CRST%^",
      "gates" : "%^RESET%^%^C241%^Imposing gates forged from a %^RESET%^%^C240%^black metal %^RESET%^%^C241%^buffed to a %^RESET%^%^C244%^m%^C245%^i%^C246%^r%^C247%^r%^C245%^o%^RESET%^%^C244%^r s%^C245%^h%^C246%^e%^C245%^e%^C246%^n %^RESET%^%^C241%^feature a %^RESET%^%^C240%^shade%^RESET%^%^C241%^-shrouded %^RESET%^%^C246%^knight %^RESET%^%^C241%^astride a rearing %^RESET%^%^C240%^n%^C241%^i%^C242%^g%^C243%^h%^C244%^t%^C160%^m%^C124%^a%^C088%^r%^C052%^e%^RESET%^%^C241%^. Surrounding the pair are tendrils of %^RESET%^%^C240%^darkness%^RESET%^%^C241%^, the tortured faces of the %^RESET%^%^C088%^d%^C124%^a%^C160%^m%^C196%^n%^C124%^e%^C088%^d %^RESET%^%^C241%^caught within. The surface of the gates are adorned with %^RESET%^%^C253%^r%^C252%^a%^C251%^z%^C252%^o%^C253%^r%^RESET%^%^C241%^-sharp %^RESET%^%^C240%^spikes%^RESET%^%^C241%^, stained with old %^RESET%^%^C052%^blood%^RESET%^%^C241%^, and crawling with %^RESET%^%^C241%^a%^C242%^n%^C243%^i%^C244%^m%^C243%^a%^C242%^t%^RESET%^%^C241%^e s%^C242%^h%^C243%^a%^C244%^d%^C242%^o%^C241%^w%^RESET%^%^C241%^. The gates give off an unnatural %^RESET%^%^C051%^c%^C087%^h%^C123%^i%^C087%^l%^C051%^l%^RESET%^%^C241%^, a layer of %^RESET%^%^C087%^r%^C123%^i%^C159%^m%^C087%^e %^RESET%^%^C241%^coating the %^RESET%^%^C240%^d%^C241%^a%^C242%^r%^C240%^k m%^RESET%^%^C241%^e%^C242%^t%^C241%^a%^RESET%^%^C240%^l%^RESET%^%^C241%^.%^CRST%^",
    ]));
}

void reset(){
    ::reset();
    if(!present("golem")){new("/d/tharis/newtharis/mobs/bladegolem.c")->move(TO);}
}

void init() {
    ::init();
    if(!present("tharisambiancexxx",TP)) new(OBJ"ambiance")->move(TP);
}