#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"c2",
          "west" : RUINS"6",
          "east" : RUINS"10",

   ]));

}
