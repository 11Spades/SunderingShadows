#include <std.h>
#include "../../serakii.h"

inherit STORAGE"outside_inn.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C094%^A small path leads around the building.%^CRST%^\n");


set_exits(([

"east" : INN"3",
"southwest" : INN"1",

]));

}

