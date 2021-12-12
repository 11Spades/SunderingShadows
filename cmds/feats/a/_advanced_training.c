#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("AdvancedTraining");
    feat_name("advanced training");
    feat_prereq("Fighter L21");
    feat_desc("Dedicated fighters are known for their peerless training in martial pursuits. With this feat, the fighter unlocks a group of Advanced Training feats to choose from. In addition, the fighter gains an additional 10% damage with all weapons.");
    permanent(1);
    set_required_for(({ "abundant tactics", "fighter finesse", "fighter reflexes", "aura of confidence", "defensive weapon training", "armored juggernaut", "master armorsmith", "master weaponsmith", "unmoving" }));
}

int prerequisites(object ob) 
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("fighter") < 21)
    {
        dest_effect();
        return 0;
    }
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

