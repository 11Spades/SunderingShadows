
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"east" : FALLOW"22",
"west" : FALLOW"20",
"northwest" : FALLOW"17",


]));

}

