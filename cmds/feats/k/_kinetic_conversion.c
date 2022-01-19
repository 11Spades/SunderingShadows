#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Archpsion");
    feat_name("kinetic conversion");
    feat_prereq("Archpsion L4, Power Surge");
    feat_desc("The Archpsion has become a master of the nature of energy and the astral. With this feat, the Archpsion will occasionally be able to convert the energy of a non-physical attack into latent astral energy, shunting it into the astral plane. This will reduce the damage by half. This is a passive feat that consumes focus on triggering. This feat will only trigger on non-physical hits of significant size.");
    permanent(1);
    set_required_for(({"perfect manifesting"}));
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("archpsion") < 4 || !FEATS_D->usable_feat(ob,"power surge"))
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
