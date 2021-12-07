#include <std.h>
#include "../../serakii.h"

inherit STORAGE"white_room.c";



void create(){
   ::create();



set_exits(([
"east" : WHITE"25",


]));

    set_door("wooden door",WHITE"25","east",0);
    set_door_description("wooden door","%^C094%^Formed from solid wood, this door looks very"+
" heavy. An %^C243%^iron ring%^C094%^ hands from it to allow it to be opened.");
    set_string("wooden door", "open", "%^C094%^You push against the heavy door and it opens slowly.%^CRST%^");
    set_string("wooden door", "close", "%^C094%^You close the heavy wooden door slowly%^RESET%^%^BOLD%^.");



}

 void reset(){
   ::reset();
   if(!present("brock")){
      new(MOBS"brock.c")->move(TO);
   }
}
