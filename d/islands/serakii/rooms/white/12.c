#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^To the north you can see stairs leading up.%^CRST%^\n");

set_exits(([
"northwest" : WHITE"11",
"northeast" : WHITE"13",
"north" : WHITE"15",

]));


}
