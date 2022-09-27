/*
  _soul_theft.c
  
  Abyssal Warlock spell.
  
  -- Tlaloc --
*/

#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int current;
string target_limb;
object *targets;

void create()
{
    ::create();
    set_spell_name("soul theft");
    set_spell_level(([ "warlock" : 4 ]));
    set_heritage("abyssal");
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS soul theft on TARGET");
    set_damage_desc("death on failed save, divine damage on save, fester and heal");
    set_save("fortitude");
    set_description("You unleash the power of the Abyss, attempting to greedily grasp the souls of your target and those nearby. The target makes a death save or dies as their soul is torn asunder, feeding you its very essence, and reducing your soul burn. Those who make their death save will take normalized divine damage and gaining the fester effect for a short period of time and healing you for a smaller amount.");
    evil_spell(1);
    set_verbal_comp();
    set_target_required(1);
    splash_spell(2);
}

string query_cast_string()
{
    return "%^BOLD%^%^BLACK%^" + caster->QCN + " begins to utter an abyssal incantation.%^RESET%^";
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
    
    tell_object(caster,"%^C060%^A c%^C066%^a%^C072%^s%^C078%^c%^C072%^a%^C066%^d%^C060%^e of a%^C066%^b%^C072%^y%^C078%^s%^C072%^s%^C066%^a%^C060%^l %^C078%^energy%^C060%^ tears through the %^C066%^area%^C060%^ around your target, attempting to tear %^C078%^souls%^C060%^ from %^C078%^bodies%^C060%^!%^CRST%^");
    tell_room(place,"%^C060%^A c%^C066%^a%^C072%^s%^C078%^c%^C072%^a%^C066%^d%^C060%^e of a%^C066%^b%^C072%^y%^C078%^s%^C072%^s%^C066%^a%^C060%^l %^C073%^energy%^C060%^ descends upon the area around %^C072%^" + target->query_cap_name() + "%^C060%^, attempting to tear %^C072%^souls%^C060%^ from %^C072%^bodies%^C060%^!%^CRST%^",({caster}));
    
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
            tell_object(ob,"d%^C059%^Divine energy rips through your body, tearing your %^C077%^soul%^C059%^ from your flesh %^C077%^greedily%^C059%^.%^CRST%^");
            tell_room(place,"%^C072%^" + ob->query_cap_name() + "%^C066%^ dies as " + ob->query_possessive() + " %^C078%^soul%^C066%^ is shorn from " + ob->query_possessive() + " %^C078%^flesh%^C066%^!%^CRST%^",({ob}));
            ob->set_hp(-100);
            caster->add_hp(sdamage / 4);
            USER_D->spend_pool(caster, -1, "burn");
            continue;
        }
        else
        {
            tell_object(ob,"%^C078%^You endure through the agony as divine forces attempt to pull your soul from your body, leaving you weakened!%^CRST%^");
            tell_room(place,"%^C078%^" + ob->query_cap_name() + " endures through the soul theft attempt!%^CRST%^",({ob}));
            ob && ob->cause_typed_damage(ob, ob->return_target_limb(), sdamage,"divine");
            ob && ob->set_property("fester", sdamage / 2);
            caster->add_hp(sdamage / 8);
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
