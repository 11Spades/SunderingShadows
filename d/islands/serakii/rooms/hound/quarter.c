#include <std.h>
#include "../../serakii.h"

inherit STORAGE"hound_tent.c";


void create(){
   ::create();

set_exits(([
"out" : HOUND"26",

]));

}

void init() {
   ::init();
   add_action("enlist_in_company", "enlist");
   add_action("resign", "resign");
   add_action("remove_enemy", "forgive");
}

void resign(){
	
   if(member_array("Serakii_Hounds",TP->query_mini_quests())== 1) {
   tell_object(TP,"You leave the Hounds!");
   TP->remove_mini_quest("Serakii_Hounds", 0,"Member of the Hounds of Serakii");
   return 1;
   }    	
   tell_object(TP,"You Dont do anything because there was nothing to do!");
   return 1;
}

int enlist_in_company(){
   tell_object(TP,"Trying to Enlist!");	
   if(member_array("Serakii_Hounds",TP->query_mini_quests())== 1) {
      tell_object(TP,"You already belong to the Hounds!");
      return 1;
   }
   tell_object(TP,"You join the Hounds!");
   TP->set_mini_quest("Serakii_Hounds", 0, "Member of the Hounds of Serakii");
   return 1;
}

int remove_enemy(){
    tell_object(TP,"Trying to Remove Enemy!");
    if(member_array("Enemy of the Hounds of Serakii",TP->query_mini_quests())== 1) {
      tell_object(TP,"You were an enemy of the Hounds!");
	  TP->remove_mini_quest("Enemy of the Hounds of Serakii", 0,"Enemy of the Hounds of Serakii");
      tell_object(TP,"Now you arent!");
      return 1;
   }	
    tell_object(TP,"Dont worry you arent our enemy!");
    return 1;
}
