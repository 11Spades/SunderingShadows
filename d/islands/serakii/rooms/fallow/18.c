
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"east" : FALLOW"19",
"southwest" : FALLOW"24",
"south" : FALLOW"25",

]));

}

