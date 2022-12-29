#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int timer,flag,stage,toggle,counter;


void create()
{
    ::create();
    set_spell_name("thirsting tendrils");
    set_spell_level(([ "warlock" : 4 ]));
    set_heritage("fey");
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS thirsting tendrils");
    set_damage_desc("piercing, paralyzed, life leach");
    set_description("Strange plant-like tendrils shoot from the warlock's palms, sinking into the earth before erupting and attacking everything in the area. Odd suckers and glistening thorns wreathe about the lashing plant life, grasping and ensnaring any victims, draining their life essence to replenish the warlock.");
    set_save("reflex");
    set_verbal_comp();
    set_somatic_comp();
    aoe_spell(1);
    set_aoe_message("%^RESET%^%^CRST%^%^C130%^(%^C040%^p%^C207%^l%^C040%^a%^C046%^n%^C213%^t%^C040%^-%^C046%^l%^C040%^i%^C207%^k%^C046%^e te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^C100%^lash about%^C130%^)%^CRST%^");
}

void spell_effect(int prof)
{
    tell_object(caster, "%^RESET%^%^CRST%^%^C040%^P%^C207%^l%^C040%^a%^C046%^n%^C213%^t%^C040%^-%^C046%^l%^C040%^i%^C207%^k%^C046%^e te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^shoot from your palms into the %^C058%^ground%^C100%^, erupting a moment later to %^C144%^attack%^C100%^!%^CRST%^");
    tell_room(place, "%^RESET%^%^CRST%^%^C040%^P%^C207%^l%^C040%^a%^C046%^n%^C213%^t%^C040%^-%^C046%^l%^C040%^i%^C207%^k%^C046%^e te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^shoot from "+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C100%^'s palms into the ground, erupting a moment later to %^C144%^attack%^C100%^!%^CRST%^", caster);
    counter = clevel * 3;
    addSpellToCaster();
    spell_successful();
    execute_attack();
}

void execute_attack()
{
    object *foes=({});
    int i;
    string limb;
    int dam, gripped;

    if (!flag) {
        flag = 1;
        ::execute_attack();
        return;
    }

    if (!objectp(caster) || !objectp(place) || !present(caster, place) || counter < 0 || place != environment(caster))
    {
        dest_effect();
        return;
    }

    message("info", "%^RESET%^%^CRST%^%^C100%^Strange %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^loop and lash about nearby.%^CRST%^", nearbyRoom(place,2));

    foes = target_selector();
    foes -= ({ caster });
    
    dam = sdamage;
    gripped = 0;

    foreach(object ob in foes)
    {
        if (!objectp(ob))
            continue;

        limb = ob->return_target_limb();
        
        set_save("reflex");
        
        if(do_save(ob, 0))
        {
            gripped = 0;
            tell_object(ob, "%^C100%^You %^C144%^twist %^C100%^and %^C144%^dodge %^C100%^away from the seeking %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s%^C100%^!%^CRST%^");
        }
        else
        {
            tell_object(ob, "%^RESET%^%^CRST%^%^C100%^The %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^grab hold of you, %^C130%^pinning %^C100%^you in place!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C100%^The %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^grab hold of "+ob->query_cap_name()+"%^RESET%^%^CRST%^%^C100%^, %^C130%^pinning %^C100%^them in place!%^CRST%^", ({ ob }));
            ob->set_paralyzed(6, "%^RESET%^%^CRST%^%^C100%^The %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^have you in their %^C144%^grip%^C100%^!%^CRST%^", 4);
            gripped = 1;
            damage_targ(ob, limb, dam, "piercing");
        }
        //Now a fort save to see if they can avoid the life drain.
        
        set_save("fort");
        
        if(objectp(ob) && gripped && !do_save(ob, 0) && !ob->is_undead())
        {
            tell_object(ob, "%^RESET%^%^CRST%^%^C100%^The %^C046%^t%^C213%^h%^C046%^or%^C040%^n%^C207%^s %^RESET%^%^C144%^bite %^C100%^into your flesh, and the %^C144%^strange suckers %^C100%^feed upon the %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C100%^!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C100%^The %^C046%^t%^C213%^h%^C046%^or%^C040%^n%^C207%^s %^RESET%^%^C144%^bite %^C100%^into "+ob->query_cap_name()+"%^RESET%^%^CRST%^%^C100%^ flesh, and the %^C144%^strange suckers %^C100%^feed upon the %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C100%^!%^CRST%^");
            damage_targ(ob, limb, dam / 8, "negative energy");
            caster->add_hp(dam / 8);
        }
        
        set_save("reflex");
    }

    counter--;
    place->addObjectToCombatCycle(this_object(),1);
}

void dest_effect()
{
    if (objectp(place))
    {
        tell_object(place, "%^RESET%^%^CRST%^%^C058%^The %^C100%^strange %^C046%^te%^C040%^n%^C046%^dr%^C213%^i%^C207%^l%^C046%^s %^RESET%^%^C100%^dry up %^C058%^and crumble to %^C144%^dust%^C058%^.%^CRST%^");
    }
    ::dest_effect();
    if (objectp(this_object()))
        TO->remove();
}
