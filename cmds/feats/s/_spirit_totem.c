#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("RagePower");
    feat_name("spirit totem");
    feat_prereq("Barbarian");
    feat_desc("While raging, the barbarian is surrounded by a swarm of spirit whisps. These whisps will harass her enemies, causing negative energy damage. This totem behaves like a travelling AOE spell (and cannot stack with traveling AOE spells). The damage from this ability is increased by the barbarian's charisma bonus. The whisps have no effect on undead enemies. This feat is mutually exclusive with other totem feats.");
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
    if (!ob->is_class("barbarian")) {
        dest_effect();
        return 0;
    }
    
    if(FEATS_D->has_feat(ob, "beast totem") || 
    FEATS_D->has_feat(ob, "air totem") ||
    FEATS_D->has_feat(ob, "celestial totem") ||
    FEATS_D->has_feat(ob, "spire totem") ||
    FEATS_D->has_feat(ob, "daemon totem") ||
    FEATS_D->has_feat(ob, "ancestor totem") ||
    FEATS_D->has_feat(ob, "moon totem"))
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
