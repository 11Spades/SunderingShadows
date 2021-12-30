#include <std.h>
#include "../../serakii.h"

inherit LIBRARY;

void create() {
    ::create();
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("light",2);
    set_property("indoors",1);
    set_name("The Library of Kismet, main rotunda");
    set_short("%^C060%^The Library of %^C034%^Kismet"+
        "%^C060%^, %^C059%^main rotunda%^CRST%^");
    set_long("You are in an %^C045%^impossibly large%^CRST%^ "+
        "space for having just entered from the %^C060%^stairs%^CRST%^ "+
        "of the %^C247%^fortress%^CRST%^. Above you %^C094%^bookshelves%^CRST%^ "+
        "rise into %^C038%^infinity%^CRST%^, with %^C094%^walkways%^CRST%^ "+
        "and %^C094%^stairs%^CRST%^ crossing back and forth in dizzying "+
        "magnitude. The %^C094%^bookshelves%^CRST%^ all around you are "+
        "a %^C095%^deep mahogany%^CRST%^ and polished to a shine, each packed "+
        "to the brim with %^C059%^books%^CRST%^ of all sizes. On the "+
        "%^C247%^ground floor%^CRST%^ of the library the floor itself is "+
        "a %^C029%^thick deep green carpet%^CRST%^. Large %^C124%^comfortable "+
        "couches%^CRST%^ are arranged around a %^C111%^large fountain%^CRST%^ "+
        "with %^C034%^ferns%^CRST%^ arranged around it. Everywhere in the libray "+
        "you see %^C220%^songbirds%^CRST%^. Some are small, others are extremely "+
        "large and can be seen carrying %^C094%^books%^CRST%^ from spot "+
        "to spot.\n");

    set_items(([
      ({"floor","rug"}) : "This rich thick rug is %^C028%^green%^CRST%^, the "+
      "shade of %^C029%^peridot%^CRST%^. It %^C060%^muffles%^CRST%^ the sound "+
      "as you move and adds a sense of %^C022%^comfort%^CRST%^ to this impossibly large space.\n",
      ({"books","bookshelves"}) : "The %^C095%^infinite bookshelves%^CRST%^ are "+
      "each made from a %^C094%^rich mahogany%^CRST%^ and filled with every "+
      "manner of %^C060%^book%^CRST%^. The %^C094%^bookshelves%^CRST%^ themselves "+
      "continue for leagues above you and if you try to concentrate on how far "+
      "up you get %^C044%^dizzy%^CRST%^.\n",
      ({"fountain"}) : "In the middle of the library is a %^C247%^large stone "+
      "fountain%^CRST%^ with two levels. on a ledge around the base of the second "+
      "level are very healthy %^C034%^ferns%^CRST%^. %^C220%^Songbirds%^CRST%^ play "+
      "in and around the %^C111%^fountain%^CRST%^.\n",
      ({"birds","songbirds"}) : "%^C220%^Songbirds%^CRST%^ are everywhere and "+
      "fill the %^C060%^library%^CRST%^ with chirping. From extremely %^C033%^small "+
      "birds%^CRST%^ playing in the %^C111%^fountain%^CRST%^, to %^C173%^dog sized%^CRST%^ birds "+
      "who grab %^C061%^books%^CRST%^ and seemingly refile them in other spots.\n",
      ({"couch","couches"}) : "The %^C124%^couches%^CRST%^ are arranged in small "+
      "groups facing each other so people can discuss the %^C060%^books%^CRST%^ they are reading.\n",
    ]));

    set_smell("default","%^C028%^You smell richly polished wood and books.%^CRST%^");
    set_listen("default","%^C111%^You hear songbirds and the fountain.%^CRST%^");

    set_exits(([


        "stairs" : CAER"foyer",

    ]));


}


void init(){
    ::init();
    add_action("func_sit", "sit");

}


int func_sit(string str)
{

    if (str == "couch") {
        tell_object(TP, "%^C124%^You sink down onto one of the many comfortable" +
                    " couches that are scattered about the room.%^CRST%^");
        tell_room(ETP, "%^C124%^" + TP->query_cap_name() + " %^C124%^sinks down onto one of" +
                  " the many comfortable couches.%^CRST%^", TP);
        return 1;
    }
return 0;
}

void reset(){
   ::reset();
   if(!present("archivist")){
      new(MOBS"ada.c")->move(TO);
   }
}
