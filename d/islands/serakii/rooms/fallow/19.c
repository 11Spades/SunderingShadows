
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"east" : FALLOW"20",
"west" : FALLOW"18",
"north" : FALLOW"16",

]));

}

