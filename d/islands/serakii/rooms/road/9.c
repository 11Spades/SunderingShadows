#include <std.h>
#include "../../serakii.h"

inherit STORAGE"trade_road.c";



void create(){
   ::create();


set_exits(([

"east" : ROAD"8",
"northwest" : HOUND"1",
"west" : ROAD"10",
]));

}

