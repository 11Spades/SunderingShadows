#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C247%^To the north is a small set of stairs up.%^CRST%^\n");

set_exits(([
"southwest" : WHITE"21",
"southeast" : WHITE"18",
"north" : WHITE"23",



]));



}
