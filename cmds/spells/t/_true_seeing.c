#include <spell.h>
#include <magic.h>

inherit SPELL;

object oldenv, *conceal;
int i, num = 0;

void dest_effect();
object *invisobs();
void env_change();
void see_room();
void see_changes();

void create() {
    ::create();
    set_spell_name("true seeing");
    set_spell_level(([ "cleric" : 6,"druid" : 7, "mage" : 6, "inquisitor" : 5, "magus" : 6 ]));
    set_spell_sphere("divination");
    set_spell_domain("magic");
    set_mystery("dragon");
    set_syntax("cast CLASS true seeing");
    set_description("This spell will allow you to see things as they truly are. It will allow you to see through magical invisibility and concealment. It will negate the effects of blindness on yourself, and the effects of blurred movement, displacement and similar effects on opponents. Note: This spell does not negate non-magical hiding effects, such as hide in shadows.");
    set_verbal_comp();
    set_somatic_comp();
	set_helpful_spell(1);
}

string query_cast_string()
{
    tell_object(caster,"%^BLUE%^Closing your eyes, you begin to chant in an even tone.");
	tell_room(place,"%^BLUE%^"+caster->QCN+" closes "+
                ""+caster->QP+" eyes, chanting in an even tone.",caster);
	return "display";
}

int preSpell()
{
    if(caster->detecting_invis() || caster->true_seeing())
    {
        tell_object(caster, "You are already detecting invisible or true seeing.");
        return 0;
    }
    return 1;
}

spell_effect(int prof)
{
    oldenv=environment(caster);
    spell_successful();
    tell_room(environment(caster),"%^BOLD%^%^WHITE%^"+
              caster->QCN+"'s eyes snap open and flash "+
              "bright white for an instant.",caster);
    tell_object(caster,"%^BOLD%^Your eyes snap open and flash bright white for an instant.");
    caster->set_true_seeing(1);
    caster->set_property("spelled", ({TO}) );
    spell_duration = (10 + clevel / 2 * roll_dice(1, 4)) * ROUND_LENGTH;
    set_end_time();
    call_out("dest_effect",spell_duration);
    addSpellToCaster();
}


void dest_effect()
{

    if (caster) {
        tell_object(caster,"%^BOLD%^Your eyes hurt for a moment and you "+
                    "close them, then they flutter open quickly.");
        tell_room(environment(caster),"%^BOLD%^"+caster->QCN+
                  " closes "+caster->QP+" eyes tightly in apparent "+
                  "pain, then they flutter open and "+caster->QS+""+
                  " peers around.",caster);
        caster->set_true_seeing(0);
        caster->remove_property_value("spelled", ({TO}) );
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
