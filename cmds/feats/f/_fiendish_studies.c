#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("CrimsonTemplar");
    feat_name("fiendish studies");
    feat_prereq("Crimson Templar L1");
    feat_desc("The Crimson Templar is a being who is singularly focused on the destruction of evil and chaos in their purest forms. With this feat, the Crimson Templar gains +2 to attack and damage against chaotic or evil outsiders (see help favored types). Their studies have also how to best take advantage of weaknesses in their enemies and they gain the ability to sneak attack, adding up to 3d6 of sneak attack damage with 10 levels.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if(!ob->is_class("crimson_templar"))
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
