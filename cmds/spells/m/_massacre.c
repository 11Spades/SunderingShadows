/*
  _massacre.c
  
  Necromancy Splash Spell.
  
  -- Tlaloc --
*/

#include <std.h>
#include <spell.h>
#include <magic.h>
inherit SPELL;

int current;
string target_limb;
object *targets;

void create()
{
    ::create();
    set_spell_name("massacre");
    set_spell_level(([ "mage" : 9, "cleric" : 9 ]));
    set_domains(({ "evil" }));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS massacre on TARGET");
    set_damage_desc("death on failed save, divine damage and fester otherwise");
    set_save("fortitude");
    set_description("You unleash a wave of necromantic energy that snuffs out the life force of those in its path. This wave pulses out from you, visibly ripping the souls from the bodies of those it passes through. All other must make a combat death save or die. Those who make the save will take full normalized divine damage, and have their healing diminished for a short time. This spell hits fewer targets than spells like Wail of the Banshee.");
    evil_spell(1);
    set_verbal_comp();
    set_target_required(1);
    splash_spell(2);
}

string query_cast_string()
{
    return "%^BOLD%^%^BLACK%^" + caster->QCN + " begins to utter words of slaughter.%^RESET%^";
}

void spell_effect(int prof)
{
    int difflevel, myoutput, mydmg;

    if (!target || !present(target,environment(caster)))
    {
        tell_object(caster,"%^BOLD%^Your target is not in this area.\n");
        dest_effect();
        return;
    }
    
    tell_object(caster,"%^RESET%^%^C052%^You motion and a w%^RESET%^%^C088%^a%^C124%^v%^RESET%^%^C160%^e %^RESET%^%^C196%^o%^C160%^f %^RESET%^%^C124%^s%^C088%^l%^C124%^a%^C160%^u%^C196%^g%^C160%^h%^C124%^t%^C088%^e%^RESET%^%^C052%^r %^RESET%^%^C088%^r%^C124%^i%^C160%^p%^C196%^p%^C160%^l%^C124%^e%^RESET%^%^C088%^s %^RESET%^%^C052%^away from you, %^RESET%^%^C088%^k%^C124%^i%^C160%^l%^C196%^l%^C160%^i%^C124%^n%^RESET%^%^C088%^g %^RESET%^%^C052%^those in its path!%^CRST%^");
    tell_room(place,"%^RESET%^%^C052%^"+caster->QCN+" %^RESET%^%^C052%^motions and a w%^RESET%^%^C088%^a%^C124%^v%^RESET%^%^C160%^e %^RESET%^%^C196%^o%^C160%^f %^RESET%^%^C124%^s%^C088%^l%^C124%^a%^C160%^u%^C196%^g%^C160%^h%^C124%^t%^C088%^e%^RESET%^%^C052%^r %^RESET%^%^C088%^r%^C124%^i%^C160%^p%^C196%^p%^C160%^l%^C124%^e%^RESET%^%^C088%^s %^RESET%^%^C052%^outward, %^RESET%^%^C088%^k%^C124%^i%^C160%^l%^C196%^l%^C160%^i%^C124%^n%^C088%^g %^RESET%^%^C052%^all those in its path!%^CRST%^",({caster}));
    
    spell_successful();
    spell_kill(target, caster);

    targets = target_selector();
    targets += ({target});
    targets = distinct_array(targets);
    
    foreach(object ob in targets)
    {
        spell_kill(ob, caster);
        
        if(!objectp(ob) || !objectp(caster))
            continue;
        
        if(!combat_death_save(ob, 0))
        {
            tell_object(ob,"%^RESET%^%^RESET%^%^C052%^The w%^RESET%^%^C088%^a%^C124%^v%^C160%^e %^RESET%^%^C052%^of %^RESET%^%^C240%^death %^RESET%^%^C052%^r%^C088%^i%^C124%^p%^C160%^s %^RESET%^%^C052%^your %^RESET%^%^C087%^soul %^RESET%^%^C052%^from your body, leaving a %^RESET%^%^C123%^p%^C159%^a%^C195%^l%^C123%^e %^RESET%^%^C087%^a%^C123%^f%^C159%^t%^C123%^e%^RESET%^%^C087%^r-i%^RESET%^%^C123%^m%^C159%^a%^C123g%^RESET%^%^C087%^e%^RESET%^%^C052%^!%^CRST%^");
            tell_room(place,"%^RESET%^%^C052%^"+ob->QCN+"%^RESET%^%^C052%^'s %^RESET%^%^C087%^soul %^RESET%^%^C052%^is %^RESET%^%^C088%^r%^C124%^i%^C160%^p%^C196%^p%^C124%^e%^RESET%^%^C088%^d %^RESET%^%^C052%^from their body, leaving a %^RESET%^%^C123%^p%^C159%^a%^C195%^l%^C123%^e %^RESET%^%^C087%^a%^C123%^f%^C159%^t%^C123%^e%^RESET%^%^C087%^r-i%^RESET%^%^C123%^m%^C159%^a%^C123g%^RESET%^%^C087%^e%^RESET%^%^C052%^!%^CRST%^",({ob}));
            ob->set_hp(-100);
            continue;
        }
        else
        {
            tell_object(ob,"%^RESET%^%^C052%^The w%^RESET%^%^C088%^a%^C124%^v%^C160%^e %^RESET%^%^C052%^of %^RESET%^%^C240%^death %^RESET%^%^C052%^passes through you, and you barely retain your %^RESET%^%^C087%^soul%^RESET%^%^C052%^!%^CRST%^");
            tell_room(place,"%^RESET%^%^C052%^The w%^RESET%^%^C088%^a%^C124%^v%^C160%^e %^RESET%^%^C052%^of %^RESET%^%^C240%^death %^RESET%^%^C052%^passes through "+ob->QCN+"%^RESET%^%^C052%^, and they barely retain their %^RESET%^%^C087%^soul%^RESET%^%^C052%^!%^CRST%^",({ob}));
            ob && ob->cause_typed_damage(ob, ob->return_target_limb(), sdamage,"divine");
            ob && ob->set_property("fester", sdamage / 2);
            continue;
        }
    }
 
    call_out("dest_effect", 1 + (6 * clevel) / 10); 
}

void dest_effect()
{
    if(pointerp(targets) && sizeof(targets))
    {
        foreach(object ob in targets)
        {
            if(!objectp(ob))
                continue;
        
            tell_object(ob, "You feel your wounds stop festering.");
            ob->remove_property("fester");
        }
    }
    
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
