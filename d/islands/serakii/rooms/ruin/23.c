#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([

          "south" : RUINS"24",
          "west" : RUINS"16",
          "north" : RUINS"22",

   ]));

}
