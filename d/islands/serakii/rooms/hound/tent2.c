#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_tent.c";



void create(){
   ::create();
   set_long(::query_long()+"\n%^C094%^A desk dominates "+
   "this %^C246%^tent %^C094%^and is crammed "+
   "with %^C251%^paperwork %^C094%^and "+
   "%^C039%^maps%^C094%^.%^CRST%^\n");


set_exits(([
"out" : HOUND"12",

]));

add_item("desk", "%^C095%^%^C094%^A desk dominates "+
   "this %^C246%^tent %^C094%^and is crammed "+
   "with %^C251%^paperwork %^C094%^and "+
   "%^C039%^maps%^C094%^.%^CRST%^\n");

}

void reset(){
   ::reset();
   if(!present("sienna")){
      new(MOBS"sienna.c")->move(TO);
   }
}
