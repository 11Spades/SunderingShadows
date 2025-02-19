#include <std.h>
#include <daemons.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("MeleeAccuracy");
    feat_name("lethal strikes"); // Improved critical
    feat_desc("This feat represents your ability to strike in a much more lethal manner. This will double the critical threat range with weapons or when unarmed.
    
%^BOLD%^N.B.%^RESET%^ This feat does not stack with the Keen Edge spell.");
    permanent(1);
}

int allow_shifted()
{
    return 1;
}

int prerequisites(object ob)
{
    if (!objectp(ob)) {
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
