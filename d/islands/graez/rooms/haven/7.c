
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^large building%^CRST%^ sits to the east. and %^C060%^another%^RESET%^ to the north.\n");


set_exits(([
"north" : HAVEN"27",
"northwest" : HAVEN"8",
"east" : HAVEN"22",
"south" : HAVEN"6",

]));

}

