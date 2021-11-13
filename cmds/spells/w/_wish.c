/*
  _wish.c

  Similar to shadow spells like shadow alteration.
  Lets you cast other spells, but at a cost. Does not
  have imposed penalties like shadow spells.

  -- Tlaloc -- 10.15.21
*/

#include <std.h>
#include <daemons.h>

#define MAX_MAG 9
#define MAX_OPP 8

inherit SPELL;

void create()
{
    ::create();
    set_spell_name("wish");
    set_spell_level(([ "mage" : 10 ]));
    set_spell_sphere("universal");
    set_syntax("cast CLASS wish on SPELL_NAME [on SPELL_ARGS]");
    set_description("With this spell, the arcanist pulls on the very nature of the weave, changing the universe around them to perform a spell effect. The caster can perform any spell in the game, up to level 9 for most spells, limited to level 8 for spells of the mage's opposing school. This spell can only be used once per day. This spell is considered deep magic and represents the pinnacle of the universalist school of magic.");
    set_arg_needed(1);
    set_silent_casting(1);
}

int preSpell()
{
    int max_level;
    int slevel, mage_level;
    object spell_to_cast;
    string spl, sargs, disc;
    string splfn, ctype;

    if(!stringp(arg))
    {
        tell_object(caster,"You must provide arguments to this spell!");
        return 0;
    }
    
    if(caster->cooldown("wish"))
    {
        tell_object(caster, "You need to wait to use limited wish again.");
        return 0;
    }

    if(sscanf(arg, "%s on %s", spl, sargs)!=2)
        spl = arg;

    if(!stringp(spl))
    {
        tell_object(caster,"You must provide another spell to this spell!");
        return 0;
    }

    spl = replace_string(spl, " ", "_");
    splfn = "/cmds/spells/"+spl[0..0]+"/_"+spl+".c";

    if(!file_exists(splfn))
        {
        tell_object(TP,"Either that spell does not exist, or you do not know it!");
        return 0;
    }
    if(!sargs || sargs == "" || !stringp(sargs))
        sargs = "";
    spell_to_cast = new(splfn);

    mage_level = min(values(MAGIC_D->query_index_row(spl)["levels"]));

    max_level = MAX_MAG;
    
    if(spell_to_cast->query_spell_sphere() == caster->query_opposing_school())
        max_level = MAX_OPP;

    if(mage_level <= max_level)
        slevel = mage_level;
    else
    {
        tell_object(this_player(),"This spell is too powerful for wish!");
        return 0;
    }

    tell_object(caster, "%^BOLD%^CYAN%^You concentrate deeply and bring your deepest desire into being.");
    tell_room(place, "%^BOLD%^CYAN%^" + caster->query_cap_name() + " concentrates deeply and slowly brings " + caster->query_possessive() + " deepest desires into being.", caster);

    spell_successful();

    spell_to_cast->use_spell(this_player(),sargs,clevel);
    caster->add_cooldown("wish", 86400);
    
    return 1;

}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
