#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();

   set_long(::query_long()+"\n%^C241%^To the west is a massive black stone tower%^CRST%^\n");


   set_exits(([

          // "west" : RED"1",
         "east" : RUINS"7",

   ]));

}
