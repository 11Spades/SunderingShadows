#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C246%^\nThe ground here "+
   "has a %^C055%^ha%^C199%^z%^C055%^e of "+
   "mia%^C128%^s%^C055%^ma%^C246%^ that "+
   "hangs from it, seeming to come from "+
   "a %^C094%^tent%^C246%^ to the "+
   "north...\n%^CRST%^");

set_exits(([
"northeast" : HOUND"15",
"northwest" : HOUND"18",
"south" : HOUND"6",

]));

}
