i

#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"south" : FALLOW"29",
"northeast" : FALLOW"18",


]));

}

