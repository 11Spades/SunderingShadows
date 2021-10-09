#include <std.h>
#include <daemons.h>

inherit FEAT;

string *allowed = ({ "mage", "sorcerer" });

void create()
{
    ::create();
    set_author("tlaloc");
    feat_type("instant");
    feat_category("MetaMagic");
    feat_name("counterspell");
    feat_prereq("Mage or Sorcerer L31");
    feat_syntax("counterspell [TARGET]");
    feat_desc("This Meta Magic feat will attempt to cause your target's spell to fail. The target must be in the process of casting a spell for this to work. First a spellcraft check against DC 15 +  opponent caster level must be made. Then the feat will consume a random prepared spell, for mages, or a prepared spell slot, for sorcerers, equal to the level of the spell being countered.");
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
    return ::prerequisites(ob);
}

int cmd_counterspell(string str)
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
    int DC, level;
    
    ::execute_feat();

    if(!objectp(caster))
    {
        dest_effect();
        return;
    }

    if(caster->cooldown("counterspell"))
    {
        tell_object(caster, "You can't use counterspell yet.");
        dest_effect();
        return;
    }
    
    if(!target)
    {
        tell_object(caster, "That target is not here.");
        dest_effect();
        return;
    }
    
    spell = target->query_property("spell_casting");
    
    if(!objectp(spell))
    {
        tell_object(caster, "Your target is not casting a spell.");
        dest_effect();
        return;
    }
    
    DC = spell->query_clevel() + 15;
    
    if(DC > caster->query_skill("spellcraft") + roll_dice(1, 20))
    {
        tell_object(caster, "%^CYAN%^The spell resists your attempt to counter it!");
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
    available = keys(caster->query_all_memorized(my_class)[level]);
    
    if(!pointerp(available) || !sizeof(available))
    {
        tell_object(caster, "You don't have any spells prepared of the proper level.");
        dest_effect();
        return;
    }
    
    spell_to_use = available[random(sizeof(available))];
    
    if(spell_to_use == "generic")
        spell_to_use = "level " + level + "";
    
    if(!this_player()->forget_memorized(my_class, spell_to_use, 1))
    {
        tell_object(caster, "The spell you are using to counter failed.");
        dest_effect();
        return;
    }
    
    tell_object(caster, "%^BOLD%^You use your meta magic knowledge to counter " + target->query_cap_name() + "'s spell.");
    target->set_property("counterspell", 1);
    caster->add_cooldown("counterspell", 600);

    dest_effect();
    return;
}

void dest_effect()
{
    if(objectp(caster))
    {
        caster->remove_property("quicken spell");
    }
    ::dest_effect();
    remove_feat(TO);
    return;
}
