#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Psionics");
    feat_name("martial power");
    feat_prereq("Psywarrior L11");
    feat_desc("With this feat, the psychic warrior is able to manifest his psionic powers in the midst of combat, while fully attacking, as long as he is has psionic focus. Damage spells cast during combat will have reduced damage.");
    psionic(1);
    permanent(1);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if(ob->query_class_level("psywarrior") < 11)
    {
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
