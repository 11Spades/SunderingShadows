
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"southwest" : FALLOW"5",
"east" : FALLOW"7",


]));

}

