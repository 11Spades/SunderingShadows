

#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"6",
          "south" : RUINS"4",
          "east" : RUINS"20",
          "west" : RUINS"19",

   ]));

}
