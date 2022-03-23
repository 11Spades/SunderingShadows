
#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the north lays the %^C231%^sprawling cathedral complex%^CRST%^ of the %^C231%^Castle de Boquillas%^CRST%^. Its %^C042%^stained glass%^CRST%^ windows gleaming at all hours. to the south is a %^C094%^small pub%^CRST%^. The %^C059%^road%^CRST%^ continues to the east and west.\n");


set_exits(([
"east" : TOWN"13",
"west" : TOWN"12",
"south" : TOWN"pub",

]));

}

