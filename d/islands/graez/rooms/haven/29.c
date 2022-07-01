
#include <std.h>
#include "../../graez.h"

inherit STORAGE"haven.c";



void create(){
   ::create();
   set_name("inside a small building");
   set_short("%^C058%^inside a small %^C244%^desolate%^C058%^ building%^CRST%^");
   
   set_property("indoors",1);
   set_long(::query_long()+"\nThis %^C059%^building%^CRST%^ looks like it was originally going to be a %^C028%^herbalist's%^CRST%^ with fresh %^C041%^herbs%^CRST%^ and %^C167%^flowers%^CRST%^ hung to dry.\n");



set_exits(([
"north" : HAVEN"14",
"east" : HAVEN"15",

]));

}
void reset(){
   ::reset();
   if(!present("statue")){
     new(OBJ"statue5.c")->move(TO);
   }
}

