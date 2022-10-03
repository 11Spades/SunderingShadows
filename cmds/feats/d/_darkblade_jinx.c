#include <std.h>

inherit FEAT;

void create() 
{
    ::create();
    feat_type("permanent");
    feat_category("Hexblade");
    feat_name("darkblade jinx");
    feat_prereq("Hexblade L4");
    feat_desc("The Hexblade gains even greater mastery over their warlock's curse. So much so, that merely swinging their weapon at their enemy will trigger the curse. With this feat, the Hexblade now always has a chance to inflict their curse damage on a foe, even if they miss with their weapon.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob))
        return 0;
    
    if(ob->query_class_level("hexblade") < 4)
    {
        dest_effect();
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

