


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_long(::query_long()+"\n%^C058%^There is a squat building to the west.%^CRST%^\n");
   set_exits(([

         "west" : TOWN"dojo",
          "south" : TOWN"2",
          "east" : TOWN"5",
   ]));

}


