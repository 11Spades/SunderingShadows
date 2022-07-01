
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
  ::create();
  set_long(::query_long()+"\nYou are faced with a %^C059%^ridge%^CRST%^, and %^C065%^fetid water%^CRST%^ sloshes down it in a %^C023%^slow waterfall%^CRST%^, you could %^C067%^>slide<%^CRST%^ here, but you have no clue where you might turn up..\n");


set_exits(([

"northwest" : SWAM"6",
"east" : SWAM"16",


]));

}
void init() {
	::init();
	add_action("slide_func", "slide");
}


int slide_func(string str,object who){

        object player, room;

	player = this_object();
	room = environment(player);

   tell_room(room,"%^C066%^With a %^C073%^yelp%^C066%^,%^CRST%^ "+player+"%^C066%^ slips on a slick rock and disappears into the water and muck!%^CRST%^\n",player);
   tell_object(player,"%^C066%^You step over to the edge of the %^C059%^ridge%^C066%^ to see if it's safe to slide. At the last moment though you slip on a %^C243%^rock %^C066%^and slide.\n%^CRST%^");
   tell_object(player,"%^C101%^You tumble through the %^C075%^water%^C101%^, past %^C068%^fetid waters%^C101%^ and down until you tumble to a stop at a lower spot in the %^C060%^swamp%^CRST%^%^C101%^!\n");
	TP->move_player(SWAM"22.c");
	return 1;
}

