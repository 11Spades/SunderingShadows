#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"c1",
          "west" : RUINS"8",
          "east" : RUINS"6",

   ]));

}
