
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"north" : FALLOW"37",
"south" : FALLOW"44",
"east" : FALLOW"42",




]));

}

