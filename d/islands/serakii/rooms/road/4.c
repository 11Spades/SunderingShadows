#include <std.h>
#include "../../serakii.h"

inherit STORAGE"trade_road.c";



void create(){
   ::create();
   set_long(::query_long()+"\nSome fields lay to the south.\n");


set_exits(([

"northwest" : ROAD"1",
"south" : FALLOW"1",



]));

}
