#include <std.h>
#include <spell.h>
#include <magic.h>
#include <priest.h>
#include <daemons.h>

#define BAN ({ "soulforged", "deva", "shade", "alaghi", "ghost", "nightwing", "barrus", "illithid", "unborn", "dragon", "squole" })

inherit SPELL;

string *types = ({ "plant", "animal", "human" });
string *valid_races;
int cocooned = 0;

object cocoon, cocoon_inside;

void create()
{
    ::create();
    set_spell_name("cocoon");
    set_spell_level(([ "innate" : 9 ]));
    set_mystery("nature");
    set_spell_sphere("alteration");
    set_syntax("cast CLASS cocoon on RACE");
    set_damage_desc("Envelop yourself in a cocoon and become another race");
    set_description("With this ability, the oracle spins a silvery, silk-threaded cocoon around themselves, entering a stage of metamorphosis. While in the cocoon, the caster will not be able to leave or teleport. When they emerge, they will have become the race of their choice. This ability has a long cooldown.\n\nCocooning into a pk race will cause your nopk flag to be removed.");
    set_arg_needed();
    set_verbal_comp();
    set_somatic_comp();
}

string query_cast_string()
{
    return "%^CYAN%^"+caster->QCN+" lifts "+caster->QP+" head and lets out a call to the wilds.";
}

int color(string str)
{
    return CRAYON_D->color_string(str, "dark green");
}

int preSpell()
{
    int size;
    
    if(caster->cooldown("cocoon"))
    {
        tell_object(caster, "You can't use cocoon yet. Type <cooldowns> to see your wait time.");
        return 0;
    }
    if(!arg)
    {
        tell_object(caster, "You need to choose a race to change into.");
        return 0;
    }
    if(arg == caster->query_race())
    {
        tell_object(caster, "You are already that race!");
        return 0;
    }
    if(caster->query_current_attacker())
    {
        tell_object(caster, "You can't spin a cocoon during combat!");
        dest_effect();
        return;
    }
    
    valid_races = RACE_D->query_races();
    valid_races -= BAN;
    
    if(member_array(arg, valid_races) < 0)
    {
        tell_object(caster, capitalize(arg) + " is not a valid race. Valid races are :");
        tell_object(caster, "%^GREEN%^" + implode(valid_races, ", "));
        return 0;
    }
    if(!USER_D->is_valid_terrain(place->query_terrain(), "forest"))
    {
        tell_object(caster, "You need to be in the forest to use this ability.");
        return 0;
    }
    
    return 1;
}
    
void spell_effect(int prof)
{
    
    if(!objectp(caster))
        return;
 
    if(catch(cocoon = new("/d/magic/room/cocoon.c")) ||
    catch(cocoon_inside = new("/d/magic/room/cocoon_inside.c")))
    {
        tell_object(caster, "Something went wrong. Contact a creator.");
        dest_effect();
        return;
    }
    
    tell_object(caster, color("You begin to spin a cocoon of silky threads around yourself."));
    tell_room(place, "%^GREEN%^" + caster->query_cap_name() + " begins to spin silky threads around " + caster->query_objective() + ".", caster);
       
    spell_successful();
    caster->add_cooldown("cocoon", 86400);
    call_out("finish_cocoon", ROUND_LENGTH);
}

void finish_cocoon()
{
    if(!objectp(caster))
        return;
    
    if(caster->query_current_attacker())
    {
        tell_object(caster, "Your cocoon spinning was interrupted!");
        dest_effect();
        return;
    }
    
    if(!cocoon_inside->setup_cocoon(types[random(sizeof(types))]))
    {
        tell_object(caster, "Something went wrong with the cocoon.");
        dest_effect();
        return;
    }

    cocoon->move(place);    
    caster->move_player(cocoon_inside);
    
    tell_object(caster, color("You spin the silky threads around you and finish your cocoon."));
    tell_room(place, "%^GREEN%^BOLD%^" + caster->query_cap_name() + " finishes spinning the threads into a complete cocoon!", caster);
    cocooned = 1;
    call_out("dest_effect", 15 * ROUND_LENGTH);
}
    
void dest_effect()
{
    if(objectp(caster) && cocooned)
    {
        tell_object(caster, color("You wriggle and push your way out. You burst into open, fresh air, a brand new " + arg + "."));
        tell_room(place, "%^GREEN%^The cocoon begins to wriggle then bursts open, revealing a " + arg + ".", caster);
        caster->move_player(place);
        if(!caster->query("cocooned")) caster->set("cocooned", caster->query_race());
        caster->set_race(arg);
    }
    cocoon_inside->remove();
    cocoon->remove();
    
    ::dest_effect();
}

