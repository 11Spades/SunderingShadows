#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("CrimsonTemplar");
    feat_name("heavenly fire");
    feat_prereq("Crimson Templar L4");
    feat_desc("With the help of their sacred church, the Crimson Templar is gifted the power to aid in the fight against evil. With this feat, the Crimson Templar's sneak attacks are empowered with heavenly fire, inflicting additional divine damage (up to 3d6). In addition, the Crimson Templar gains fiery body, trial by fire, fire shield, dimension door, true seeing, alter self, and greater invisibility as innate spells.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if(ob->query_class_level("crimson_templar") < 4)
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
