
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_tent.c";



void create(){
   ::create();
   set_long(::query_long()+"%^C058%^\nThis tent has "+
   "been crammed full of %^C094%^storage crates%^C058%^, "+
   "each bearing the seal of the %^C242%^"+
   "hounds%^C058%^.%^CRST%^\n");


set_exits(([
"out" : HOUND"2",

]));

add_item("crates", "%^C095%^These crates "+
		"are %^C242%^nailed %^C095%^shut and heavy. On each is "+
		"a symbol of a wolf's paw.%^CRST%^");


}

void reset(){
   ::reset();
   if(!present("johann")){
      new(MOBS"johann.c")->move(TO);
   }
}
