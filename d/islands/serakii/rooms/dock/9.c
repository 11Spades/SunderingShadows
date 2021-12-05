
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"dock.c";

void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThe docks end here and you see a mostly "+
   "silent city to the northeast.%^CRST%^\n");

   set_exits(([

	  "west" : DOCK"10",
          "northeast" : TOWN"1",
          "southeast" : DOCK"4",
	  
   ]));

}
