#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";



void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThe Military Camp sprawls to the north of you and dominates the whole area.%^CRST%^\n");


set_exits(([
"north" : HOUND"2",
"southeast" : ROAD"9",

]));

}
