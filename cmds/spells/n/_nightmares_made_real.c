// parity with earthquake/windstorm for balance; upper AOE effect with trip option
#include <spell.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

int nightmare_effects(object obj);
int duration;

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("nightmares made real");
    set_spell_level(([ "warlock" : 3 ]));
    set_spell_sphere("illusion");
    set_syntax("cast CLASS nightmares made real");
    set_damage_desc("negative energy");
    set_description("By means of this invocation, the warlock cloaks the surrounding area in a horrific dreamscape "
"interwoven with planar energy, making any terrain look, sound and smell like something out of a nightmare. Writhing "
"vegetation, disembodied limbs, animated corpses, smoking pits, miasmic vapors, vile stenches, or anything else that "
"may spring from the caster's imagination. Those in the affected area that are strong of will may realize that these "
"are only illusions, and in doing so resist part of the harm they can cause; those fleet of foot may manage to avoid "
"the ensnaring grasp of the illusionary phantasms.");
    set_verbal_comp();
    set_somatic_comp();
    set_save("varied");
    aoe_spell(1);
    set_aoe_message("%^RESET%^%^CRST%^%^C051%^(%^C031%^warped by horrifying %^C105%^p%^C111%^ha%^C117%^n%^C105%^t%^C111%^as%^C117%^m%^C105%^s%^RESET%^%^C051%^)%^CRST%^");
}

string query_cast_string(){
   tell_object(caster, "%^RESET%^%^CRST%^%^C031%^You wave your arms, and the air around you %^C105%^s%^C111%^hi%^C117%^m%^C105%^m%^C111%^er%^C117%^s %^C031%^and %^C093%^r%^C099%^i%^C105%^p%^C099%^p%^C093%^l%^C099%^e%^C105%^s%^C031%^.%^CRST%^");
   tell_room(place, "%^RESET%^%^CRST%^%^C031%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C031%^ waves "+caster->query_possessive()+" arms, and the air around you %^C105%^s%^C111%^hi%^C117%^m%^C105%^m%^C111%^er%^C117%^s %^C031%^and %^C093%^r%^C099%^i%^C105%^p%^C099%^p%^C093%^l%^C099%^e%^C105%^s%^C031%^.%^CRST%^", caster);
   return "display";
}

void spell_effect(int prof){
   duration = (ROUND_LENGTH * clevel) * 2;
   tell_object(caster, "%^RESET%^%^CRST%^%^C031%^Weaving threads of %^C037%^p%^C043%^l%^C049%^a%^C037%^n%^C043%^a%^C049%^r %^C037%^e%^C043%^n%^C049%^e%^C037%^r%^C043%^g%^C049%^y %^RESET%^%^C031%^into the illusion, you shape a terrifying %^C105%^d%^C111%^re%^C117%^a%^C105%^m%^C111%^sc%^C117%^a%^C105%^p%^C111%^e %^RESET%^%^C031%^and interpose it upon %^C025%^reality%^C037%^!%^CRST%^");
   tell_room(PLACE, "%^RESET%^%^CRST%^%^C031%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C031%^ completes "+caster->query_possessive()+" spell, as the world around you suddenly descends into a state of %^C105%^n%^C111%^ig%^C117%^h%^C105%^t%^C111%^ma%^C117%^r%^C105%^e%^RESET%^%^C031%^!%^CRST%^", caster);
   caster->set_property("spelled", ({TO}));
   addSpellToCaster();
   spell_successful();
   spell_duration = duration;
   set_end_time();
   call_out("dest_effect",spell_duration);
}

void execute_attack(){
   object *attackers = ({});
   int i;

   ::execute_attack();
   if(!objectp(caster) || !objectp(environment(caster)) || caster->query_unconscious()){
      dest_effect();
      return;
   }
   if(environment(caster) != place){
      tell_object(caster,"%^RESET%^%^CRST%^%^C031%^The %^C105%^i%^C111%^ll%^C117%^u%^C105%^s%^C111%^io%^C117%^n %^RESET%^%^C051%^f%^C049%^a%^C043%^d%^C037%^e%^C031%^s as you leave the area.%^CRST%^");
      tell_room(place,"%^RESET%^%^CRST%^%^C031%^The %^C105%^i%^C111%^ll%^C117%^u%^C105%^s%^C111%^io%^C117%^n %^RESET%^%^C051%^f%^C049%^a%^C043%^d%^C037%^e%^C031%^s as "+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C031%^ leaves the area.%^CRST%^");
      dest_effect();
      return;
   }
//   attackers = caster->query_attackers();
   attackers = target_selector();


// let's see about this just going regardless of present attackers? else can't be pre-cast.
//   if(sizeof(attackers)){
      tell_room(place,"%^RESET%^%^CRST%^%^C031%^A %^C093%^h%^C099%^o%^C105%^r%^C093%^r%^C099%^i%^C105%^f%^C093%^i%^C099%^c %^C037%^d%^C043%^r%^C049%^e%^C051%^a%^C037%^m%^C043%^s%^C049%^c%^C051%^a%^C037%^p%^C043%^e %^RESET%^%^C031%^shifts around you, filled with %^C105%^p%^C111%^ha%^C117%^n%^C105%^t%^C111%^as%^C117%^m%^C105%^a%^C111%^l f%^C117%^i%^C105%^g%^C111%^ur%^C117%^e%^C105%^s %^RESET%^%^C031%^that reach out for the living!%^CRST%^");
      for(i=0;i<sizeof(attackers);i++) {
         if(!nightmare_effects(attackers[i])) continue;
      }
/*   }
   else{
      dest_effect();
      return;
   } */
   if(present(caster,place) && caster != target && !caster->query_unconscious()) {
       place->addObjectToCombatCycle(TO,1);
   }
   else {
       dest_effect();
   }
}

int nightmare_effects(object obj){
   int damage;
   object room;
   if(!objectp(obj))               { return 0; }
   if(!objectp(environment(obj)))  { return 0; }
   if(environment(caster) != environment(obj)) { return 0; }
   if(obj == caster) return 0;
   room = environment(obj);

   damage = sdamage;

   set_save("will");
   if(do_save(obj,0)){
      tell_object(obj, "%^RESET%^%^CRST%^%^C031%^You will away the %^C105%^i%^C111%^ll%^C117%^u%^C105%^s%^C111%^io%^C117%^n%^RESET%^%^C031%^, though the %^C037%^p%^C043%^l%^C049%^a%^C037%^n%^C043%^a%^C049%^r %^C037%^e%^C043%^n%^C049%^e%^C037%^r%^C043%^g%^C049%^y %^RESET%^%^C031%^still tears at your body!%^CRST%^");
      tell_room(room, "%^RESET%^%^CRST%^%^C031%^"+obj->query_cap_name()+"%^RESET%^%^CRST%^%^C031%^ seems to see past the worst of the %^C093%^n%^C099%^ig%^C105%^h%^C093%^t%^C099%^ma%^C105%^r%^C093%^i%^C099%^sh %^C105%^v%^C093%^i%^C099%^si%^C105%^o%^C093%^n%^C099%^s%^RESET%^%^C031%^!%^CRST%^", obj);
      damage_targ(obj,obj->return_target_limb(),damage/2,"negative energy");
   }
   else{
      tell_object(obj, "%^RESET%^%^CRST%^%^C031%^The %^C093%^n%^C099%^ig%^C105%^h%^C093%^t%^C099%^ma%^C105%^r%^C093%^i%^C099%^sh %^C105%^a%^C093%^p%^C099%^pa%^C105%^r%^C093%^i%^C099%^ti%^C105%^o%^C093%^n%^C099%^s %^RESET%^%^C124%^rend %^C031%^and %^C124%^tear %^C031%^your flesh!%^CRST%^");
      tell_room(room, "%^RESET%^%^CRST%^%^C031%^"+obj->query_cap_name()+"%^RESET%^%^CRST%^%^C031%^ is %^C124%^tormented %^C031%^by the %^C093%^n%^C099%^ig%^C105%^h%^C093%^t%^C099%^ma%^C105%^r%^C093%^i%^C099%^sh %^C105%^a%^C093%^p%^C099%^pa%^C105%^r%^C093%^i%^C099%^ti%^C105%^o%^C093%^n%^C099%^s%^RESET%^%^C031%^!%^CRST%^", obj);
      damage_targ(obj,obj->return_target_limb(), damage, "negative energy");
      set_save("reflex");
      if(!do_save(obj,0)){
        tell_object(obj, "%^RESET%^%^CRST%^%^C025%^Writhing %^C037%^ve%^C043%^g%^C037%^et%^C031%^a%^C037%^ti%^C043%^o%^C037%^n %^RESET%^%^C025%^and %^C105%^i%^C111%^nc%^C117%^o%^C105%^r%^C111%^po%^C117%^r%^C105%^e%^C111%^al %^C117%^b%^C105%^e%^C111%^in%^C117%^g%^C105%^s %^RESET%^%^C025%^grasp at you, knocking you from your feet!%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C025%^"+obj->query_cap_name()+"%^RESET%^%^CRST%^%^C025%^ is knocked from "+obj->query_possessive()+" feet by the %^C105%^g%^C111%^ra%^C117%^s%^C105%^p%^C111%^in%^C117%^g %^C105%^p%^C111%^ha%^C117%^n%^C105%^t%^C111%^as%^C117%^m%^C105%^s %^RESET%^%^C025%^and %^C037%^wr%^C031%^i%^C037%^th%^C043%^i%^C037%^ng %^C031%^v%^C037%^eg%^C043%^e%^C037%^ta%^C031%^t%^C037%^io%^C043%^n%^C025%^!%^CRST%^", obj);
        obj->set_tripped(roll_dice(1,2), "%^RESET%^%^CRST%^%^C025%^You are struggling to get back to your feet!%^CRST%^",2);
      }
   }
   return 1;
}

void dest_effect(){
    if(objectp(place)) tell_room(place,"%^RESET%^%^CRST%^%^C037%^%^The %^C093%^n%^C099%^ig%^C105%^h%^C093%^t%^C099%^ma%^C105%^r%^C093%^e %^RESET%^%^C037%^finally ends as reality reasserts itself over the %^C031%^dreamscape%^C037%^.%^CRST%^");
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
