#include <std.h>
#include <daemons.h>
inherit FEAT;

void timer(object tp);

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("CombatManeuvers");
    feat_name("improved shieldbash");
    feat_prereq("Shieldbash");
    feat_desc("With this feat you are able avoid the attack of opportunity when performing a shieldbash. Your shieldbash also gets a +2 modifier to its attack roll, and +2 damage dice.");
    permanent(1);
}

int allow_shifted()
{
    return 1;
}

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    if (!FEATS_D->has_feat(ob, "shieldbash")) {
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
