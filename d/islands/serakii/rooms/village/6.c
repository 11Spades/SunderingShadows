


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_exits(([

          "south" : TOWN"7",
          "east" : TOWN"9",
		  "northwest" : TOWN"3",
		  "northeast" : TOWN"13",
   ]));

}


