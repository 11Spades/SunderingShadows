// Ruins

#include <std.h>
#include "../serakii.h"

inherit CROOM;


object ob;
int count,i;

void create() {
    ::create();
    set_terrain(CITY);
    set_travel(DIRT_ROAD);
    set_property("indoors",0);
    set_name("ruins of a city");
    set_property("light",2);
    set_short("%^C242%^ru%^C060%^"+
	"i%^C242%^ns o%^C060%^f%^C242%^ "+
	"a c%^C061%^i%^C242%^ty%^CRST%^");
    set_long("%^C245%^The whole area around you "+
	"is %^C241%^desolate %^C245%^and %^C088%^heart "+
	"breaking%^C245%^. You are standing in what "+
	"used to be a %^C060%^city%^C245%^, but it was "+
	"destroyed decades ago. Walls of buildings "+
	"stand half-tall, %^C060%^roads %^C245%^are "+
	"torn up, and %^C250%^rubble %^C245%^is "+
	"everywhere. There is a heavy sense of "+
	"%^C055%^sorrow %^C245%^in the area, though "+
	"no sense of actual danger. The %^C244%^"+
	"rubble %^C245%^is thick enough here that "+
	"you could try to %^C099%^>clear< %^C245%^it "+
	"and see what is underneath.%^CRST%^\n");

    set_items(([
    ({"rubble"}) : "%^C059%^The rubble around you "+
	"is deep, though it is small enough pieces "+
	"that you could %^C063%^clear %^C059%^some "+
	"of it to find something underneath.%^CRST%^\n",
    ({"road","walls"}) : "%^C245%^The road and "+
	"walls have been ravaged by some battle or "+
	"calamity that happened decades ago. Why "+
	"hasn't anyone repaired this?%^CRST%^",
    ]));
    
set_smell("default","%^C244%^You smell "+
"%^C241%^dust %^C244%^and %^C060%^rubble%^C244%^"+
".%^CRST%^");
set_listen("default","%^C111%^The %^C062%^wind "+
"%^C111%^whips through the ruins%^CRST%^");

          count = 0;
}

void init(){
   ::init();
   add_action("clear","clear");
}

void clear(string str){
   int roll, might, bonus;
   object obj;
   roll = roll_dice(1,20) + (int)TP->query_skill("athletics");

   bonus = ((int)TP->query_stats("strength")-10)/2 -
((int)TP->query_stats("dexterity")-10)/2;
   if(bonus < 0) bonus = 0;
   roll += bonus;
   if(TP->query_bound() || TP->query_unconcious() || TP->query_paralyzed()
|| TP->query_tripped()){
      TP->send_paralyzed_message("info",TP);
      return 1;
   }
   if(!interactive(TP)) return;
   if(!str) { return 0; }
   if(str != "Rubble" && str != "rubble"){
      tell_object(TP,"clear what?\n");
      return 1;
   }

   if(count > 6){
      tell_object(TP,"All the rubble has been cleared!\n");
      return 1;
   }


   if(roll < 10){
      tell_object(TP,"You dont even know where to start with all this
rubble.");
      tell_room(ETP,""+TPQCN+" looks at the rubble with a frown.",TP);
        TP->set_paralyzed(7,"You are recovering from your efforts.");
      return 1;
   }
   if(roll < 13){
      tell_object(TP,"You move around rubble but aren't making much
progress.");
      tell_room(ETP,""+TPQCN+" seems to dig at the rubble but without
progress.",TP);
        TP->set_paralyzed(5,"You are recovering from your efforts.");
      return 1;
   }
   if(count > 5){
    tell_object(TP,"You finally pull something out of the rubble.");
    tell_room(ETP,""+TPQCN+" pulls something out of the rubble.",TP);


    TP->set_paralyzed(3,"You are recovering from your efforts.");
    count = count+1;

    i = random(7);
    switch(i){
        case 0..2:    // corpse

    {
        object corpse;
        corpse = new("/std/obj/corpse");
        corpse->set_name("human");
        corpse->set_gender(({"male","female"})[random(2)]);
        corpse->set_long("%^CYAN%^Before you is an %^CYAN%^o%^CYAN%^l%^CYAN%^d "+
         "%^CYAN%^c%^BOLD%^%^BLACK%^o%^RESET%^%^CYAN%^r%^BOLD%^%^BLACK%^"+
         "p%^RESET%^%^CYAN%^s%^CYAN%^e%^CYAN%^ of a human being in tattered "+
         "clothes. Its features are %^CYAN%^r%^BOLD%^%^BLACK%^ott%^RESET%^%^CYAN%^"+
         "e%^BOLD%^%^BLACK%^n %^BLACK%^aw%^RESET%^%^CYAN%^a%^BOLD%^%^BLACK%^"+
         "y%^RESET%^%^CYAN%^ and are hard to discern. It smells as disgustingly "+
         "as it looks, %^BOLD%^%^WHITE%^bi%^BLACK%^t%^WHITE%^s %^BLACK%^o%^WHITE%^"+
         "f %^BLACK%^b%^WHITE%^o%^BLACK%^n%^BLACK%^e%^RESET%^%^CYAN%^ peer through "+
         "decayed pieces. Who it was in life is impossible to tell at this point.");
        corpse->set_short("%^CYAN%^A human corpse%^RESET%^");
        corpse->move(TO);
    }

        break;

        case 3..4:    // toy

        new(OBJ"childs_toy.c")->move(TO);

        break;

        case 5:       // art

       new(OBJ"oil_painting.c")->move(TO);

        break;

        case 6:       // sculpture

        new(OBJ"sculpture.c")->move(TO);


        break;


        }


      return 1;
   }else{
      tell_object(TP,"You clear some of the rubble.");
      tell_room(ETP,""+TPQCN+" digs at the rubble, clearing some of
it.",TP);

        TP->set_paralyzed(3,"You are recovering from your efforts.");
      count = count+1;
      return 1;
   }
}
