#include <spell.h>
#include <daemons.h>
inherit SPELL;
int bonus;

string *valid_forms()
{
    return ({"cat", "bear", "wolf", "bird"});
}

void create()
{
    ::create();
    set_spell_name("animal shape");
    set_spell_level(([ "cleric" : 8, ]));
    set_domains("animal");
    set_mystery("nature");
    set_spell_sphere("alteration");
    set_syntax("cast CLASS animal shape on cat|wolf|bear|bird");
    set_description("With this spell you transform into one of several fearsome creatures. In the new form you won't be able to access your inventory, but you will possess mighty melee abilities. The potency of the form will grow with your power, but it won't benefit from the transformation spell. In addition, winged forms can use <wing> command to travel.

%^BOLD%^%^RED%^N.B.%^RESET%^ You can set an alternative description, speech string, and adjective for each form.");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_helpful_spell(1);
}

int preSpell()
{
    object shape;
    if(objectp(shape = caster->query_property("shapeshifted")) ||
       objectp(shape = caster->query_property("transformed")) ||
       objectp(shape = caster->query_property("dance-of-cuts")) ||
       objectp(shape = caster->query_property("altered")))
    {
        tell_object(caster,"You are already in an alternative form!");
        return 0;
    }
    if(member_array(arg,valid_forms())==-1)
    {
        tell_object(caster,"Invalid form, valid forms are: "+implode(valid_forms(),", "));
        return 0;
    }
    return 1;
}

void spell_effect(int prof)
{
    object shape;
    if (!objectp(caster)){
        TO->remove();
        return;
    }

    if (!objectp(caster)) {
        dest_effect();
        return;
    }

    new("/std/races/shapeshifted_races/druid_"+arg+".c")->init_shape(caster,arg);

    shape = caster->query_property("shapeshifted");
    shape->set_clevel(clevel);
    bonus = clevel/4+1;
    spell_successful();

    caster->set_property("spelled", ({TO}) );
    addSpellToCaster();
}

void dest_effect()
{
    object shape;
    if (objectp(caster)) {
        if (objectp(shape = caster->query_property("shapeshifted"))) {
            shape->reverse_shape(caster);
        }
    }
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
