#include <std.h>

inherit FEAT;

int help();

void create() 
{
    ::create();
    feat_type("permanent");
    feat_category("WildernessLore");
    feat_name("guardian of nature");
    feat_prereq("Druid L31");
    feat_desc("The druid becomes a true guardian of the natural order, and the natural world around them lends them its strength. While the druid is not within a city, he gains +2 attack bonus, +2 damage bonus, and +2 caster level.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("druid") < 31)
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

