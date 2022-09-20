#include <std.h>

inherit FEAT;

void create() 
{
    ::create();
    feat_type("permanent");
    feat_category("Hexblade");
    feat_name("inevitable steel");
    feat_prereq("Hexblade L7");
    feat_desc("The hexblade has proven himself a worthy combatant with magic and steel. His patron bestows upon him the ability to summon a patron weapon of his choice. The Hexblade gains the eldritch bow, eldritch claws, eldritch glaive, and eldritch scimitar spells as bonus mastered spells (these have been buffed significantly from before). In addition, the Hexblade can no longer be disarmed while wielding one of these patron weapons.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob))
        return 0;
    
    if(ob->query_class_level("hexblade") < 7)
    {
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

