#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([

          "west" : RUINS"3",
          "north" : RUINS"18",
          "east" : RUINS"23",
          "south" : RUINS"14",

   ]));

}
