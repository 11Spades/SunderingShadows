
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^RESET%^The path diverges here. To the northeast you smell a vague hunt of %^C062%^water%^CRST%^, to the southwest you hear signs of %^C088%^battle%^CRST%^. To the northwest, it is %^C194%^eerily silent%^CRST%^.\n");

set_exits(([
"southwest" : MOUNT"4",
"northeast" : MOUNT"7",
"northwest" : MOUNT"6",

]));

}

