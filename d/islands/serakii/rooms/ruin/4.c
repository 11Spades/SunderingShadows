
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"5",
          "south" : RUINS"3",

   ]));

}
