#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThere is a large tent to "+
   "the southwest larger than all the rest.%^CRST%^\n");

set_exits(([

"north" : HOUND"27",
"tent" : HOUND"tent4",
"east" : HOUND"25",

]));

}
