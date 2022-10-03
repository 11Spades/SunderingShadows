#include <std.h>
#include <daemons.h>
inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("AdvancedTraining");
    feat_name("fighter reflexes");
    feat_prereq("Fighter L21, Advanced Training Feat");
    feat_desc("This feat represents a fighter's ability to hone their reflexes to an astonishing degree. This feat grants the fighter their weapon mastery bonus to their reflex save.");
    permanent(1);
    set_required_for(({}));
}

int prerequisites(object ob) 
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("fighter") < 21) {
       dest_effect();
       return 0;
    }
   
    if(!FEATS_D->has_feat(ob,"advanced training")) {
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

