


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_exits(([

          "southwest" : TOWN"1",
          "east" : TOWN"3",
          "north" : TOWN"4",
   ]));

}

