#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^Stairs here lead to the second floor of the tower%^CRST%^\n");

set_exits(([
"north" : WHITE"5",
"up" : WHITE"8",

]));


}
