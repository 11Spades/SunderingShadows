
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"west" : FALLOW"3",
"east" : FALLOW"5",
"south" : FALLOW"11",


]));

}

