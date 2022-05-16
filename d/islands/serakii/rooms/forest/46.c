
#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([

    "east" : FOR"47",
    "south" : FOR"45",

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
    add_action("observe_fun","observe");

}

int power_fun(string str,object who){

object ob;

    if(!str) {
       tell_object(TP,"Power what? the archway?\n");
       return 1;
    }

    if(str == "archway"){
        ob=present("shard of children",TP);
        if(!ob) return notify_fail("\nYou have nothing that seems to power this archway. "+
         "You will need an item that holds an immense amount of power.\n");
       TP->set_mini_quest("Opened the Forest of Blood on Serakii", 1000000, "%^RED%^%^BOLD%^Opened the Forest of Blood on Serakii%^RESET%^");
       tell_object(TP,"The archway powers up and a portal appears\n");
           add_exit( FOR"b1", "portal" );
        return 1;
    }
        
       tell_object(TP,"Power what? the archway?\n");
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
      tell_object(TP,"%^%^C134%^As you walk around observing the construction "+
         "and material of the archway you realize that it is in perfect condition "+
         "but has been drained of power. The runes on this arch though show its power is "+
         "wrong.\n\n %^C160%^As you look closer your head is wracked with pain and a vision "+
         "of a corpses fills it! You feel like you must find these corpses.%^RESET%^\n%^RESET%^");
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