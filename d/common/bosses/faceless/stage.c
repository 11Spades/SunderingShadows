// Puppet's Stage - LoKi 2022

#include <std.h>
#include "puppet.h"

inherit ROOM;

int triggered, isrunning;
int do_puppet(int mystate);
int is_running();

void create() {
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",1);
    set_property("no_teleport",1);
    set_name("vast stage");
    set_property("light",2);
    set_short("vast stage");
    set_long("%^C058%^You have stepped out onto, strangely, a "+
        "massive %^C060%^stage%^C058%^! The floor here is %^C094%^finely "+
        "laid wood%^C058%^ that has been polished and maintained with care. "+
        "Along the edge of the stage are %^C242%^clamshell metal holders%^C058%^ where "+
        "a %^C160%^flame%^C058%^ would sit to %^C185%^light%^C058%^ up the actors as "+
        "they perform. You cannot see much beyond the stage, if there are seats or "+
        "not, for there is nothing but an %^C238%^impenetrable inky blackness%^C058%^ beyond. "+
        "Deep red carpets have been drawn.\n\nIn the centre of the stage is a solitary unlit candle.%^CRST%^\n");

    set_items(([
      ({"floor"}) : "%^C094%^The floor has been set with fine wood, %^C060%^polished%^C094%^ "+
      "and %^C064%^varnished%^C094%^ to a frozen lake finish.%^CRST%^\n",
      ({"clamshells","lights"}) : "%^C143%^All around the stage are %^C241%^clamshells%^C143%^ facing "+
      "you. They hold a %^C160%^light%^C143%^ so that actors would be well %^C190%^lit%^C143%^ but "+
      "without %^C190%^lighting%^C143%^ the audience.%^CRST%^\n",
      ({"blackness"}) : "%^C238%^beyond the stage is an %^C242%^inky blackness%^C238%^ that you "+
      "cannot enter or see beyond.%^CRST%^\n",
      ({"candle"}) : "A candle sits alone in the centre of the stafe. You could >light< it.%^CRST%^\n",
    ]));


set_smell("default","%^C130%^You smell acrid smoke.%^CRST%^");
set_listen("default","%^C141%^You hear muffled.. laughter?%^CRST%^");

   set_property("no pocket space",1);
   triggered = 0;


   set_exits(([
      "backstage":ROOMS"11.c",
   ]));

}

void init(){
    ::init();
    add_action("light","light");
}


int quit_func(string str) {

   object room,player;

   player = environment(this_object());    
   room = environment(this_player());

   player->move(ROOMS"11");
   tell_object(TP,"%^BOLD%^%^BLUE%^You realize resting here is a bad idea...%^RESET%^");
   player->force_me("quit");
}

int light(string str) {
   object thatroom;
   object room,player;

   player = environment(this_object());    
   room = environment(this_object());
   
    if(str == "candle" || str=="single candle"){
		
		if(triggered == 1){
			tell_object(player,"The candle has already been spent.\n");
		    return 1;
		}
		
        do_puppet(TP,0);
        return 1;}
        else  {tell_object(TP,"Light what?");
                return 1;}
}

int do_puppet(object tp,int mystate) {
   object thatroom;
   object room,player;

   player = environment(this_object());    
   room = environment(this_player());

   switch(mystate) {
     case 0:
       tell_room(room,"%^C058%^You light the candle and step back...\n%^RESET%^");
     break;
     case 1:
       tell_room(room,"%^C240%^You hear a lone solitary clapping, it is exagerated and condesending.\n%^RESET%^");
     break;
     case 2:
       tell_room(room,"%^C100%^A voice speaks from the %^C239%^blackness%^C100%^. '%^C135%^You thought you could remove my puppets from the world, remove my influence from the crowns, and I would skulk away?'\n%^RESET%^");
     break;
     case 3:
       tell_room(room,"%^C100%^A voice speaks from the %^C239%^blackness%^C100%^. '%^C135%^You thought wrong. There is always a stage, and there will always be roles to fill. Perhaps you would like to act for me?'\n%^RESET%^");
     break;
     case 4:
       tell_room(room,"%^C058%^One by one fire erupts from the clamshells around you, bathing the stage in %^C227%^searing hot light%^C058%^. You shield your face from it.\n%^RESET%^");
     break;
     case 5:
       tell_room(room,"%^C100%^A voice speaks from the %^C239%^blackness%^C100%^. '%^C135%^Time to draw the curtains!'%^RESET%^\n");

       
       //Remove Exit

       /*
       if(member_array("backstage",room->query_exits()) != -1) room->remove_exit("backstage");
       thatroom = find_object_or_load(ROOMS"11.c");
       if(member_array("stage",thatroom->query_exits()) != -1) thatroom->remove_exit("stage");
       
       */

       tell_room(thatroom,"Suddenly the exit to the stage vanishes!");



     break;
     case 6:
       tell_room(room,"%^C100%^A voice speaks from the %^C239%^blackness%^C100%^. '%^C135%^Don't worry that you didn't rehearse your lines. I'll speak for you from now on!\n%^RESET%^");
     break;
     case 7:

       // Call avatar

       /*
       tell_room(room," \n%^RESET%^");
       new(MON"puppet")->move(room);
       */


       isrunning = 0;
       return 1;
     break;

     default:
       tell_room(room,"%^BOLD%^%^BLUE%^Something has gone wrong in this room, please notify LoKi.%^RESET%^");
       return 1;
     break;
   }
   mystate++;
   call_out("do_puppet",5,tp,mystate);
   return 1;
}

void reset_cinematics() { triggered = 0; }
int is_running() { return isrunning; }  