


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nTo the northeast you see "+
   "the gates of the town. To the east and north there are "+
   "statues that catch your eye.%^CRST%^\n");
   set_exits(([

		  "southwest" : TOWN"6",
		  "north" : TOWN"12",
		  "east" : TOWN"10",
		  "northeast" : TOWN"11",

   ]));

}


