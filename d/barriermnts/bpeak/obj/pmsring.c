#include <std.h>
inherit ARMOUR;
int uses;
int query_uses(){return uses;}

void create(){
   ::create();
   set_name("%^BOLD%^%^WHITE%^Platinum ring of stars%^RESET%^");
   set_id(({"ring","ring of stars","platinum ring","star ring","platinum ring of stars"}));
   set_short("%^BOLD%^%^WHITE%^A sparkling platinum ring%^RESET%^");
   set_long("%^BOLD%^%^WHITE%^This sparkling ring is made out of the purest"
" platinum.  Inset upon the top of the ring is a very large princess cut diamond"
" that shines in the light and reflects prismatic sprays of color throughout the"
" room.  A small inscription is written on the inside of the band.%^RESET%^\n");
   set_lore("%^BOLD%^%^WHITE%^These rings are rare and rumored to be made by a"
" wayward priest who dappled in the arts of magic.  Because of the mad wizards"
" inexperience, the rings were thought to be to dangerous and unreliable for"
" general use.  All the known copies were gathered together and buried deep"
" within the Barrier Mountains.%^RESET%^");
   set_language("common");
   set_read("%^YELLOW%^This is the fabled prismatic ring of stars.\nUse it wisely"
" as it casts prismatic spray at your enemies."
"\nYou may 'aim ring at <target>' to see the wonders this ring creates!%^RESET%^");
   set_weight(2);
   set_value(2000);
   set_type("ring");
   set_limbs(({"left hand","right hand"}));
   set_size(2);
   set_property("enchantment",0);
   set_ac(0);
   set_wear((:this_object(),"wearme":));
   uses=random(5)+5;
   set_heart_beat(1);
}
int wearme(string str){
      tell_room(environment(ETO),"%^BOLD%^%^WHITE%^%^As "+ETOQCN+" slips on the ring, bright %^RED%^c%^BLUE%^o%^YELLOW%^l%^CYAN%^o%^RED%^r%^YELLOW%^s %^WHITE%^fill the room.%^RESET%^",ETO);
   tell_object(ETO,"%^BOLD%^%^WHITE%^Bright %^RED%^c%^BLUE%^o%^YELLOW%^l%^CYAN%^o%^RED%^r%^YELLOW%^s %^WHITE%^fill the room as you slip on the ring.%^RESET%^");
   return 1;  
}
void init(){
   ::init();
   if(!objectp(TP)) return;
   if (!objectp(ETO)) return;
   if (TP != ETO) return;
   add_action("aim","aim");
}
void aim(string str){
   string tmp;
   object obj;
   if(!str) return notify_fail("Aim what at what?\n");
   if(sscanf(str,"ring at %s",tmp)){
   if (TP->query_bound()||TP->query_unconscious()||TP->query_paralyzed()) {
       TP->send_paralyzed_message("info",TP);
       return 1;
    }
    if(!TO->query_worn()) return notify_fail("You need to be wearing the ring.\n");
    if(uses<1)return notify_fail("There are no more charges in the ring!");
    if(!(obj = present(tmp, ETP))) return notify_fail("That isn't here!\n");
       switch(random(5)){
          case 0..1:
          tell_object(ETO,"You caress the ring softly and then point it at "+obj->QCN+" but the ring tricks you and forces you to turn your hand against yourself!");
         tell_object(obj,""+TPQCN+" caresses the ring softly then points it directly at you but something goes wrong and "+TP->query_subjective()+" turns the ring against "+TP->query_objective()+"self!");
        tell_room(ETP,""+TPQCN+" caresses the ring and then points it at "+obj->query_cap_name()+" but something goes terribly wrong and "+TP->query_subjective()+" turns the ring against "+TP->query_objective()+"self!",({TP,obj}));

          new("/cmds/spells/p/_prismatic_spray")->use_spell(TP,TP,14,1,"mage");
          uses --;
          break;
          case 2..4:
          tell_object(ETO,"You caress the ring softly and then point it at "+obj->QCN+"!");
          tell_object(obj,""+TPQCN+" caresses the ring softly then points it directly at you!");
          tell_room(ETP,""+TPQCN+" caresses the ring and then points it at "+obj->query_cap_name()+"!",({TP,obj}));

          new("/cmds/spells/p/_prismatic_spray")->use_spell(TP,obj,14,1,"mage");
          uses --;
          break;
       }
    return 1;
    }
}
void heart_beat(){
   object obj;
   if((obj=present("platinum ring of stars",ETO))&&living(ETO)&&obj!=TO){
      tell_object(ETO,"The ring feels the presence of another and disappears!");
      ETO->do_damage("torso",roll_dice(3,10));
      ETO->add_attacker(TO);
      ETO->continue_attack();
      obj->remove();
      TO->remove();
   }
}
