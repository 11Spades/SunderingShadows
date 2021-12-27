

#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_camp.c";

void create(){
   ::create();

set_exits(([
"north" : HOUND"24",
"west" : HOUND"26",
"east" : HOUND"23",

]));

}

void reset(){
   ::reset();
   if(!present("catapult")){
      new(OBJ"catapult.c")->move(TO);
   }
}
