
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"15",
"west" : FALLOW"16",
"southeast" : FALLOW"21",
"south" : FALLOW"20",

]));

}

