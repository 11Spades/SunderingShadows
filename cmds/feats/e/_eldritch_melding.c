#include <std.h>
#include <daemons.h>
inherit FEAT;

void create()
{
   ::create();
   feat_type("permanent");
   feat_category("PactBond");
   feat_name("eldritch melding");
   feat_prereq("Warlock L14");
   feat_desc("As the tether to your patron grows, certain secrets are revealed. Shortcuts, if you will. Why study an object for hours to determine its intricacies when greater powers already possess such knowledge? What is a little more soul compared to vast applications of the arcane with a mere snap of the fingers? With this feat, the warlock gains +5 when rolling to use off-class spells on wands and other enchanted items. (this does not apply to scrolls)");
   permanent(1);
   allow_blind(1);
   set_required_for(({}));
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("warlock") < 14) {
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
