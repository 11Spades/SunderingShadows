#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^To the South you can see stairs leading down.%^CRST%^\n");

set_exits(([
"south" : WHITE"8",
"southwest" : WHITE"10",
"southeast" : WHITE"14",

]));


}
