#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^Stairs here lead to the third floor of the tower.%^CRST%^\n");

set_exits(([
"south" : WHITE"12",
"up" : WHITE"16",


]));


}
