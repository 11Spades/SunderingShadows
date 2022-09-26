/*
  _chains_of_justice.c
  
  Inquisitor capstone feat.
  Affects one enemy target with damage sharing, reducing a portion
  of damage taken by the inquisitor and routing it to the affected
  target.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>

#define DELAY 120

inherit FEAT;

object feat;

void create()
{
    ::create();
    set_author("tlaloc");
    feat_type("instant");
    feat_category("Inquisition");
    feat_name("chains of justice");
    feat_prereq("Inquisitor L31");
    feat_syntax("chains_of_justice [TARGET]");
    set_save("will");
    feat_desc("With this feat, the inquisitor enacts divine retribution upon one unlucky foe. The foes must make a will save or be wrapped in divine chains. 20% of all damage the inquisitor takes will instead be inflicted on the target, causing divine damage. The target of this feat must be an existing attacker. This feat has a cooldown.");
    set_target_required(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) {
        return 0;
    }
    if(ob->query_class_level("inquisitor") < 31)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_chains_of_justice(string str)
{
    if(!objectp(this_player()))
        return 0;
    
    if(!stringp(str))
        return 0;

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);
    return 1;
}

void execute_feat()
{
    object *foes;
    string color, mess;
    
    ::execute_feat();
    
    if((int)caster->query_property("using instant feat"))
    {
        tell_object(caster,"You are already in the middle of using a feat!");
        dest_effect();
        return;
    }
    
    if(caster->query_property("chains of justice"))
    {
        dest_effect();
        return;
    }
        
    if(caster->cooldown("chains of justice"))
    {
        tell_object(caster, "You're not ready to use Chains of Justice yet.");
        dest_effect();
        return;
    }
    
    foes = caster->query_attackers();
    
    if(!objectp(target) || member_array(target, foes) < 0)
    {
        tell_object(caster, "That is not a valid target.");
        dest_effect();
        return;
    }
    
    if(is_evil(caster))
        mess = CRAYON_D->color_string("You throw blackened chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "very black");
    else if(is_good(caster))
        mess = CRAYON_D->color_string("You throw heavenly chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "lightning yellow");
    else
        mess = CRAYON_D->color_string("You throw spectral chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "sierra");
    
    tell_object(caster, mess);
    
    if(is_evil(caster))
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws blackened chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "very black");
    else if(is_good(caster))
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws heavenly chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "lightning yellow");
    else
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws spectral chains of divinity at " + target->query_cap_name() + ".%^RESET%^", "sierra");
    
    tell_room(place, mess, ({ caster, target }));

    if(is_evil(caster))
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws blackened chains of divinity at you.%^RESET%^", "very black");
    else if(is_good(caster))
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws heavenly chains of divinity at you.%^RESET%^", "lightning yellow");
    else
        mess = CRAYON_D->color_string(caster->query_cap_name() + " throws spectral chains of divinity at you.%^RESET%^", "sierra");
    
    tell_object(target, mess);
    
    caster->use_stamina(roll_dice(1,6));
    caster->set_property("using instant feat",1);
    spell_kill(target,caster);
    
    return;
}

void execute_attack()
{
    string mess;
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    
    caster->remove_property("using instant feat");    
    ::execute_attack();
    
    if(!objectp(target) || !present(target,place))
    {
        tell_object(caster,"Your target is no longer here!");
        dest_effect();
        return;
    }
    
    caster->add_cooldown("chains of justice", DELAY);
    
    if(do_save(target, 5 + BONUS_D->query_stat_bonus(caster, "wisdom")))
    {
        tell_object(target, "%^BOLD%^WHITE%^You manage to resist the chains!%^RESET%^");
        tell_room(place, "%^BOLD%^WHITE%^" + target->query_cap_name() + " manages to resist the chains!%^RESET%^", target);
        dest_effect();
        return;
    }
    
    if(is_evil(caster))
        mess = CRAYON_D->color_string("The blackened divine chains wrap around " + target->query_cap_name() + " tightly.%^RESET%^", "very black");
    else if(is_good(caster))
        mess = CRAYON_D->color_string("The heavenly chains of divinity wrap around " + target->query_cap_name() + " tightly.%^RESET%^", "lightning yellow");
    else
        mess = CRAYON_D->color_string("The spectral chains of divinity wrap around " + target->query_cap_name() + " tightly.%^RESET%^", "sierra");
    
    tell_room(place, mess, target);

    if(is_evil(caster))
        mess = CRAYON_D->color_string("The blackened divine chains wrap around you tightly.%^RESET%^", "very black");
    else if(is_good(caster))
        mess = CRAYON_D->color_string("The heavenly chains of divinity wrap around you tightly.%^RESET%^", "lightning yellow");
    else
        mess = CRAYON_D->color_string("The spectral chains of divinity wrap around you tightly.%^RESET%^", "sierra");
    
    tell_object(target, mess);
    
    caster->set_property("chains of justice", target);
    call_out("dest_effect", 60);
    return;
}

void dest_effect()
{
    if(objectp(caster) && caster->query_property("chains of justice"))
    {
        tell_object(caster, "%^BOLD%^You release your chains of justice.%^RESET%^");
        caster->remove_property("chains of justice");
    }
    
    ::dest_effect();
}
    