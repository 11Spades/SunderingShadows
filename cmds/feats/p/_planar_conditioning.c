#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
   ::create();
   feat_type("permanent");
   feat_category("PactInvocation");
   feat_name("planar conditioning");
   feat_prereq("Warlock L1");
   feat_desc("With this feat, your patron lends you the capabilities of a planar being by turning your weapon into a magical focus. You may now cast warlock spells as normal while wielding a weapon that is empowered by eldritch strikes.");
   permanent(1);
   allow_blind(1);
   set_required_for(({}));
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("warlock") < 1) {
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

void execute_feat()
{
   ::execute_feat();
   dest_effect();
}

void dest_effect()
{
   ::dest_effect();
   remove_feat(TO);
   return;
}
