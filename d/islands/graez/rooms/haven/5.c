
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^small building%^CRST%^ sits to the east..\n");


set_exits(([
"north" : HAVEN"6",
"east" : HAVEN"21",
"southeast" : HAVEN"4",

]));

}

