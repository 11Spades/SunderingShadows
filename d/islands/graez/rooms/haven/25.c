
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_name("inside a large desolate building");
   set_short("%^C058%^inside a large %^C244%^desolate%^C058%^ building%^CRST%^");

   set_property("indoors",1);
   set_long(::query_long()+"\nThis part of the %^C061%^community hall%^CRST%^ was obviously meant to be the %^C193%^chapel%^CRST%^. A %^C094%^large altar%^CRST%^ rests to the side and %^C094%^freshly constructed pews%^CRST%^ line the room with precision.\n");
   

set_exits(([
"northwest" : HAVEN"23",

]));

}
void reset(){
   ::reset();
   if(!present("medusa")){
      new(MOBS"medusa.c")->move(TO);
   }
}


