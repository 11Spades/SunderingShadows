#include <std.h>
#include "../../serakii.h"

inherit STORAGE"tree_lined.c";

void create(){
   ::create();

   set_long(::query_long()+"\n%^C124%^To the east is a massive red stone tower%^CRST%^\n");


   set_exits(([

          // "east" : BLACK"1",
         "west" : RUINS"9",

   ]));

}
