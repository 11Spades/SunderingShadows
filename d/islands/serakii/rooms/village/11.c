


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_exits(([


                  "northeast" : ROAD"11",
		  "west" : TOWN"12",
		  "south" : TOWN"10",
		  "southwest" : TOWN"13",


   ]));

}


