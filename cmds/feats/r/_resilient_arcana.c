#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Archmage");
    feat_name("resilient arcana");
    feat_prereq("Archmage L4");
    feat_desc("With this feat, the archmage's magic becomes more resilient than that of others. He gains a bonus to checks against dispel magic effects, making his spells much harder to dispel. In addition, the Archmage's spells become harder to identify by others while being cast.");
    permanent(1);
    set_required_for(({"arcane perfection"}));
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }

    if ((int)ob->query_class_level("archmage") < 4) {
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

void remove()
{
    return ::remove();
}
