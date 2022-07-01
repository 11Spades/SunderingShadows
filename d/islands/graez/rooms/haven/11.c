
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_long(::query_long()+"\nA %^C060%^large building%^CRST%^ sits to the south.\n");


set_exits(([
"west" : HAVEN"10",
"southeast" : HAVEN"12",
"south" : HAVEN"26",



]));

}
void reset(){
   ::reset();
   if(!present("statue")){
      new(OBJ"statue4.c")->move(TO);
   }
}

