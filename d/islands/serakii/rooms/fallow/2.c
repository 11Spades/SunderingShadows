#include <std.h>
#include "../../serakii.h"

inherit STORAGE"fallow_field.c";



void create(){
   ::create();


set_exits(([

"west" : FALLOW"1",
"south" : FALLOW"9",
]));

}
