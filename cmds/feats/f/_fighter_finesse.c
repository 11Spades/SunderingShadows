#include <std.h>
#include <daemons.h>
inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("FighterEnhancement");
    feat_name("fighter finesse");
    feat_prereq("Fighter L21, Advanced Training Feat");
    feat_desc("This feat allows an experienced dexterity-based fighter to utilize their dexterity on all weapons, despite their size.");
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
   
   if(!FEATS_D->has_feat(ob,"AdvancedTraining")) {
       dest_effect();
       return 0;
}
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

