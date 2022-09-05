

#include <spell.h>
#include <magic.h>

inherit SPELL;

int counter, flag;

create()
{
    ::create();
    set_spell_name("grease");
    set_spell_level(([ "mage" : 1, "bard" : 1, "magus" : 1 ]));
    set_spell_sphere("conjuration_summoning");
    set_damage_desc("persistent AOE tripped");
    set_syntax("cast CLASS grease");
    set_description("A grease spell covers the ground with a layer of slippery grease. Any creature in the area must make a successful Reflex save each round or fall prone.");
    set_verbal_comp();
    set_somatic_comp();
    set_save("reflex");
    aoe_spell(1);
    set_aoe_message("%^C094%^(covered in grease)%^CRST%^");
}

string query_cast_string()
{
    return "%^GREEN%^" + caster->query_cap_name() + " steps back and starts a low chant.";
}

spell_effect(int prof)
{
    int save, neededroll, power;
    string strength;
    
    spell_successful();
    addSpellToCaster();
    
    tell_object(caster, "%^GREEN%^You jab your finger and strands of sticky grease shoot out, covering the ground!");
    tell_room(place, "%^GREEN%^" + caster->query_cap_name() + " points " + caster->query_possessive() + " finger and strands of sticky grease shoot out, covering the ground!", ({ caster }));
    
    counter = 1 + clevel / 8;
    execute_attack();
}

void execute_attack()
{
    object *foes=({}),targ;
    int i;
    string limb;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    if(!objectp(caster) || !objectp(place) || !present(caster,place)|| counter<0)
    {
        dest_effect();
        return;
    }

    message("info", "%^RESET%^%^YELLOW%^%^Slippery grease oozes about on the ground!%^RESET%^", place);

    foes = target_selector();
    foes -= ({ caster });

    for(i=0;i<sizeof(foes);i++) {
        if(!objectp(targ = foes[i])) continue;

        limb = targ->return_target_limb();
        if(do_save(targ,0)) {
          tell_object(targ,"%^BOLD%^%^GREEN%^You slip and slide on the grease but manage to keep standing!");
          tell_room(place,"%^GREEN%^"+targ->QCN+" manages to hold on the grease!",({targ}));
        }
        else {
          tell_object(targ,"%^BOLD%^%^GREEN%^Unable to hold your balance, you slip on the grease!%^RESET%^");
          tell_room(place,"%^GREEN%^%^BOLD%^Unable to hold balance, " + targ->query_cap_name() + " slips on the grease!",({targ}));
          targ->set_tripped(1,"%^BOLD%^You are struggling to regain your footing!%^RESET%^",4);
        }
    }

    counter--;
    place->addObjectToCombatCycle(TO,1);
}

void dest_effect()
{
    if(objectp(place)) tell_object(place,"%^YELLOW%^The oozing grease sinks into the ground and disappears.%^RESET%^");
    ::dest_effect();
    if(objectp(this_object())) this_object()->remove();
}
