#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
   ::create();
   feat_type("permanent");
   feat_category("MeleeAccuracy");
   feat_name("prime strike");
   feat_prereq("Warlock L2");
   feat_desc("No fool should ever leave their back turned to one who has given his soul for power. With this feat, the warlock gains a +1 attack bonus on all attacks (melee and ranged, including ranged touch attacks) against targets that are vulnerable to them (blind, paralyzed, or fighting someone else).");
   permanent(1);
   allow_blind(1);
   set_required_for(({}));
}

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("warlock") < 2) {
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
