#include <std.h>
#include <daemons.h>
#include <magic.h>
inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("RangedCombat");
    feat_name("improved preciseshot");
    feat_prereq("Preciseshot");
    feat_desc("With this feat you are able to avoid being tripped on a failed preciseshot. This feat also adds +2 to your attack roll with preciseshot and adds two additional damage dice.");
    set_required_for(({  }));
}

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    if (!FEATS_D->has_feat(ob, "preciseshot")) {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
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