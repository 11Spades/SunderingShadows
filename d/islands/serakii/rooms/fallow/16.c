
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"14",
"east" : FALLOW"17",
"south" : FALLOW"19",

]));

}

