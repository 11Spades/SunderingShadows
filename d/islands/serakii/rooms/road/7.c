#include <std.h>
#include "../../serakii.h"

inherit STORAGE"trade_road.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C252%^Before you stands the walls of a massive white stone fortress. The gates are open.%^CRST%^\n");

   set_items(([
       ({"walls","fortress"}) : "%^C247%^The walls of this %^C243%^fortress %^C247%^tower over you. The stones that form it are each larger than a %^C058%^wagon %^C247%^each and would have been a super human effort to place them. The walls themselves are at least six hundred feet high and you can barely see the top of them.\n%^CRST%^",
       ]));

set_exits(([

"south" : ROAD"6",
"gates" : WHITE"1",
]));

}
