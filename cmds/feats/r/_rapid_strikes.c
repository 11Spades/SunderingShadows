#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("UnarmedCombat");
    feat_name("rapid strikes");
    feat_prereq("Spinning kick");
    feat_desc("Rapid strikes is a passive feat that gives an extra attackwhen fighting unarmed.");
    permanent(1);
    set_required_for(({"improved rapid strikes","unarmed parry"}));
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) {return 0; }

    if(!FEATS_D->has_feat(ob,"spinning kick"))
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
