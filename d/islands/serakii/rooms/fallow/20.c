
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"east" : FALLOW"21",
"west" : FALLOW"19",
"north" : FALLOW"17",
"south" : FALLOW"26",

]));

}

