#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThere is a large tent to "+
   "the northeast larger than all the rest.%^CRST%^\n");

set_exits(([
"tent" : HOUND"tent2",
"west" : HOUND"13",
"south" : HOUND"11",

]));

}
