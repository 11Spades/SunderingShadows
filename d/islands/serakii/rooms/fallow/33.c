
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"28",
"south" : FALLOW"36",
"west" : FALLOW"32",


]));

}

