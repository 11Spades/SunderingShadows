
#include <std.h>
#include "../../graez.h"

inherit STORAGE"mountain.c";



void create(){
   ::create();

   set_long(::query_long()+"\nTo the northwest %^C094%^tall palisades%^CRST%^ of a %^C059%^settlement%^CRST%^ dominate the %^C075%^skyline%^CRST%^ and there is no way around them. Strangely though, for such %^C094%^tall walls%^CRST%^, the gate is %^C244%^open%^CRST%^...\n");

set_exits(([
"southeast" : MOUNT"16",
"northwest" : HAVEN"1",

]));

}

