#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();


set_exits(([
"northeast" : WHITE"5",
"south" : WHITE"3",

]));


}
