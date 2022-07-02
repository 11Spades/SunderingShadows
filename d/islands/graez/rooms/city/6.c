
#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the east lays a small %^C060%^warehouse%^CRST%^ and to the west a %^C094%^stable%^CRST%^. You can see the cathedral to the north still, its %^C042%^stained glass%^CRST%^ windows gleaming at all hours. The %^C059%^road%^CRST%^ continues to the east and west and south.\n");


set_exits(([
"east" : TOWN"psion",
"west" : TOWN"stable",
"south" : TOWN"4",
"north" : TOWN"14",

]));

}

