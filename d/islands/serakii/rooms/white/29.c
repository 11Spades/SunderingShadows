#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_hall.c";



void create(){
   ::create();

   set_long(::query_long()+"\n%^C249%^There is a large %^C245%^opening %^C249%^here to the %^C111%^outside%^C249%^. The %^C244%^opening %^C249%^is angled so from inside the tower you have a clear view in any direction but are still protected from %^C063%^outside %^C249%^attacks.%^CRST%^\n");

set_exits(([
"west" : WHITE"28",
"north" : WHITE"25",
"east" : WHITE"30",

]));


}

void reset(){
   ::reset();
   if(!present("arbalest")){
      new(OBJ"legion_arbalest.c")->move(TO);
   }
}
