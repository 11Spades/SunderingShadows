
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^large building%^CRST%^ sits to the east.\n");


set_exits(([
"north" : HAVEN"9",
"east" : HAVEN"27",
"southeast" : HAVEN"7",


]));

}

