#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("ArcaneSpellcraft");
    feat_name("deep magic");
    feat_prereq("Mage L31");
    feat_desc("The mage has reached a pinnacle of power and understanding in their studies. It is at this point that they begin to delve into the deeper recesses of the weave to grasp power long lost With this feat, the mage gains access to Deep Magic, another type of magic, similar to cantrips or innate. To utilize deep magic spells you have, type use the following syntax.
    
    recall deep spells
    cast deep <spell name>

The mage starts with the wish spell. Any new deep magic must be acquired by finding tomes of knowledge in the world, which will be introduced periodically.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    
    if(ob->query_class_level("mage") < 31)
        return 0;

    return ::prerequisites(ob);
}


void execute_feat() {
    ::execute_feat();
    dest_effect();
}

void permanent_effects(object ob) {
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob) {
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void dest_effect() {
    ::dest_effect();
    remove_feat(TO);
    return;
}
