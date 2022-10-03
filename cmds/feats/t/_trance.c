/*
  _trance.c
  
  CombatPrescience rewrite.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit FEAT;

int mod;
string path;

void create()
{
    ::create();
    
    feat_type("instant");
    feat_category("Psionics");
    feat_name("trance");
    feat_prereq("Psywarrior L5");
    feat_syntax("trance");
    feat_classes("psywarrior");
    feat_desc("This feat allows the psywarrior to enter a specialized battle trance to aid them in combat. This trance gives the psywarrior full base attack and a few bonus attacks each round. This trance also adds other buffs based on the psywarrior's warrior path. See specific warrior path help files for more information.");
    allow_blind(1);
    psionic(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) return 0;
    if(ob->query_class_level("psywarrior") < 5)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_trance(string str)
{
    object feat;
    if(!objectp(this_player())) { return 0; }
    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(),str);
    return 1;
}

void execute_feat()
{
    int duration;
    
    if((int)caster->query_property("prescienced"))
    { //won't stack with the Prescience power
        tell_object(caster,"You are already enjoying the effects of prescience!");
        this_object()->remove();
        return;
    }
    if((int)caster->query_property("using instant feat"))
    {
        tell_object(caster,"You are already in the middle of using a feat!");
        dest_effect();
        return;
    }
    
    ::execute_feat();
    
    if(!USER_D->spend_pool(caster, 1, "focus"))
    {
        tell_object(caster, "You must have psionic focus to use trance!");
        dest_effect();
        return;
    }
    
    tell_object(caster,"%^RESET%^%^ORANGE%^You pluck the very essence of planning from the air around you, giving you insight into battle.%^RESET%^");
    tell_room(place,"%^RESET%^%^ORANGE%^Strange symbols flash in " + caster->query_cap_name() + "'s eyes as " + caster->query_subjective() + " gives a warcry.%^RESET%^",caster);
    caster->set_property("dance-of-cuts", 1); //Makes them full BAB
    
    mod = 2 + caster->query_class_level("psywarrior") / 16;
    path = caster->query("warrior path");
    strlen(path) && tell_object(caster, "%^YELLOW%^You focus on the " + path + " path!");

    switch(path)
    {
        case "ascetic":
        caster->add_skill_bonus("spellcraft", mod);
        caster->add_saving_bonus("all", 2);
        caster->add_ac_bonus(mod);
        break;
        case "assassin":
        caster->add_skill_bonus("stealth", mod);
        caster->add_damage_bonus(mod);
        break;
        case "gladiator":
        caster->add_skill_bonus("influence", mod);
        caster->set("gladiator trance", mod);
        break;
        case "survivor":
        caster->add_skill_bonus("survival", mod);
        caster->set_property("damage resistance", mod);
        caster->set_property("fire resistance", mod);
        caster->set_property("cold resistance", mod);
        break;
        case "weaponmaster":
        caster->add_skill_bonus("academics", mod);
        caster->add_attack_bonus(mod);
        break;
    }
    
    caster->set_property("prescienced", 1);
    caster->set_property("using instant feat",1);
    duration = ROUND_LENGTH * (8 + mod + BONUS_D->query_stat_bonus("intelligence", caster));
    
    if(FEATS_D->has_feat(caster, "eternal warrior"))
        duration *= 2;
    
    call_out("dest_effect", duration);
}

void execute_attack()
{
    int extra;
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    
    caster->remove_property("using instant feat");
    ::execute_attack();
    
    if(caster->query_current_attacker())
    {
        extra = 1 + flevel / 31;
        extra += (FEATS_D->has_feat(caster, "battle psyche"));
    
        tell_object(caster, "%^CYAN%^BOLD%^You unleash a barrage of additional attacks!%^RESET%^");
    
        for(int x = 0; x < extra; x++)
        {
            if(caster->query_current_attacker())
                caster->execute_attack();
        }
    }
        
    environment(caster)->addObjectToCombatCycle(this_object(),1);
}

void dest_effect()
{
    if(objectp(caster))
    {
        tell_object(caster,"%^RESET%^%^ORANGE%^Your insight into battle fades, leaving you feeling slightly disoriented.%^RESET%^");
        
        switch(path)
        {
            case "ascetic":
            caster->add_skill_bonus("spellcraft", -mod);
            caster->add_saving_bonus("all", -2);
            caster->add_ac_bonus(-mod);
            break;
            case "assassin":
            caster->add_skill_bonus("stealth", -mod);
            caster->add_damage_bonus(-mod);
            break;
            case "gladiator":
            caster->add_skill_bonus("influence", -mod);
            caster->set("gladiator trance", -mod);
            break;
            case "survivor":
            caster->add_skill_bonus("survival", -mod);
            caster->set_property("damage resistance", -mod);
            caster->set_property("fire resistance", -mod);
            caster->set_property("cold resistance", -mod);
            break;
            case "weaponmaster":
            caster->add_skill_bonus("academics", -mod);
            caster->add_attack_bonus(-mod);
            break;
        }
        
        caster->remove_property("dance-of-cuts");
        caster->remove_property("prescienced");
        
    }
    
    ::dest_effect();
    remove_feat(this_object());
}   