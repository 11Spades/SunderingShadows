#include <std.h>
#include "../../serakii.h"

inherit STORAGE"ruins.c";

void create(){
   ::create();


   set_exits(([


          "west" : RUINS"25",
         "southeast" : RUINS"11",
          "north" : RUINS"15"

   ]));

}
