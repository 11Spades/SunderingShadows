
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_name("inside a large desolate building");
   set_short("%^C058%^inside a large %^C244%^desolate%^C058%^ building%^CRST%^");

   set_property("indoors",1);
   set_long(::query_long()+"\nThis %^C059%^building%^CRST%^ looks to be a %^C097%^community hall%^CRST%^. It is massive, with high arched ceilings. It is strangely %^C244%^empty%^CRST%^ of.. %^C061%^Community%^CRST%^ though.\n");


set_exits(([
"southeast" : HAVEN"25",
"east" : HAVEN"24",
"south" : HAVEN"22",

]));

}

void reset(){
   ::reset();
   if(!present("statue")){
      new(OBJ"statue6.c")->move(TO);
   }
}

