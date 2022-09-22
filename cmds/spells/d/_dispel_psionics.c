#include <std.h>
#include <spell.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

string arg;
int theProf;
object targ;

void dispel(object ob);
int checkDispel(object ob);

void create() {
    ::create();
    set_spell_name("dispel psionics");
    set_spell_level(([ "psion" : 3 ]));
    set_spell_sphere("psychokinesis");
    set_syntax("cast CLASS dispel psionics [on TARGET]");
    set_description("Despite the name, dispel psionics will dispel effects created by both psionics and magic, whether it "
"be divine or arcane in nature.  The chance to dispel a particular effect depends upon the ability of the psion versus "
"the ability of the effect's caster.  A psion may manifest this item on a room or on a particular target.");
    set_arg_needed();
    set_verbal_comp();
    set_somatic_comp();
}

string query_cast_string() {
    return CASTER->QCN+" casts "+CASTER->QP+" gaze about, and the "+
       "area shimmers briefly with a translucent substance!";
}

int dispel_power()
{
    return 0;
}

int preSpell() {
    if (!query_arg()) return 1;
    targ = present(query_arg(), query_place());
    if (!targ) {
        tell_object(query_caster(), "That is not here.");
        return 0;
    }
    return 1;
}

void spell_effect(int prof) {
    object *allinv;
    int i;
    theProf = prof;

    caster = query_caster();
    place = query_place();
    arg = query_arg();
    clevel += dispel_power();
    
    if(!objectp(place))
        return;

    tell_room(place, "%^BOLD%^The air shimmers as "+caster->QCN+" %^BOLD%^%^WHITE%^completes a spell.", caster);
    tell_object(caster, "%^BOLD%^The air in the area begins to shimmer.");

    if (targ && !objectp(targ)) {  // if there was a target set but it's gone, dispel
        dest_effect();
        return;
    }
    if(targ && !caster->ok_to_kill(targ)) {   // fixed from target *Styx* 1/25/05
        dest_effect();
        return;
    }
    
    //Holy shit this section - imagine aoe farming and there are a hundred items on the floor and dozens of mobs in room and a witch doctor casts this
    if (!targ) {  // now, if there wasn't a target set, do the room
        allinv = deep_inventory(place);
        allinv = target_filter(allinv);
        allinv += ({place});
      } else {
        allinv = deep_inventory(targ);
        allinv += ({targ});
    }

    //And then some of your targets have 8-10 buffs on them and aoe spells
    for (i = 0;i < sizeof(allinv);i++) {
        if (!objectp(allinv[i])) continue;
        if(!caster->ok_to_kill(allinv[i])) continue;
        if (allinv[i]->query_property("spelled"))
            dispel(allinv[i]);
    }

    dest_effect();
    return 1;
}

void dispel(object ob) {
    object *spells;
    int i;

    if (!objectp(ob)) {
        return;
    }

    if (!ob->query_property("spelled")) {
        return;
    }
    if (ob->query_true_invis()) {
        return;
    }

    if (pointerp(ob->query_property("spelled"))) {
        spells = ob->query_property("spelled");
    }else {
        spells = ({ ob->query_property("spelled") });
    }

    if (!sizeof(spells)) {
        return;
    }

    shuffle(spells);
    
    if(sizeof(spells) > 10)
        spells = spells[0..9];

    for (i = 0; i < sizeof(spells); i++) {
        if (!objectp(ob)) {
            continue;
        }
        if (!objectp(spells[i])) {
            continue;
        }
        if (i > clevel / 12 + 1) {
            tell_object(caster, "You fail to dispel the " + spells[i]->query_spell_name());
            continue;
        }
        if (!checkDispel(spells[i])) {
            tell_object(caster, "You fail to dispel the " + spells[i]->query_spell_name());
            continue;
        }
        tell_object(caster, "You dispel the " + spells[i]->query_spell_name());
        ob->remove_property_value("spelled", ({ spells[i] }));
        spells[i]->dest_effect();
    }

    return;
}

int checkDispel(object ob)
{
    return "/std/magic/dispel"->checkDispel(ob, clevel, caster);
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();

}

