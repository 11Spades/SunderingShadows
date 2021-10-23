#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

int timer, flag, stage, toggle, counter;

//This spell is way more powerful in SRD. Rewrite this.
void create()
{
    ::create();
    set_spell_name("cloudkill");
    set_spell_level(([ "mage" : 5, "magus" : 5 ]));
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS cloudkill");
    set_damage_desc("acid");
    set_description("This spell generates a bank of fog, similar to a fog cloud, except that its vapors are yellowish green and poisonous. For the duration of the spell's effect, the area will be filled with greenish poisonous arsine gas. This gas will instantly kill any enemies that are 1/4 of the casters clevel. Enemies that are less than half the caster's clevel must make a combat death save or die. Any enemies who are not killed inhale the gas, becoming poisoned with arsenic, which causes constitution damage. The longer the vicitms remain in the area, the more stacks of this poison that will be applied.");
    set_verbal_comp();
    set_somatic_comp();
    aoe_spell(1);
    set_save("fort");
    set_aoe_message("%^ORANGE%^(%^GREEN%^engulfed in acidic fog%^ORANGE%^)%^RESET%^");
}

string query_cast_string()
{
    tell_room(place, "%^GREEN%^" + caster->QCN + " %^RESET%^%^GREEN%^draws an %^ORANGE%^a%^ORANGE%^c%^GREEN%^i%^ORANGE%^d %^ORANGE%^i%^GREEN%^n%^ORANGE%^f%^GREEN%^use%^ORANGE%^d %^ORANGE%^s%^GREEN%^igil%^GREEN%^ in the air.%^RESET%^%^RESET%^");
    return "display";
}

void spell_effect(int prof)
{
    tell_object(caster, "%^RESET%^%^GREEN%^You take quick retreat from %^ORANGE%^t%^GREEN%^he %^ORANGE%^s%^GREEN%^i%^ORANGE%^g%^GREEN%^il%^GREEN%^ as it opens a portal and fumes rush through it!%^RESET%^%^RESET%^");
    tell_room(place, "%^GREEN%^" + caster->QCN + "%^GREEN%^ takes cover as %^GREEN%^aci%^ORANGE%^d%^ORANGE%^i%^GREEN%^g %^GREEN%^si%^ORANGE%^g%^GREEN%^il%^GREEN%^ explodes and fumes rush through the open portal!%^RESET%^%^RESET%^", caster);
    counter = clevel * 3;
    addSpellToCaster();
    spell_successful();
    execute_attack();
}

void execute_attack()
{
    object* foes = ({}), targ;
    object poison;
    int i, dam;

    if (!flag) {
        flag = 1;
        ::execute_attack();
        return;
    }

    if (!objectp(caster) || !objectp(place) || !present(caster, place) || counter < 0) {
        dest_effect();
        return;
    }

    foes = target_selector();
    foes -= ({ caster });
    
    foreach(object ob in foes)
    {
        if(ob->is_undead())
            continue;
        
        if((ob->query_character_level() < clevel / 4) ||
        (ob->query_character_level() < clevel / 2 && !combat_death_save(ob, 0)))
        {
            tell_room(place, "%^GREEN%^BOLD%^" + ob->query_cap_name() + " is instantly slain by the poisonous cloud!", ob);
            tell_object(ob, "%^GREEN%^BOLD%^You are instantly slain by the poisonous cloud!");
            ob->set_hp(-100);
            continue;
        }
        
        tell_object(ob, "%^GREEN%^You inhale the poisonous gas, feeling your lungs bubbling and foaming as you gag and retch.");
        tell_room(place, "%^GREEN%^BOLD%^" + ob->query_cap_name() + " retches on the poison gas.");
        
        poison = new("/d/common/obj/poisons/base/arsenic");
        poison->set_poison_dc(clevel / 2);
        POISON_D->apply_poison(ob, poison, caster, "inhaled");
        spell_kill(ob, caster);
    }
        

    /*
    for (i = 0; i < sizeof(foes); i++) {
        if (!objectp(targ = foes[i])) {
            continue;
        }
        dam = sdamage;

        if (do_save(targ, 0)) {
            dam /= 2;
        }

        tell_object(targ, "%^RESET%^%^GREEN%^You choke on %^GREEN%^a%^ORANGE%^c%^ORANGE%^i%^GREEN%^d%^ORANGE%^i%^ORANGE%^c %^GREEN%^fu%^ORANGE%^m%^ORANGE%^e%^GREEN%^s!%^RESET%^%^RESET%^");
        tell_room(place, "%^GREEN%^" + targ->QCN + " %^RESET%^%^GREEN%^chokes on %^ORANGE%^a%^GREEN%^cid%^ORANGE%^i%^GREEN%^c %^ORANGE%^f%^GREEN%^umes%^ORANGE%^!%^RESET%^%^RESET%^", ({ targ }));
        damage_targ(targ, targ->return_target_limb(), sdamage, "acid");
    }
    */
    counter--;
    place->addObjectToCombatCycle(TO, 1);
}

void dest_effect()
{
    if (objectp(place)) {
        tell_object(place, "%^RESET%^%^GREEN%^The %^ORANGE%^a%^ORANGE%^c%^GREEN%^idic %^GREEN%^fo%^ORANGE%^g%^GREEN%^ finally disperses!%^RESET%^%^RESET%^");
    }
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
