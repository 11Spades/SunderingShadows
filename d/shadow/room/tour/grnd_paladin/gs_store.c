#include "/d/shadow/room/city/melnmarn.h"
#include <daemons.h>

inherit ROOM;

void create() {
    ::create();
    set_light(2);
    set_indoors(1);
    set_short("Shadow's General Store");
    set_long(
@MELNMARN
%^BOLD%^You are standing inside of Shadow's Newbie Store%^RESET%^
There are many things on the shelves, and behind the counter. 
Mostly items you would use on your adventures. You can <buy> 
or <sell> items here. Behind the counter, you see a clerk.
MELNMARN
);

    set_items(
	(["shop" : "A general store, actually.",
          "store" : "A place where you can buy and sell stuff.",
	  "counter" : "An worn and battered oak counter. About waist high.",
	  "shelves" : "The shelves are made of oak."]) );
    set_exits( 
	      (["east"	: ROOMDIR+"gs_rd_bk"]) );
    set_property("no castle", 1);
    set_smell("default","The smell of oil lanterns, and rope fills your nostrils.");
    set_listen("default","The sounds of a craftmans tools, fill your ears.");
 }


void init(){
      ::init();
      if(!present("pendaxin",TO))
              new(MONDIR+"pendaxin")->move(TO);

}
