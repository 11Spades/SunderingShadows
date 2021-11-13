/*
  _limited_wish.c

  Similar to shadow spells like shadow alteration.
  Lets you cast other spells, but at a cost. Does not
  have imposed penalties like shadow spells.
  
  Debating on cost of gold or cooldown.

  -- Tlaloc -- 10.15.21
*/

#include <std.h>
#include <daemons.h>

#define MAX_MAG 6
#define MAX_OPP 5
#define GOLD_COST 10000

inherit SPELL;

void create()
{
    ::create();
    set_spell_name("limited wish");
    set_spell_level(([ "mage" : 7 ]));
    set_spell_sphere("universal");
    set_syntax("cast CLASS limited wish on SPELL_NAME [on SPELL_ARGS]");
    set_description("With this spell, the arcanist pulls on the very nature of the weave, changing the universe around them to perform a spell effect. The caster can perform any spell from the mage/sorcerer list up to level 6, as long as it is not of their opposing school. If the spell is of their opposing school, then the max level becomes 5. Unlike spells like Shadow Evocation, this spell does not cast an illusory version of the spell and thus does not gain the associated penalties. This spell has a cooldown.");
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
    
    /*
    if(caster->query_money("gold") < GOLD_COST)
    {
        tell_object(caster, "You must spend " + GOLD_COST + " gold to cast this spell.");
        return 0;
    }
    */
    
    if(caster->cooldown("limited wish"))
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

    mage_level = spell_to_cast->query_spell_level("mage");

    //If it's not a spell that exists for mages, error message.
    if(!mage_level)
    {
        tell_object(this_player(), "You may only cast mage spells with this spell!");
        return 0;
    }

    max_level = MAX_MAG;
    
    if(spell_to_cast->query_spell_sphere() == caster->query_opposing_school())
        max_level = MAX_OPP;

    if(mage_level <= max_level)
    {
        ctype = "mage";
        slevel = mage_level;
    }
    else
    {
        tell_object(this_player(),"This spell is too powerful for limited wish!");
        return 0;
    }

    tell_object(caster, "%^BOLD%^CYAN%^You concentrate deeply and change the very nature of the universe around you.");
    tell_room(place, "%^BOLD%^CYAN%^" + caster->query_cap_name() + " concentrates deeply and changes the very nature of the universe around " + caster->query_objective() + ".", caster);

    spell_successful();

    spell_to_cast->use_spell(this_player(),sargs,clevel,100,"mage");
    caster->add_cooldown("limited wish", 600);
    
    return 1;

}

void dest_effect()
{
    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
