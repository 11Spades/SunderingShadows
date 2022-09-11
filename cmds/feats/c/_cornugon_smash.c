#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("WeaponMastery");
    feat_name("cornugon smash");
    feat_prereq("Powerattack");
    feat_desc("Beat fear into your opponents with your unmatched combat prowess. While using powerattack, your hits have a chance of demoralizing opponents. When you hit an opponent (with powerattack), you perform an intimidation check. On a successful check, the victim is shaken.");
    permanent(1);
    set_target_required(0);
    set_required_for(({}));
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
    
    if(!FEATS_D->has_feat(caster, "powerattack"))
        return 0;
    
    return ::prerequisites(ob);
}

void execute_feat()
{
    ::execute_feat();
    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
