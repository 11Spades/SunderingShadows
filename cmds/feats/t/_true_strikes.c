#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Duelist");
    feat_name("true strikes");
    feat_prereq("Positioning");
    feat_desc("This feat increases accuracy of your strikes when you use one single-handed weapon.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    object *weapons;
    if(!objectp(ob)) { return 0; }
    if(!FEATS_D->has_feat(ob,"positioning") ||
       ob->is_wearing_type("shield"))
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
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
