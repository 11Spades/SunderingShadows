#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"20",
          "east" : RUINS"22",
          "south" : RUINS"16",

   ]));

}
