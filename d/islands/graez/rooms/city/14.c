
#include <std.h>
#include "../../graez.h"

inherit STORAGE"street.c";



void create(){
   ::create();
   set_long(::query_long()+"\nTo the north lays the entrance to the %^C231%^sprawling cathedral complex%^CRST%^ of the %^C231%^Castle de Boquillas%^CRST%^. Its %^C042%^stained glass%^CRST%^ windows gleaming at all hours. The %^C059%^road%^CRST%^ continues to the east and west and south.\n");


set_exits(([
"east" : TOWN"15",
"west" : TOWN"13",
"south" : TOWN"6",
"north" : TOWN"church1",

]));

}
void reset(){
   ::reset();
   if(!present("ambiance device")){
      new(MOBS"rich_ambiance.c")->move(TO);
   }
}

