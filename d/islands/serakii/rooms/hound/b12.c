#include <std.h>
#include "../../serakii.h"

inherit STORAGE"beach.c";
object ob;


void create(){
   ::create();
   set_long(::query_long()+"\n%^C247%^Dominating the whole section of beach is a giant archway made of some %^C093%^unknown metal%^C247%^.%^CRST%^\n");




set_exits(([
"west" : HOUND"b11",

]));

}


void reset(){
   ::reset();
   if(!present("archway")){
      new(OBJ"archway.c")->move(TO);
   }
}

void init() {
    ::init();
    add_action("power_fun", "power");
    add_action("observe_fun", "observe");

}

int power_fun(string str,object who){

object ob;

    if(!str) {
       tell_object(TP,"%^BLACK%^%^BOLD%^Power what? the archway?\n%^RESET%^");
       return 1;
    }

    if(str == "archway"){
        ob=present("shard of soul",TP);
        if(!ob) return notify_fail("\nYou have nothing you could use to power the archway.\n");
       tell_object(TP,"%^YELLOW%^%^BOLD%^The archway powers up and a portal appears\n%^RESET%^");
      TP->set_mini_quest("Opened the Forest of Mists on Serakii", 1000000, "%^BOLD%^Opened the Forest of Mists on Serakii%^RESET%^");
	   add_exit( FOR"1", "portal" );
        return 1;
    }
	
       tell_object(TP,"%^BLACK%^%^BOLD%^Power what? the archway?\n%^RESET%^");
    return 1;
}

int observe_fun(string str,object who){

   // Observe based directly off of adademics
   object ob;
   int study = TP->query_skill("academics");


    if(!str) {
       tell_object(TP,"%^BLACK%^%^BOLD%^Observe what? the archway?\n%^RESET%^");
       return 1;
    }

   if(str == "archway"){
   

   if(study > 25){ 
      // Success
      tell_room(ETP,"%^BOLD%^"+TPQCN+"%^BOLD%^ walks around the archway. They seem to "+
         "come to some conclusion about it!%^RESET%^",TP);
      tell_object(TP,"%^C134%^As you walk around observing the construction "+
         "and material of the archway you realize that it is in perfect condition "+
         "but has been drained of power. Your studies mentioned %^C081%^shards%^C134%^ created "+
         "through the freeing of souls. Perhaps if you asked around about %^C081%^shards%^C134%^ you might learn more.\n%^RESET%^");
      return 1;
   }
      // Fail
      tell_room(ETP,"%^BOLD%^"+TPQCN+"%^BOLD%^ walks around the archway. They look "+
            "a little lost though.%^RESET%^",TP);
      tell_object(TP,"%^%^C134%^No matter how much you look at the archway you can't "+
         "remember anything from your studies that might help you.\n%^RESET%^");
      return 1;
   }
   
       tell_object(TP,"%^BLACK%^%^BOLD%^Observe what? the archway?\n%^RESET%^");
    return 1;
}



