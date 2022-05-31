#include <std.h>
#include <daemons.h>
inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("PeerlessArcher");
    feat_name("sharp shooting");
    feat_prereq("Peerless Archer L7");
    feat_desc("The Peerless Archer is the master of terrain, cover and concealment. He has learned how best to use cover whilst also possessing the knowledge to dead eye shots into cover to hit their target. With this feat, the Peerless Archer gains 10% MissChance and their shots ignore 20% of their enemies' MissChance, as long as the shot was fired from a bow.");
    permanent(1);
    set_required_for(({}));
}

int prerequisites(object ob)
{
    if (!objectp(ob))
    {
        return 0;
    }

    if ((int)ob->query_class_level("peerless_archer") < 4)
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