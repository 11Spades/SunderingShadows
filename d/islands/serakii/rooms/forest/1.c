

#include <std.h>
#include "../../serakii.h"

inherit STORAGE"mist_forest.c";



void create(){
   ::create();


set_exits(([
"west" : FOR"2",
"south" : FOR"9",

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
        //ob->remove();
       tell_object(TP,"%^YELLOW%^%^BOLD%^The archway powers up and a portal appears\n%^RESET%^");
	   add_exit( HOUND"b12", "portal" );
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
      tell_object(TP,"%^%^C134%^As you walk around observing the construction "+
         "and material of the archway you realize that it is in perfect condition "+
         "but has been drained of power. You should be able to use the "+
         "same method you used to got here.\n%^RESET%^");
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

