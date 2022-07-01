
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
  ::create();
  set_long(::query_long()+"\nYou are faced with a %^C059%^ridge%^CRST%^, and there are a enough %^C022%^larger plants%^CRST%^ and %^C064%^slick rocks%^CRST%^ you probably %^C067%^>climb<%^CRST%^ but its hard to tell what is above you..\n");

set_exits(([

"east" : SWAM"40",

]));

}

void init() {
	::init();
	add_action("climb_func", "climb");
}


int climb_func(string str,object who){

   object player, room;

   player = this_object();
   room = environment(player);

   tell_object(player,"%^C143%^You walk up to the %^C059%^ridge %^C143%^and find some %^C239%^rocks %^C143%^and %^C034%^vegetation %^C143%^you can grasp.%^CRST%^\n%^CRST%^");
   tell_room(room,"%^C143%^With a %^C059%^resolute %^C143%^look,%^CRST%^ "+player+" %^C143%^grasps onto whatever they can in the %^C034%^vegitation %^C143%^and climbs out of sight.%^CRST%^\n",player);
   tell_object(player,"%^C143%^You climb for some time and arrive higher up in the %^C101%^swamp%^C143%^!%^CRST%^\n");
   TP->move_player(SWAM"9.c");
   return 1;
}


void reset(){
   ::reset();
   if(!present("minotaur")){
      new(MOBS"minotaur.c")->move(TO);
   }
}

