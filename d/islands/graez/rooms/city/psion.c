
#include <std.h>
#include "../../graez.h"

inherit STORAGE"warehouse.c";



void create(){
   ::create();
      set_long(::query_long()+"\nThis room is filled with boxes of shattered crystals.\n");


set_exits(([

"west" : TOWN"6",

]));

}
