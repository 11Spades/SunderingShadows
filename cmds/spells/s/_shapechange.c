#include <spell.h>
#include <daemons.h>
inherit SPELL;
int bonus;

string *valid_forms()
{
    return ({"dragon","demon","golem"});
}

void create()
{
    ::create();
    set_spell_name("shapechange");
    set_spell_level(([ "oracle" : 8, "innate" : 9, "druid" : 9, "sorcerer" : 9 ]));
    set_spell_sphere("alteration");
    set_mystery(({"dragon"}));
    set_syntax("cast CLASS shapechange on demon|golem|dragon");
    set_description("With this spell you transform into one of several fearsome creatures. In the new form you won't be able to access your inventory, but you will possess mighty melee abilities. The potency of the form will grow with your power, but it won't benefit from the transformation spell. In addition winged forms can use <wing> command to travel.

%^BOLD%^%^RED%^N.B.%^RESET%^ You can set an alternative description, speech string, and adjective for these forms.");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_helpful_spell(1);
}

int preSpell()
{
    object shape;
    string *forms;
    if(objectp(shape = caster->query_property("shapeshifted")) ||
       objectp(shape = caster->query_property("transformed")) ||
       objectp(shape = caster->query_property("dance-of-cuts")) ||
       objectp(shape = caster->query_property("altered")))
    {
        tell_object(caster,"You are already in an alternative form!");
        return 0;
    }
    
    forms = valid_forms();
    
    if(spell_type == "oracle")
    {
        forms = ({ "dragon" });
    }
    if(spell_type == "innate" && FEATS_D->usable_feat(caster,"command the stone"))
    {
        forms = ({ "golem" });
    }    
    if(member_array(arg,forms)==-1)
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

    new("/std/races/shapeshifted_races/mage_"+arg+".c")->init_shape(caster,arg);

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
