
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"11",
"west" : FALLOW"14",
"south" : FALLOW"17",

]));

}

