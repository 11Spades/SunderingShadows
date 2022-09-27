#include <std.h>
#include <spell.h>
#include <magic.h>
#include <rooms.h>
inherit SPELL;

int num_mon, amount;
object controller;

#define UNDEADDIR "/d/magic/mon/create_undead/"

void fail();

void create()
{
    ::create();
    set_spell_name("dance of the dead");
    set_spell_level(([ "bard" : 4 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS dance of the dead [on TARGET]");
    set_damage_desc("raises no more than three skeletal champions at a time");
    set_description("%^RESET%^With this spell, the bard plays or sings a dirge to the dead, causing dead bodies or bones to rise up and move or fight on command. Unlike animate dead, this song infuses the corpses with the bard's own life force, using 10% of their current hit points. This spell has a shorter duration than animate dead and the dead will collapse once the song is over, returning the lost health to the bard." + extra_help());
    set_verbal_comp();
    set_somatic_comp();
    evil_spell(1);
    set_non_living_ok(1);
    set_helpful_spell(1);
}

string extra_help(){

    return "

Each undead will use one pool slot, with five pool slot maximum.
Undead pool is shared across similar spells.
To remove undead use %^ORANGE%^<dismiss undead>%^RESET%^
To command undead use %^ORANGE%^<command undead to %^ORANGE%^%^ULINE%^ACTION%^RESET%^%^ORANGE%^>%^RESET%^
To force lost undead to follow use %^ORANGE%^<command undead to follow>%^RESET%^
To check how many undead you have rised use %^ORANGE%^<poolsize>%^RESET%^";
}


void spell_effect(int prof)
{
    object* targs = ({}), * temp = ({}), * inven = ({}), undead;
    int i, j, lvl, flag;

    if (target && objectp(target) && !target->is_room()) {
        if (!target->is_corpse()) {
            fail();
            return;
        }
        targs = ({ target });
    }else {
        targs = all_inventory(environment(caster));

        for (i = 0; i < sizeof(targs); i++) {
            if (!targs[i]->is_corpse()) {
                continue;
            }
            temp += ({ targs[i] });
        }
        targs = temp;

        if (!sizeof(targs)) {
            tell_object(caster, "%^RESET%^%^BOLD%^%^There are no remains here to play for.%^RESET%^");
            TO->remove();
            return;
        }
    }
    
    amount = caster->query_hp() / 10;

    if (present("undead_controller", caster)) {
        controller = present("undead_controller", caster);
    }else {
        controller = new("/d/magic/obj/undead_controller");
        controller->set_caster(caster);
        controller->move(caster);
    }

    num_mon = (int)caster->query_property("raised");
    if (!intp(num_mon)) {
        num_mon = 0;
    }
    if (num_mon >= 5) {
        tell_object(caster, "%^RESET%^%^BOLD%^%^BLACK%^You can't cause any more remains to dance!%^RESET%^%^RESET%^");
        tell_room(environment(caster), "%^CYAN%^" + caster->QCN + " seems to strain doing something.%^RESET%^", caster);
        TO->remove();
        return;
    }

    spell_successful();

    for (i = 0; i < sizeof(targs) && i < 2; i++) {
        undead = new(UNDEADDIR + "skeleton");
        lvl = 1;

        if (num_mon > 4) {
            undead->remove();
            tell_object(caster, "%^RESET%^%^BOLD%^%^BLACK%^Causing more to dance is beyond your power.%^RESET%^");
            tell_room(environment(caster), "%^CYAN%^" + caster->QCN + " seems to strain doing something.%^RESET%^", caster);
            TO->remove();
            return;
        }

        inven = all_inventory(targs[i]);
        inven->move(undead);

        targs[i]->remove();
        num_mon += lvl;

        undead->set_property("raised", 1);
        undead->set_property("minion", caster);
        undead->move(environment(caster));

        undead->set_guild_level("fighter", clevel);
        undead->set_weap_enchant(clevel / 12);
        undead->set_skill("athletics", clevel);
        undead->set_skill("perception", clevel);
        undead->set_level(clevel);
        undead->set_hd(clevel, 4);

        undead->set_max_hp(clevel * 10);
        undead->set_hp(undead->query_max_hp());
        undead->set_overall_ac(5 - clevel);
        undead->control(caster);
        caster->add_follower(undead);

        undead->add_id("summoned monster");
        undead->set_property("spell", TO);
        undead->set_property("spell_creature", TO);
        undead->set_property("minion", caster);
        controller->add_monster(undead);
        caster->set_property("raised", 1);

    }
    tell_object(caster, "%^C243%^You play a %^C099%^d%^C105%^i%^C111%^s%^C117%^c%^C111%^o%^C105%^r%^C099%^dant%^C243%^, %^C098%^h%^C104%^a%^C110%^u%^C116%^n%^C110%^t%^C104%^i%^C098%^ng%^C243%^ %^C116%^melody%^C243%^ and the corpses begin to stir!%^CRST%^");
    tell_room(place, "%^C243%^" + caster->query_cap_name() + " plays a %^C099%^d%^C105%^i%^C111%^s%^C117%^c%^C111%^o%^C105%^r%^C099%^dant%^C243%^, %^C098%^h%^C104%^a%^C110%^u%^C116%^n%^C110%^t%^C104%^i%^C098%^ng%^C243%^ %^C116%^melody%^C243%^ and the corpses begin to stir!%^CRST%^", caster);
    spell_successful();
    caster->add_hp(-amount);
    call_out("dest_effect", ROUND_LENGTH * clevel);
    return;
}

void fail()
{
    tell_object(caster, "%^RESET%^%^BOLD%^%^BLACK%^Nothing happens...%^RESET%^%^RESET%^");
    tell_room(environment(caster), "%^CYAN%^" + caster->QCN + " seems disappointed.", caster);
    TO->remove();
    return;
}

void dest_effect()
{
    objectp(caster) && tell_object(caster, "%^C116%^Your dirge to the dead ends and your minions collapse.%^CRST%^");
    caster->add_hp(amount);
    objectp(controller) && controller->remove();
    
    if (objectp(TO)) {
        TO->remove();
    }
}

string query_cast_string()
{
    return "%^C116%^" + caster->query_cap_name() + " begins to play a low, resonate tone.%^CRST%^";
}
