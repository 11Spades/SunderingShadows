
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^small building%^CRST%^ sits to the south..\n");
      

set_exits(([
"west" : HAVEN"13",
"south" : HAVEN"29",
"southeast" : HAVEN"15",



]));

}

