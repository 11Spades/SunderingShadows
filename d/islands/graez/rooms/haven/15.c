
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^small building%^CRST%^ sits to the west..\n");


set_exits(([
"northwest" : HAVEN"14",
"west" : HAVEN"29",
"south" : HAVEN"16",



]));

}
void reset(){
   ::reset();
   if(!present("statue")){
      new(OBJ"statue1.c")->move(TO);
   }
}

