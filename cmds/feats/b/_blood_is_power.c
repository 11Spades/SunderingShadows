#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("ArcaneSpellcraft");
    feat_name("blood is power");
    feat_prereq("L31 Sorcerer");
    feat_desc("The power of your bloodline flows through your veins, and you push your capabilities further than ever before, reaching deep into your innate powers to extract just a little bit more. With this feat, you gain an additional mastery slot for each spell level.");
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    int *clslvls;
    string *clss;

    if (!objectp(ob)) {
        return 0;
    }

    if(ob->query_class_level("sorcerer") < 31)
    {
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
