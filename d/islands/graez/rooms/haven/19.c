
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nOn either side of the %^C058%^road%^CRST%^ are %^C244%^empty lots%^CRST%^, with the start of %^C094%^home construction%^CRST%^ in them..\n");
   

set_exits(([
"west" : HAVEN"20",
"east" : HAVEN"18",

]));

}

