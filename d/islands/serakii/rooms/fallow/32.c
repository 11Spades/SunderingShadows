
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"northeast" : FALLOW"28",
"east" : FALLOW"33",
"south" : FALLOW"35",


]));

}

