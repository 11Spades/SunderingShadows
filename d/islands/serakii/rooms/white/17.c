#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^To the north you can see stairs leading down.%^CRST%^\n");


set_exits(([
"north" : WHITE"16",
"northeast" : WHITE"18",
"northwest" : WHITE"22",



]));



}
