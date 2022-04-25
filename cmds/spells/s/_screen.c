//Screen - Illusion domain spell by ~Circe~ based on detect scrying
//and protection from scrying.  Part of the rebalancing of domain
//spells 5/5/08

#include <spell.h>
#include <magic.h>
#include <daemons.h>

#define SCRY_D "/daemon/ic_scry_locate_d"

inherit SPELL;

object detector, blocker;

void create() {
    ::create();
    set_spell_name("screen");
    set_spell_level(([ "mage": 8 ]));
    set_spell_sphere("illusion");
    set_syntax("cast CLASS screen");
    set_description("Upon casting this spell, the user creates a screen of illusion in the area that makes scrying attempts difficult. This screen will actively attempt to block scry attempts, though it will not warn the caster when attempts fail. This scry blocking spell, unlock other such spells, affects the entire room, and stays in that room. It does not move around with the caster. This can be used to create an area (room) that has temporary scry protection that will protect everyone within.");
    set_verbal_comp();
    set_somatic_comp();
    set_peace_needed(1);
	set_helpful_spell(1);
}

string query_cast_string(){
   tell_object(caster,"%^CYAN%^You gesture gracefully with your "+
      "hands, weaving an illusion to confuse those who attempt "+
      "to view you from afar.%^RESET%^");
   tell_room(place,"%^CYAN%^"+caster->QCN+" gestures gracefully "+
      "with "+caster->QP+" hands, almost as if weaving.%^RESET%^",caster);
   return "display";
}

void spell_effect(int prof) {
   int num, duration, wis_bonus, power;
   object temp;

   ::spell_effect();
   
    /*
    if(caster->query_property("scry detect power") || caster->query_property("scry block power") || caster->query_property("block scrying") || caster->query_property("false vision"))
    {
        tell_object(caster, "There is already scry protection magic on you.");
        dest_effect();
        return;
    }
    */
    
    if(caster->query_property("screen"))
    {
        tell_object(caster, "You can only maintain one screen at a time.");
        dest_effect();
        return;
    }
    
    if(place->query_property("scry block power") || place->query_property("scry proof"))
    {
        tell_object(caster, "This place is already under the effects of scry protection.");
        dest_effect();
        return;
    }
   
   /*
   if(temp = caster->query_property("detect scrying")){
      if(!objectp(temp)){
         caster->remove_property("detect scrying");
      }else{
         tell_object(caster,"%^BOLD%^RED%^You are already detecting "+
            "scrying attempts!");
         TO->remove();
         return;
      }
   }
   */
   /*
   if(temp = caster->query_property("block scrying")){
      if(!objectp(temp)){
         caster->remove_property("block scrying");
      }else{
         tell_object(caster,"%^BOLD%^RED%^There is already blocking "+
            "magic working for that target!");
         TO->remove();
         return;
      }
   }
   */
   tell_room(place,"%^BOLD%^%^CYAN%^The air around "+caster->QCN+" "+
      "s%^RESET%^%^CYAN%^h%^BOLD%^i%^RESET%^%^CYAN%^m%^BOLD%^m"+
      "%^RESET%^%^CYAN%^e%^BOLD%^r%^RESET%^%^CYAN%^s %^BOLD%^with "+
      "shifting images for a moment before growing still.%^RESET%^",caster);
   tell_object(caster,"%^BOLD%^%^CYAN%^The air around you "+
      "s%^RESET%^%^CYAN%^h%^BOLD%^i%^RESET%^%^CYAN%^m%^BOLD%^m"+
      "%^RESET%^%^CYAN%^e%^BOLD%^r%^RESET%^%^CYAN%^s %^BOLD%^with "+
      "shifting images for a moment before growing still.%^RESET%^");
   wis_bonus = calculate_bonus(caster->query_stats(get_casting_stat()));
   //power = CLEVEL + wis_bonus + random(6);
   power = clevel + wis_bonus + query_spell_level(spell_type);

   caster->set_property("spelled",({TO}));
   /*
   detector = SCRY_D->add_detect_scrying(caster);
   if(!objectp(detector)){
      tell_object(caster,"%^BOLD%^RED%^Something is wrong that "+
         "a wiz might want to look at!");
      dest_effect();
      return;
   }
   detector->set_detect_power(power);
   blocker = SCRY_D->add_block_scrying(caster);
   if(!objectp(blocker)) {
      tell_object(caster,"%^BOLD%^RED%^Something is wrong that "+
         "a wiz might want to look at!");
      dest_effect();
      return;
   }
   wis_bonus = calculate_bonus(caster->query_stats(get_casting_stat()));
   power = CLEVEL + wis_bonus + random(6);
   blocker->set_block_power(power);
   */
   
   spell_successful();
   addSpellToCaster();
   place->set_property("scry block power", power);
   caster->set_property("screen", 1);
   spell_duration = 6 * (int)CLEVEL * ROUND_LENGTH;
   set_end_time();
   call_out("dest_effect", spell_duration);
   return;
}

void dest_effect(){

   if(objectp(caster))
   {
       tell_object(caster,"%^CYAN%^%^BOLD%^The illusion protecting you from scrying fades.%^RESET%^");
       caster->remove_property_value("spelled", ({TO}) );
       caster->remove_property("screen");
   }
   objectp(place) && place->remove_property("scry block power");
   //if(objectp(detector)) detector->self_destruct();
   //if(objectp(blocker)) blocker->self_destruct();

   ::dest_effect();
   if(objectp(TO)) TO->remove();
}
