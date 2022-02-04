#include "../../serakii.h"

inherit STORAGE"white_room.c";

void create(){

::create();

set_long(::query_long()+"\n%^C247%^The office has a large %^C226%^sign%^C247%^ you could read and a ledger you can work with.%^CRST%^\n");

set_exits(([

"south" : WHITE"16",


]));

    set_door("wooden door",WHITE"16","south",0);
    set_door_description("wooden door","%^C094%^Formed from solid wood, this door looks very"+
" heavy. An %^C243%^iron ring%^C094%^ hands from it to allow it to be opened.");
    set_string("wooden door", "open", "%^C094%^You push against the heavy door and it opens slowly.%^CRST%^");
    set_string("wooden door", "close", "%^C094%^You close the heavy wooden door slowly%^RESET%^%^BOLD%^.");

}

void init() {

   ::init();
   add_action("enlist_in_company", "enlist");
   add_action("read", "read");
   add_action("resign", "resign");
   add_action("remove_enemy", "forgive");

}


void resign(){

   if(member_array("Serakii_Legions",TP->query_mini_quests())== 1) {
    tell_object(TP,"%^C097%^With a frown you scratch your name off the ledger, you are a Legions no more!%^CRST%^");
    tell_room(ETP,"%^C097%^"+TPQCN+" %^C097%^scratches their name off the ledger with a frown%^CRST%^",TP);
   TP->remove_mini_quest("Serakii_Legions", 0,"Member of the Legions of Serakii");
   return 1;
   }
    tell_object(TP,"%^C182%^You flip through the ledger looking for your name, but you aren't a Legions%^CRST%^");
    tell_room(ETP,"%^C182%^"+TPQCN+" %^C182%^flips through the ledger a moment...%^CRST%^",TP);
   return 1;
}

int enlist_in_company(){
   object ob, comp;
    tell_object(TP,"%^C246%^You step up to the ledger, ready to sign up with the Legions.%^CRST%^");
    tell_room(ETP,"%^C246%^"+TPQCN+" %^C246%^resolutely steps up to the ledger.%^CRST%^",TP);
    if(member_array("Enemy of the Legions of Serakii",TP->query_mini_quests())== 1) {

    tell_object(TP,"You realize you're in the ledger as an enemy of the Legion, they wouldn't let you join! You should ask for forgiveness%^CRST%^\n");
          return 1;
        }
   if(member_array("Serakii_Legions",TP->query_mini_quests())== 1) {
    tell_object(TP,"%^C097%^As you try to join, you remember you're already in the Legion!%^CRST%^");
    tell_room(ETP,"%^C097%^"+TPQCN+" %^C097%^shakes their head as if to clear the cobwebs%^CRST%^",TP);
      return 1;

   }

    if(!comp = present("hound_seal",TP)){

            tell_object(TP,"You realize that without proof of your loyalty they have no reason to take you. What if you brought the Hound commander seal as a prize!");

        return 1;

           }

        tell_object(TP,"%^C101%^With a grim smile you drop the commander seal from the Hound Commander in to the drop box and sign your name to the ledger. You are a Legions now!%^CRST%^");

    tell_room(ETP,"%^C101%^ "+TPQCN+"%^C101%^ drops something into the drop box and signs their name in the ledger with a grim smile.%^CRST%^",TP);


        comp->remove();
   TP->set_mini_quest("Serakii_Legions", 0, "Member of the Legions of Serakii");

   return 1;


}
int remove_enemy(){
    tell_object(TP,"%^C064%^Looking over your shoulder, you flip through the ledger looking for your name as an enemy of the Legion of Pearl.%^CRST%^");
    tell_room(ETP,"%^C064%^"+TPQCN+" %^C064%^nervously looks through the ledger%^CRST%^",TP);
    if(member_array("Enemy of the Legions of Serakii",TP->query_mini_quests())== 1) {
    tell_object(TP,"%^C139%^You find your name in the list of enemies!");
    tell_room(ETP,"%^C139%^"+TPQCN+" %^C139%^flips through the books and nods.%^CRST%^",TP);


    if(!TP->query_funds("gold",100000)){
    tell_object(TP,"%^C226%^You realize you dont have enough gold to erase your crimes!");
    tell_room(ETP,"%^C058%^"+TPQCN+" %^C058%^looks over their pockets a moment and frowns%^CRST%^",TP);
        return 1;
        }

    TP->use_funds("gold",100000);
    tell_object(TP,"%^C226%^You sigh and drop a pile of gold into the drop box!");
    tell_room(ETP,"%^C226%^"+TPQCN+" %^C226%^sighs and drops a lot of gold into the drop box%^CRST%^",TP);




    TP->remove_mini_quest("Enemy of the Legions of Serakii", 0,"Enemy of the Legions of Serakii");
    tell_object(TP,"%^C196%^You scratch your name off of the list of enemies!");
    tell_room(ETP,"%^C196%^"+TPQCN+" %^C196%^scratches their name off the register with a smile.%^CRST%^",TP);
      return 1;

   }
    tell_object(TP,"%^C246%^You exhale in relief, not finding your name as an enemy of the Legion.%^CRST%^");
    tell_room(ETP,"%^C246%^"+TPQCN+" %^C246%^exhales.%^CRST%^",TP);
    return 1;
}

int read(string str)
{
    if(str == "sign") {
    tell_room(ETP,"%^C137%^"+TPQCN+" %^C137%^reads over the sign.%^CRST%^",TP);

    tell_object(TP,"%^C137%^You read over the sign.%^CRST%^\n");
            tell_object(TP,"%^C146%^******************************************************************%^CRST%^\n");
                tell_object(TP,"%^C246%^This is the ledger of the Legions of Pearl. We are the only shield against the darkness in the land.\n%^CRST%^");
                tell_object(TP,"%^C248%^- If you want to join us then %^C099%^enlist %^C248%^and we will take you.%^CRST%^");
                tell_object(TP,"%^C246%^- Pay for your crimes against us you can ask us to %^C099%^forgive %^C246%^you.%^CRST%^");
                tell_object(TP,"%^C246%^- If you walk a different path %^C099%^resign %^C246%^and be free.%^CRST%^\n");
            tell_object(TP,"%^C146%^******************************************************************%^CRST%^\n");
                return 1;
        }
}
