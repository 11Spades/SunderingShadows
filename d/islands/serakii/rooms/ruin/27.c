#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([


          "east" : RUINS"17",
          "north" : RUINS"28",
          "south" : RUINS"26",

   ]));

}
