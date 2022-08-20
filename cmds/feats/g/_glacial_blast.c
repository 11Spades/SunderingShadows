#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
   ::create();
   feat_type("permanent");
   feat_category("PactBond");
   feat_name("glacial blast");
   feat_prereq("Warlock L1");
   feat_desc("This feat represents the ability to apply the 'glacial' modifier to your eldritch blast and eldritch strikes. Upon hitting the opponent, they must make a fortitude save or be chilled, reducing their dexterity by 4 for a short time. This blasttype will also change the damage type of your eldritch blast and eldritch strikes to cold.\n\See Also: help blasttype");
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
