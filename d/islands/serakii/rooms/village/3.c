


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_long(::query_long()+"\n%^C066%^There is a building complex to the south.%^CRST%^\n");
   set_exits(([

          "north" : TOWN"5",
          "west" : TOWN"2",
          "southeast" : TOWN"6",
         "south" : TOWN"institute",
   ]));

}


