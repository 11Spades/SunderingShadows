#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nThe road continues north and south here. On the east you see what looks like a %^C095%^general %^CRST%^store and to the west a %^C220%^bank%^CRST%^.%^CRST%^\n");


set_exits(([
"east" : TOWN"general",
"west" : TOWN"bank",
"north" : TOWN"6",
"south" : TOWN"1",

]));

}

