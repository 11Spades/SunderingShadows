#include <std.h>
#include "../tharis.h"
inherit STORAGE"bazaar.c";

void create(){
   ::create();
   set_long(::query_long()+" East of here, the road leads to a lovely residential section, the buildings in pristine condition.%^RESET%^\n");
   set_exits(([
      "south" : ROOMS"square6",
      "east" : ROOMS"east1",
      "north" : ROOMS"square8",
      "west" : ROOMS"fountain",
      "northwest" : ROOMS"square1",
      "southwest" : ROOMS"square5",
   ]));
}