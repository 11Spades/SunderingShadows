


#include <std.h>
#include "../../serakii.h"

inherit STORAGE"village.c";

void create(){
   ::create();
   set_exits(([

          "north" : TOWN"6",
        "east" : TOWN"8",
        "south" : TOWN"bank",


   ]));
            set_door("double doors",TOWN"bank","south",0);

}


