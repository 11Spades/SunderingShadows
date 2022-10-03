#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("Horsemanship");
    feat_name("bred for war");
    feat_prereq("Mounted combat");
    feat_desc("Your mount is a paragon of war training, resulting in unmatched breeding for war. With this feat, your mount gains additional toughness, gaining your level * 2 additional max hit points, +5 damage resistance, and +5 spell damage resistance. Now your faithful steed can wade into the rigors of war without fear of those who stand below you.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob){
    if(!objectp(ob)) return 0;
    if(!FEATS_D->has_feat(ob,"mounted combat")) {
      dest_effect();
      return 0;
    }
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
