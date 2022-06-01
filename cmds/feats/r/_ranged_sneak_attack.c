#include <std.h>
#include <daemons.h>
inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("PeerlessArcher");
    feat_name("ranged sneak attack");
    feat_prereq("Peerless Archer L1");
    feat_desc("The Peerless Archer has become an expert at exploiting enemy weaknesses from afar. With this feat, the Peerless Archer gains up to 3d6 sneak attack damage against targets that are vulnerable to him, as long as the show came from a bow. These peerless archer sneak attack dice and a +2 attack bonus also apply to your shoot command.");
    permanent(1);
    set_required_for(({}));
}

int prerequisites(object ob)
{
    if (!objectp(ob))
    {
        return 0;
    }

    if ((int)ob->query_class_level("peerless_archer") < 1)
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