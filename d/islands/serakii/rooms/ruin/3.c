
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();


   set_exits(([

          "north" : RUINS"4",
          "south" : RUINS"2",
          "east" : RUINS"16",
          "west" : RUINS"15",
   ]));

}
