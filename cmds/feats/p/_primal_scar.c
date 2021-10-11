/*
  _counterspell.c
  
  Metamagic feat for Sorcerer and Mage L31.
  
  This is just one of a group of metamagic feats to help give
  Mages and Sorcerers the edge in terms of raw spellcasting.
  
  Counterspell will first need to overcome a spellcraft skill check,
  then will consume a same-level spell to counter the spell the
  target is currently casting.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>

inherit FEAT;

string *allowed = ({ "oracle" });

void create()
{
    ::create();
    set_author("tlaloc");
    feat_type("instant");
    feat_category("MetaMagic");
    feat_name("primal scar");
    feat_prereq("Spellscar Oracle L31");
    feat_syntax("primal scar TARGET");
    feat_desc("This Meta Magic feat will attempt to scar your target with primal wild magic, causing the next spell they cast to go wild with a random spell effect instead. This feat will first attempt a spellcraft roll against the target's spellcraft. If succeeded, a level 9 spell slot will be consumed to scar the target. You must have a level 9 slot prepared to use this feat. This feat has a cooldown.");
    set_target_required(1);
    set_required_for(({ }));
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    int success = 0;
    string *classes;

    if(!objectp(ob)) { return 0; }

    classes = ob->query_classes();

    foreach(string cls in classes)
    {
        if(member_array(cls, allowed) >= 0)
        {
            if(ob->query_class_level(cls) > 30)
                success = 1;
        }
    }

    if(!success)
    {
        return 0;
    }
    
    if(ob->query_mystery() != "spellscar")
        return 0;
    
    return ::prerequisites(ob);
}

int cmd_primal_scar(string str)
{
    object feat;
    if(!objectp(this_player())) { return 0; }

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);
    return 1;
}

void execute_feat()
{
    object obj, spell;
    string type, my_class, spell_to_use;
    mapping available;
    int DC, level, base;
    
    ::execute_feat();

    if(!objectp(caster))
    {
        dest_effect();
        return;
    }

    if(caster->cooldown("primal scar"))
    {
        tell_object(caster, "You can't use primal scar yet.");
        dest_effect();
        return;
    }
    
    if(!target)
    {
        tell_object(caster, "That target is not here.");
        dest_effect();
        return;
    }
    
    if(target->query_property("spellscarred"))
    {
        tell_object(caster, "That target is already scarred by wild magic.");
        dest_effect();
        return;
    }
    
    //Should work most of the time unless target is a clearly better spellcaster
    DC = 10 + target->query_skill("spellcraft");
    base = caster->query_skill("spellcraft") + BONUS_D->query_stat_bonus(caster, "charisma");
    
    if(DC > base + roll_dice(1, 20))
    {
        tell_object(caster, "%^CYAN%^Your target resists your attempt to scar them with wild magic!");
        caster->add_cooldown("primal scar", 300);
        dest_effect();
        return;
    }
    
    type = spell->query_spell_type();
    
    foreach(string str in allowed)
    {
        if(caster->query_class_level(str) >= 31)
            my_class = str;
    }
    
    level = spell->query_spell_level(type);
    available = keys(caster->query_all_memorized(my_class)[9]);
    
    if(!pointerp(available) || !sizeof(available))
    {
        tell_object(caster, "You don't have any level 9 spells prepared.");
        dest_effect();
        return;
    }
    
    spell_to_use = "level 9";
    
    if(!this_player()->forget_memorized(my_class, spell_to_use, 1))
    {
        tell_object(caster, "The spell you are using to scar your opponent failed.");
        dest_effect();
        return;
    }
    
    tell_object(caster, "%^BOLD%^%^CYAN%^You use your primal knowledge to scar " + target->query_cap_name() + " with wild magic.");
    target->set_property("spellscarred", 1);
    caster->add_cooldown("primal scar", 300);

    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
