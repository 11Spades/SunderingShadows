
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^large building%^CRST%^ sits to the west. and %^C060%^another%^RESET%^ to the south.\n");


set_exits(([
"west" : HAVEN"26",
"northwest" : HAVEN"11",
"south" : HAVEN"24",
"east" : HAVEN"13",



]));

}

