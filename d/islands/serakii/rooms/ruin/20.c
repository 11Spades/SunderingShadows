#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([

          "south" : RUINS"18",
          "west" : RUINS"5",
          "east" : RUINS"21",

   ]));

}
