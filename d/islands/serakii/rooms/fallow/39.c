
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"west" : FALLOW"38",
"southwest" : FALLOW"42",
"northeast" : FALLOW"34",



]));

}

