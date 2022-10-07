//racial innate for shades - based off dimension slide, psywarrior spell
#include <std.h>
#include <spell.h>
inherit SPELL;

#define DELAY 180 //3 min delay

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("shadow stride");
    set_spell_level(([ "innate" : 1, "monk" : 7, "assassin" : 1 ]));
    set_spell_sphere("alteration");
    set_monk_way("way of the shadow");
    set_syntax("cast CLASS shadow stride on <direction>");
    set_description("This spell allows the caster to step into the nearest shadow, "
"using it to travel a short distance away. It can be used in combat and will ignore "
"mundane impediments, such as caltrops or closed doors, but will be barred by "
"magically sealed doors.");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_helpful_spell(1);
}

int preSpell() {
   if(caster->cooldown("slide time")){
      tell_object(caster,"You need to take a moment's rest before you can try that again.");
      return 0;
   }
   if(!arg) {
       tell_object(caster, "%^BOLD%^%^WHITE%^You must specify a direction for this spell!%^RESET%^");
       return 0;
   }
   return 1;
}

void spell_effect(int prof) {
    string *exits, dest_name;
    object dest;

    exits = (string *)place->query_exits();
    if((member_array(arg, exits) == -1)) {
        tell_object(caster,"%^BOLD%^%^WHITE%^You can't stride in that direction!%^RESET%^");
        dest_effect();
        return;
    }

    spell_successful();
    if(place->query_property("no phase")){
       tell_object(caster,"This place seems to be enchanted against such things!\n");
       dest_effect();
       return;
    }
    dest_name = place->query_exit(arg);
    dest = find_object_or_load(dest_name);
    if(dest->query_property("no phase")){
       tell_object(caster,"This place seems to be enchanted against such things!\n");
       dest_effect();
       return;
    }
    tell_object(caster,"%^RESET%^%^C244%^You step into the %^RESET%^%^C240%^s%^C241%^h%^C242%^a%^C243%^d%^C242%^o%^C241%^w%^C240%^s%^RESET%^%^C244%^ and use their %^RESET%^%^C240%^concealment %^RESET%^%^C244%^to stride towards the "+arg+" %^RESET%^%^C242%^exit.%^CRST%^");
    if(!caster->query_invis()){
       tell_room(place,"%^RESET%^%^C244%^"+caster->QCN+" steps into the %^RESET%^%^C240%^s%^C241%^h%^C242%^a%^C243%^d%^C242%^o%^C241%^w%^C240%^s %^RESET%^%^C244%^near the "+arg+" %^RESET%^%^C244%^exit and %^RESET%^%^C240%^vanishes%^RESET%^%^C244%^!%^CRST%^",caster);
    }
    caster->clear_followers();
    caster->move_player(dest);
    caster->add_cooldown("slide time", DELAY);
    if(!caster->query_invis()){
       tell_room(dest,"%^RESET%^%^C244%^"+caster->QCN+" %^RESET%^%^C244%^steps quite suddenly from a patch of %^RESET%^%^C240%^s%^C241%^h%^C242%^a%^C243%^d%^C241%^o%^C240%^w%^RESET%^%^C244%^.%^CRST%^",caster);
    }
    dest_effect();
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
