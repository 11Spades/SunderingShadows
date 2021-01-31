#include <std.h>
#include <daemons.h>
inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("Horsemanship");
    feat_name("indomitable mount");
    feat_prereq("Mounted combat");
    feat_desc("A character with this feat substitutes a roll on their athletics skill for their mount's saving throw, serving as an indication that they can steer their mount skillfully enough to avoid danger. If the mount's saving throw exceeds the rider's athletics skill, this feat has no effect.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob){
    if(!objectp(ob)) return 0;
    if(!FEATS_D->has_feat(ob, "mounted combat")) {
      dest_effect();
      return 0;
    }
    return 1;
}

void execute_feat(){
    ::execute_feat();
    dest_effect();
}

void permanent_effects(object ob){
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob){
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void dest_effect(){
    ::dest_effect();
    remove_feat(TO);
    return;
}

