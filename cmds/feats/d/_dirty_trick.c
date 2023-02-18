/*
  _dirty_trick.c
  
  A combat maneuver geared more towards tricky types.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>

#define COOLDOWN 60

inherit FEAT;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("CombatManeuvers");
    feat_name("dirty trick");
    feat_syntax("dirty_trick [TARGET]");
    feat_prereq("Expertise");
    feat_desc("Dirty Trick is a combat maneuver that allows you to perform a trick on the designated target. If you succeed a Combat Maneuver check, the target will randomly be either blinded, tripped, or sickened. This maneuver gains +2 to Combat Maneuver Bonus and you gain +2 Combat Maneuver Defense against opponents using this feat on you. This feat has a cooldown.");
    set_target_required(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    if (!FEATS_D->has_feat(ob, "expertise"))
    {
        dest_effect();
        return 0;
    }

    return ::prerequisites(ob);
}

int cmd_dirty_trick(string str)
{
    object feat;
    
    if (!objectp(this_player()))
        return 0;

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);
    return 1;
}

void execute_feat()
{
    
    if ((int)caster->query_property("using instant feat"))
    {
        message("failure", "You are already in the middle of using a feat!", caster);
        dest_effect();
        return;
    }
    
    if(caster->cooldown("dirty trick"))
    {
        message("failure", "You're not ready to use dirty trick yet!", caster);
        dest_effect();
        return;
    }
    
    ::execute_feat();
    
    if(!present(target, place))
    {
        message("failure", "Your target is not here.", caster);
        dest_effect();
        return;
    }
    
    message("my spells", "%^C246%^You attempt to perform a dirty trick on " + target->query_cap_name() + ".%^CRST%^", caster);
    message("other spells", "%^C246%^" + caster->query_cap_name() + " attempts to perform a dirty trick on you.%^CRST%^", target);
    message("other spells", "%^C246%^" + caster->query_cap_name() + " attempts to perform a dirty trick on " + target->query_cap_name() + ".%^CRST%^", place, ({ caster, target }));
    
    caster->use_stamina(roll_dice(1, 6));
    caster->set_property("using instant feat", 1);
    spell_kill(target, caster);
    return;
}

void execute_attack()
{
    int bonus, effect, sickened;
    string my_name, your_name;
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    
    caster->remove_property("using instant feat");
    
    if(!objectp(target) || !present(target, place))
    {
        tell_object(caster, "You target is no longer here.");
        dest_effect();
        return;
    }
    
    caster->add_cooldown("dirty trick", COOLDOWN);
    
    bonus = FEATS_D->has_feat(target, "dirty trick") ? 0 : 2;
    my_name = caster->query_cap_name();
    your_name = target->query_cap_name();
    
    if(!BONUS_D->combat_maneuver(target, caster, bonus))
    {
        message("my spells", "%^MAGENTA%^" + your_name + " avoids your dirty trick!", caster);
        message("other spells", "%^MAGENTA%^You avoid the dirty trick!", target);
        dest_effect();
        return;
    }
    
    message("my spells", "%^BOLD%^You feel the impact as your dirty trick lands!%^RESET%^", caster);
    message("other spells", "%^BOLD%^You feel the impact as the dirty trick lands!%^RESET%^", target);
    
    switch(roll_dice(1,3))
    {
        case 1:
        target->set_temporary_blinded(roll_dice(1,6));
        message("my spells", "%^YELLOW%^You grab a handful of dirt from the ground and toss it in " + your_name + "'s eyes!", caster);
        message("other spells", "%^YELLOW%^" + my_name + " grabs a handful of dirt and tosses it in your eyes!%^RESET%^", target);
        break;
        case 2:
        target->set_tripped(roll_dice(1, 6));
        message("my spells", "%^YELLOW%^You kick the back of " + your_name + "'s leg, knocking them down!%^RESET%^", caster);
        message("other spells", "%^YELLOW%^" + my_name + " kicks the back of your leg, knocking you down!%^RESET%^", target);
        break;
        case 3:
        if(!catch(sickened = load_object("/std/effect/status/sickened")))
            sickened->apply_effect(target, roll_dice(1, 6), caster);
        message("my spells", "%^YELLOW%^You sucker punch " + your_name + " in the gut!", caster);
        message("other spells", "%^YELLOW%^" + my_name + " sucker punches you in the gut!", target);
        break;
    }
    
    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    this_object() && remove_feat(this_object());
    return;
}
