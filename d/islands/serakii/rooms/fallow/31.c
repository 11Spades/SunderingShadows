
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"northeast" : FALLOW"27",
"southwest" : FALLOW"34",
"northwest" : FALLOW"26",


]));

}

