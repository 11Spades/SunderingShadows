
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"west" : FALLOW"13",
"south" : FALLOW"16",
"northeast" : FALLOW"11",
"east" : FALLOW"15",

]));

}

