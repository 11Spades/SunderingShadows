#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";



void create(){
   ::create();


set_exits(([
"northeast" : FOR"b2",


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
        //ob->remove();
       tell_object(TP,"The archway powers up and a portal appears\n");
           add_exit( FOR"46", "portal" );
        return 1;
    }
        
       tell_object(TP,"Power what? the archway?\n");
    return 1;
}