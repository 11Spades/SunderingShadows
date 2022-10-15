#include <std.h>
#include "../tharis.h"
inherit STORAGE"bazaar.c";

void create(){
   ::create();
   set_long(::query_long()+"%^RESET%^\n");
   set_exits(([
      "north" : ROOMS"square7",
      "west" : ROOMS"square5",
      "northwest" : ROOMS"fountain",
   ]));
}

void reset(){
  ::reset();
  if(!present("wood vendor")) new(MOBS"wood_vendor.c")->move(TO);
}
