
#include <std.h>
#include "../../graez.h"

inherit STORAGE"ruins.c";


void create(){
   ::create();

   set_long(::query_long()+"%^C058%^\nThis building must have been a warehouse of supplies and a workshop of some kind. Sprawling piles of melted armor lay everywhere.%^CRST%^\n");

   set_exits(([
        "southeast":TOWN"smith",
        "northeast":TOWN"weapons",
    ]));

}
