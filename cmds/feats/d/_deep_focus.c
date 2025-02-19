#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("Psionics");
    feat_name("deep focus");
    feat_prereq("Psywarrior L21");
    feat_desc("With this feat, the psywarrior achieves a greater focus in battle and now can gain an additional level of focus, called firmly focused. This is essentially a second charge of focus that can be used in battle before losing your focused state.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    
    if(ob->query_class_level("psywarrior") < 21)
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
