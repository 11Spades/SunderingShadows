#include <priest.h>
inherit SPELL;

#define BAN ({ "deva", "shade", "ghost", "unborn" })

void create()
{
    ::create();
    set_spell_name("mask of many faces");
    set_spell_level(([ "warlock" : 1 ]));
    set_spell_sphere("alteration");
    set_syntax("cast CLASS mask of many faces [on [RACE] [0-9]] ");
    set_description("%^RESET%^With this spell, the warlock opens themselves fully to the power of their patron, allowing their very self to be moulded into a new form. This spell allows the caster to make major changes to their body and pretend to be be someone else. These are usually sufficient changes that they become unrecognizable even to those they are familiar with. It does not allow for such drastic changes as body size or overall shape, so be aware of races you turn into.\n\nAdjective, description, speech, messages etc will be remembered across castings, so they will only need to be set once in your alternative form. Players will be able to recognize your 'other self' as a unique entity, separate from your usual self.\n\nYou can have up to caster level / 12 + 1 alternate profiles. To switch between them use numbers from 0 to 9 as the spell argument. Default profile number is 0. The spell will also remember last profile used and will use it by default.");
    set_verbal_comp();
    set_somatic_comp();
    set_peace_needed(1);
    set_helpful_spell(1);
    set_arg_needed(1);
}

int preSpell()
{
    object shape;
    if(objectp(shape = caster->query_property("shapeshifted")) || objectp(shape = caster->query_property("altered")))
    {
        tell_object(caster,"You are already in an alternative form!");
        return 0;
    }
    return 1;
}

string query_cast_string() {
	return "%^BOLD%^%^WHITE%^"+YOU+" closes "+MINE+" eyes and concentrates deeply.";
}

void spell_effect(int prof)
{
    string * eargs,earg;
    string profile;
    string raceto;

    if (arg) {
        eargs = explode(arg, " ");
    }

    raceto = caster->query("race");

    if (sizeof(eargs)) {
        foreach(earg in eargs)
        {
            if (regexp(earg, implode(RACE_D->query_races(), "|"))) {
                raceto = earg;
            }
            if(member_array(raceto, BAN) != -1){
                tell_object(caster, "%^C059%^That isn't a proper race selection.%^CRST");
                dest_effect();
                return;
            }
            if (regexp(earg, "[0-9]")) {
                if (atoi(earg) < (clevel / 10 + 1)) {
                    profile = "spell_alter_self_" + (1000 - atoi(earg));
                    caster->set("alter_self_profile", profile);
                }else {
                    tell_object(caster, "You can't have that many profiles!");
                    dest_effect();
                    return;
                }
            }
        }
    }

    if (!objectp(caster) || !userp(caster)) {
        TO->remove(); return;
    }
    new("/std/races/shapeshifted_races/spell_alter_self.c")->init_shape(caster,raceto);
    spell_successful();
    addSpellToCaster();
}

void dest_effect()
{
    object shape;
    if(objectp(caster))
    {
        if(objectp(shape = caster->query_property("altered"))) shape->reverse_shape(caster);
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
