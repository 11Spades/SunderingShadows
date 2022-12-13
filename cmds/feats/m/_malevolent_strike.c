#include <std.h>

inherit FEAT;

void create() 
{
    ::create();
    feat_type("permanent");
    feat_category("Hexblade");
    feat_name("malevolent strike");
    feat_prereq("Hexblade L1");
    feat_desc("A Hexblade has a greater understanding the nature of their warlock's curse and now has a chance to apply their curse through normal attacks, making them a far more effective melee combatant. In addition, warlock's curse now uses d8 as its damage dice instead of d6.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob))
        return 0;
    
    if(ob->query_class_level("hexblade") < 1)
    {
        return 0;
    }
    
    return ::prerequisites(ob);
}


void execute_feat()
{
    ::execute_feat();
    dest_effect();
}

void permanent_effects(object ob)
{
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob)
{
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}

