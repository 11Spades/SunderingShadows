


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThere is a store to the south that catches your eye.%^CRST%^\n");
   set_exits(([

          "north" : TOWN"9",
          "east" : TOWN"14",
		  "west" : TOWN"7",
		  "south" : TOWN"item",

   ]));

}


