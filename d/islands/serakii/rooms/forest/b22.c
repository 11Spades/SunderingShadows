#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"west" : FOR"b21",
"northeast" : BONE"1",



]));

	add_item("tower","%^C195%^Before you stands a massive tower constructed entirely of what looks like %^C255%^bone%^C195%^. It's whole surface is un-marred and without windows and rises above the canopy of the %^C066%^'trees'%^C195%^.%^CRST%^");


    set_long(::query_long()+"\n%^C195%^Before you rises a massive tower.%^CRST%^%^CRST%^\n");
}
