


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThere is a store to the north that catches your eye.%^CRST%^\n");
   set_exits(([

          "south" : TOWN"3",
          "west" : TOWN"4",
		  "north" : TOWN"junk",
   ]));

}


