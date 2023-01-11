#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

int MAX;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Duelist");
    feat_name("positioning");
    feat_prereq("Swipe");
    //feat_syntax("positioning offensive|defensive|min|max|check");
    feat_desc("With this feat, you learn to make use of perfect timing and space to be ready to take advantage of any disruption in your foe's attention. When an opponent is vulnerable to you (paralyzed, blind, or fighting someone else), you have a chance to get an extra attack on that target.");
    set_target_required(0);
    permanent(1);
    allow_blind(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if (!objectp(ob)) { return 0; }
    if (!FEATS_D->has_feat(ob, "swipe"))
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

/*
int cmd_positioning(string str)
{
    object feat;
    if (!objectp(TP)) { return 0; }
    if (str) str = lower_case(str);
    if (str != "offensive" &&
        str != "defensive" &&
        str != "max" &&
        str != "min") {
        str = "check";
    }	
    if((int)TP->is_wearing_type("shield")){
        tell_object(TP,"%^RESET%^%^BOLD%^You can't be wearing a shield.%^RESET%^");
        return 1;
    }
	if(!TP->validate_combat_stance("one hander")){
        tell_object(TP,"%^RESET%^%^BOLD%^You must be wielding a single one-handed weapon.%^RESET%^");
        return 1;
    }	
    feat = new(base_name(TO));
    feat->setup_feat(TP, str);
    return 1;
}

int check_my_status(object ob)
{
    if (!objectp(ob)) { return 0; }

    if (ob->query_bound() || ob->query_unconscious() || ob->query_tripped())
    {
        tell_object(ob, "You are unable to move well enough to do that.");
        return 0;
    }
    return 1;
}

void execute_feat()
{
    int bonus, maxbonus;

    if (!check_my_status(caster))
    {
        dest_effect();
        return;
    }

    ::execute_feat();

    bonus = (int)caster->query_property("tactical_positioning");
    maxbonus = (int)caster->query_base_character_level() / 4 + 1;
    maxbonus = (maxbonus < 5 ? maxbonus : 5);

    switch (arg)
    {

    case "defensive":
        if (!bonus)
        {
            tell_object(caster, "%^RESET%^%^MAGENTA%^You can't fight any more defensively!%^RESET%^");
            break;
        }
        caster->set_property("tactical_positioning", 1);
        caster->add_ac_bonus(1);
        caster->add_attack_bonus(-1);
        tell_object(caster, "%^BOLD%^%^RED%^You shift your stance to better defend against attacks!%^RESET%^");
        break;

    case "offensive":
        if (bonus == -maxbonus)
        {
            tell_object(caster, "%^RESET%^%^MAGENTA%^Your can't fight any less defensive!%^RESET%^");
            break;
        }
        caster->set_property("tactical_positioning", - 1);
        caster->add_ac_bonus(-1);
        caster->add_attack_bonus(1);
        tell_object(caster, "%^BOLD%^%^CYAN%^You shift your stance to fight more aggressively!%^RESET%^");
        break;
    case "max":
        caster->set_property("tactical_positioning", maxbonus - bonus);
        caster->add_ac_bonus(maxbonus - bonus);
        caster->add_attack_bonus(bonus - maxbonus);
        tell_object(caster, "%^BOLD%^%^RED%^You shift your stance to better defend against attacks!%^RESET%^");
        break;
    case "min":
        caster->set_property("tactical_positioning", -maxbonus - bonus);
        caster->add_ac_bonus(-maxbonus - bonus);
        caster->add_attack_bonus(bonus + maxbonus);
        tell_object(caster, "%^BOLD%^%^CYAN%^You shift your stance to fight more aggressively!%^RESET%^");
        break;
    case "check":
        tell_object(caster, "%^RESET%^%^GREEN%^You have shifted %^MAGENTA%^" + bonus + " %^RESET%^%^GREEN%^points into "
            + "tactical positioning.%^RESET%^");
        break;
    }

    dest_effect();
    return;
}
*/

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
