#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";



void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nTo the northeast of the camp you see a parade ground.%^CRST%^\n");


set_exits(([
"east" : HOUND"5",
"south" : HOUND"2",
"west" : HOUND"6",

]));

}
