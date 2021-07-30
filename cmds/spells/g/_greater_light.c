// greater light
//Giving paladins light after discussions with other Imms ~Circe~ 2/20/13
//When/if daylight changes, they may lose light again

#include <spell.h>
#include <magic.h>
#include <std.h>

inherit SPELL;
object ob;

create()
{
    ::create();
    set_spell_name("greater light");
    set_spell_level(([ "paladin": 3, "cleric" : 3, "inquisitor": 3, "mage" : 3, "magus" : 3, "bard" : 3 ]));
    set_spell_sphere("alteration");
    set_syntax("cast CLASS greater light");
    set_description("This will create a large ball of light, which will light your way. This ball is more powerful than that given by the light spell. You may only possess one ball of light at a time.");
    set_non_living_ok();
    set_helpful_spell(1);
}

string query_cast_string()
{
    return "%^YELLOW%^" + CASTER->QCN + " closes " +
        CASTER->QP + " eyes and reaches out " +
        CASTER->QP + " hands, gathering in energy.";
}

spell_effect(int prof)
{
    int level;
    int duration;

    if(present("ball of light", caster))
    {
        tell_object(caster, "You already possess a ball of light.");
        return;
    }
    
    if (interactive(caster)) {
        tell_object(caster, "You create a mystical light source.");
        tell_room(place, caster->QCN + " makes a mystical light source.", ({ caster, target }));
        if (interactive(target) && !(caster == target)) {
            tell_object(target, caster->QCN + " touches you and a light appears.\n");
        }
    } else {
        tell_room(place, caster->QCN + " creates a mystical light source.", caster);
    }
    level = clevel;

    ob = new("/d/magic/obj/light");
    duration = 60 * clevel + 180;
    duration = duration > 540 ? 540 : duration;
    spell_duration = duration;
    set_end_time();
    call_out("dest_effect",spell_duration);
    ob->set_property("spell", TO);
    ob->set_property("spelled", ({ TO }));

    if (!target) {
        ob->move((TP), 4);
    }else {
        ob->move((target), 4);
    }
    spell_successful();
}

void dest_effect()
{
    if (find_call_out("dest_effect") != -1) {
        remove_call_out("dest_effect");
    }
    tell_room(place, "%^YELLOW%^The room is suddenly darker.");
    if (objectp(ob)) {
        ob->remove();
    }
    ::dest_effect();
    if (objectp(TO)) {
        TO->remove();
    }
}
