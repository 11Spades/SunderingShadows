
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"33",
"south" : FALLOW"40",
"west" : FALLOW"35",



]));

}

