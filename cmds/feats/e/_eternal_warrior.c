#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("Psionics");
    feat_name("eternal warrior");
    feat_prereq("Psywarrior L31");
    feat_desc("This feat represents the pinnacle of mental and physical prowess for the psywarrior. The psywarrior gains an edditional 50 maximum power points. Their trance effect duration is doubled. Finally while they are firmly focused, they gain 10% miss chance and +2 spell resistance.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    
    if(ob->query_class_level("psywarrior") < 31)
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
