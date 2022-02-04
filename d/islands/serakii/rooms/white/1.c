#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C247%^The Main foyer of the keep "+
   "sprawls before you. A %^C231%^giant banner%^C247%^ hangs "+
   "from%^C247%^ a %^C247%^second floor balcony and the halls lead to the "+
   "%^C241%^northwest %^C247%^and %^C241%^northeast%^CRST%^\n");


set_exits(([
"northeast" : WHITE"2",
"northwest" : WHITE"3",
"gates" : ROAD"7",

]));

add_item("banner", "%^C246%^Hanging from a second floor "+
"balcony, this banner is giant. It is %^C116%^blue "+
"%^C246%^and on it is a %^C231%^giant white "+
"sphere%^C246%^ in front of a %^C241%^gray "+
"tower%^C246%^. It is heavy enough that no "+
"wind can move it.%^CRST%^");


}
