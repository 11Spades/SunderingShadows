#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("MagicResistance");
    feat_name("spellbreaker");
    feat_prereq("Disruptive, Fighter L10");
    feat_desc("Your instincts sharpen, allowing you to make an attack of opportunity whenever enemy casts a spell.

%^BOLD%^N.B.%^RESET%^ Stacks with similar feats.");
    permanent(1);
    allow_blind(1);
}

int allow_shifted()
{
    return 1;
}

void execute_feat()
{
    ::execute_feat();
    dest_effect();
}

int prerequisites(object ob)
{
    int magus = 0;
    if (!objectp(ob)) {
        return 0;
    }
    if (ob->is_class("magus") && file_exists("/std/class/magus.c")) {
        magus = (int)"/std/class/magus.c"->fighter_training(ob);
    }
    if (!FEATS_D->has_feat(ob, "disruptive") ||
        !(ob->query_class_level("fighter") + magus >= 10 ||
            ob->query_class_level("magus") >= 9)) {
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

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
