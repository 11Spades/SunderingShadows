//archway

#include <std.h>
#include <daemons.h>
#include "../graez.h";

inherit OBJECT;

object gate_master;
string phrasea,phraseb,phrasec,phrased,phrasee,phrasef;
int ansi, using, locked;


void create() {
   ::create();
   set_name("obsidian gate");
   set_short("%^C240%^obsidian gate%^CRST%^ "+
   "with a %^C195%^white door%^CRST%^");
   set_id(({"gate","obsidian gate","Ahratha's Gate","white door","obsidian gate with a white door"}));
   set_long("Standing fifteen feet tall and five feet "+
   "wide, this gate is formed from %^C239%^chiseled "+
   "obsidian bricks%^CRST%^ set into a %^C068%^masterpiece %^CRST%^. "+
   "The %^C239%^bricks %^CRST%^themselves are so perfectly set "+
   "that no mortar has been used. The %^C058%^wood %^CRST%^of "+
   "the gate is a %^C249%^bleached white%^CRST%^ and instead "+
   "of a %^C060%^door knob%^CRST%^ or %^C060%^ring %^CRST%^there "+
   "are %^C101%^six tumblers%^CRST%^ set into the middle of it. "+
   "Each %^C102%^tumbler %^CRST%^has a small part of a phrase on "+
   "it. You could %^C195%^>turn<%^CRST%^ the %^C060%^tumblers%^CRST%^ "+
   "or %^C195%^>check%^CRST%^< them to see what they spell out. You "+
   "are sure you could push %^C195%^>open<%^CRST%^ the %^C239%^gate%^CRST%^ "+
   "as well. The %^C239%^gate%^CRST%^ itself stands alone at the top of "+
   "the %^C094%^hill%^CRST%^ and obviously there is no building behind "+
   "it. You also wonder, perhaps you've read about the gate somewhere. You could %^C195%^>study<%^RESET%^ it. Otherwise it's just a %^C239%^gate%^CRST%^ to nowhere...\n");
   set_value(0);
   set_weight(1000000);
   set_property("no animate",1);
   phrasea = "Kar";
   phraseb = "kana";
   phrasec = "Tar";
   phrased = "sat";
   phrasee = "Koro";
   phrasef = "nro";
   locked = 1;
}


void init(){
   ::init();
   //add_action("read_func", "read");
   add_action("open_func", "open");
   add_action("check_func", "check");
   add_action("turn_func", "turn");
   add_action("study_func", "study");
}

void study_func(string str){
   object player, room;
     
   player = this_player();    
   room = environment(player); 

   if(!str){
      notify_fail("Study what?\n");
      return 0;
   }

   if(str != "gate"){
   notify_fail("Study what?\n");
   return 0;
   }
      if((int)player->query_skill("academics") > 40){
        tell_object(player,"You study the gate and remember reading about it. This must be the lost %^C074%^Ahratha's Gate%^CRST%^! Ahratha was an %^C073%^archmagi %^CRST%^of the dead god %^C195%^Akadi %^CRST%^who was obsessed with research into the %^C087%^elemental plane of air%^CRST%^. It was rumored in the inner circle of the %^C242%^Shadow mage's tower%^CRST%^ that %^C074%^Ahratha %^CRST%^had successfully constructed a gate to the %^C081%^elemental plane%^CRST%^ and was gathering power from it directly. When his contemporaries came to demand access he hid the gate and locked it.");
      if(!player->query_invis()) tell_room(player,""+player->QCN+" studies the %^C060%^gate %^CRST%^closely and seems to %^C195%^become excited%^CRST%^ at its sight.%^RESET%^",player);
      return 1;
    }
    tell_room(room," "+player->QCN+" studies the archway closely.%^RESET%^",player);
    tell_object(TP,"%^C100%^It is definitely a gate, but you feel like you need to lean more heavily into your studies and read more to know what this gate is.%^RESET%^");
    return 1;
}
   

void reset_tumblers(){
  
   object player, room;
 
    
   player = this_player();    
   room = environment(player);  
   
   phrasea = "Kar";
   phraseb = "kana";
   phrasec = "Tar";
   phrased = "sat";
   phrasee = "Koro";
   phrasef = "nro";
   locked = 1;
}

void check_func(string str){

   object player, room;
   string player_name; 
   
   player = this_player();
   room = environment(player);
   player_name = player->query_cap_name(); 

    if(!str) {
       tell_object(player, "%^C079%^Did you mean to check the tumblers? Try %^C146%^>check tumblers<%^RESET%^");
       return 1;
    }   

   tell_object(player, "%^C186%^Stepping up to the %^C241%^gate %^C186%^you look over the %^C058%^tumblers%^C186%^. They currently are set to \n\n\t\t%^CRST%^"+phrasea+"%^C186%^ - %^CRST%^"+phraseb+"%^C186%^ - %^CRST%^"+phrasec+"%^C186%^ - %^CRST%^"+phrased+"%^C186%^ - %^CRST%^"+phrasee+"%^C186%^ - %^CRST%^"+phrasef+"%^CRST%^\n");
   tell_room(room, ""+player_name+"%^C186%^ checks the position of the tumblers on the %^C240%^gate%^C186%^.\n%^CRST%^",player);

   return 1;
}

void reset(){

   object player, room;

   ::reset();   
   player = this_player();
   room = environment(player);
   reset_tumblers();
   tell_room(room, "%^C151%^The whole %^C241%^gate %^C151%^shudders and all the %^C058%^tumblers %^C151%^spin with a %^C193%^viciously fast%^C151%^ speed until coming back to rest..\n%^CRST%^");
}

void turn_func(string str){

   object player, room;
   string choice,descriptive_choice, player_name; 
   
   player = this_player();
   room = environment(player);
   player_name = player->query_cap_name();  

    if(!str) {
       tell_object(player, "%^C079%^turn what? You will need to %^C146%^>turn tumbler #<%^C079%^ to turn one.\n%^CRST%^");
       return 1;
    }

    if(sscanf(str, "tumbler %s", choice)<1){
       tell_object(player, "%^C079%^turn what? You will need to %^C146%^>turn tumbler #<%^C079%^ to turn one.\n%^CRST%^");
       return 1;
    }
    
   sscanf(str, "tumbler %s", choice);

   switch(choice){
      case "1": descriptive_choice = "first"; break;
      case "2": descriptive_choice = "second"; break;
      case "3": descriptive_choice = "third"; break;
      case "4": descriptive_choice = "fourth"; break;
      case "5": descriptive_choice = "fifth"; break;
      case "6": descriptive_choice = "sixth"; break;
   } 
     
   tell_object(player, "%^C072%^you step up to the %^C240%^archway %^C072%^and turn the%^CRST%^ "+descriptive_choice+"%^C072%^ %^C058%^tumbler%^C072%^. It clunks into place with an %^C245%^ominous %^C059%^dull thud%^C072%^.\n%^CRST%^");
   tell_room(room, "%^C072%^Looking over the %^C058%^tumblers%^C072%^, %^CRST%^"+player_name+"%^C072%^ steps up and turns the %^CRST%^"+choice+" %^C058%^tumbler%^C072%^. The %^C028%^whole swamp%^C072%^ echoes with the dull thud as something settles into place.\n%^CRST%^",player);
     
switch(choice)
{
case "1" :
switch( phrasea )
{
   case "Kar":
   phrasea = "Vath";
   break;
   case "Vath":
   phrasea = "Kor";
   break;
   case "Kor":
   phrasea = "Dor";
   break;
   case "Dor":
   phrasea = "Kar";
   break;
}
break;
case "2" :
switch( phraseb )
{
   case "ara":
   phraseb = "boru";
   break;
   case "boru":
   phraseb = "ene";
   break;
   case "ene":
   phraseb = "kana";
   break;
   case "kana":
   phraseb = "ara";
   break;
}
break;
case "3" :
switch( phrasec )
{
   case "Tar":
   phrasec = "Kor";
   break;
   case "Kor":
   phrasec = "Lop";
   break;
   case "Lop":
   phrasec = "Vla";
   break;
   case "Vla":
   phrasec = "Tar";
   break;
}
break;
case "4" :
switch( phrased )
{
   case "sat":
   phrased = "kar";
   break;
   case "kar":
   phrased = "pra";
   break;
   case "pra":
   phrased = "nro";
   break;
   case "nro":
   phrased = "sat";
   break;
}
break;
case "5" :
switch( phrasee )
{
   case "Koro":
   phrased = "Nara";
   break;
   case "Nara":
   phrased = "Qura";
   break;
   case "Qura":
   phrased = "Nero";
   break;
   case "Nero":
   phrased = "Vala";
   break;
}
break;
case "6" :
switch( phrasef )
{
   case "rot":
   phrasee = "ava";
   break;
   case "ava":
   phrasee = "for";
   break;
   case "for":
   phrasee = "tir";
   break;
   case "tir":
   phrasee = "rot";
   break;
}
break;


}

return 1;
}

void open_func(string str){

   object player, room;
   int checksum; 
   string player_name;
    
   player = this_player();    
   room = environment(player);
   player_name = player->query_cap_name(); 
   
   gate_master = find_object_or_load("/realms/loki/theater/graez/gate_master.c");

   checksum = (int)gate_master->check_if_locked(phrasea,phraseb,phrasec,phrased,phrasee,phrasef);    

   if(checksum == 1){
      locked = 0;
      
      tell_object(player, "You push against the bleached wood of the door and it slowly swings open leading to another place!.\n%^CRST%^");
      tell_room(room, ""+player_name+" pushes against the bleached wood door and with a low groan it opens, leading to another place!\n%^CRST%^",player);
      add_exit(ELEAIR"1","gate");
      return 1;
   }
   
      tell_object(player, "%^C066%^You push against the %^C195%^bleached wood%^C066%^ of the door but it won't budge.%^CRST%^\n%^CRST%^");
      tell_room(room, ""+player_name+" %^C066%^pushes against the %^C195%^bleached wood%^C066%^ door with a grunt but nothing happens..%^CRST%^\n%^CRST%^",player);
   return 1;

}
 