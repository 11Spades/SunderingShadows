#include <std.h>
#include <daemons.h>
inherit FEAT;

int help();

void create() {
    ::create();
    feat_type("instant");
    feat_category("ArcaneTrickster");
    feat_name("invisible thief");
    feat_syntax("invisible_thief, step");
    feat_desc("An arcane trickster continues to merge her understanding of stealthy and arcane arts. She learns to become invisible like under greater invisibility spell as a free action.

To become visible again she must use the %^ORANGE%^<step>%^RESET%^ command.");
    set_target_required(0);
}

int allow_shifted() { return 1; }

int prerequisites(object ob) {
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("arcane_trickster") < 4) {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_invisible_thief(string str) {
    object invisob;
    if(!objectp(TP)) { return 0; }
    invisob=new("/d/magic/obj/invisobgreater.c");
    invisob->set_player_name(caster->query_name());
    invisob->set_mychance(clevel/2);
    invisob->move(caster);
    return 1;
}

void dest_effect() {
    ::dest_effect();
    remove_feat(TO);
    return;
}
