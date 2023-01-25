#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() 
{
    ::create();
    set_author("wedex");
    feat_type("permanent");
    feat_category("Steel&Magic");
    feat_name("arcane pool");
    feat_prereq("Magus L1");
    feat_classes("magus");
    feat_desc("The magus gains a reservoir of mystical arcane energy that takes the form of two different resources. The first is the arcane pool, which he can draw upon to either cast spells without using a prepared spell slot or to activate weapon or armor enhancements. The second resource are enhancement pool, which determines how many different weapon or armor enhancements he can add to his weapon and armor, which last for one minute per magus level. The magus has the following weapon enhancements available by default: flaming, flaming burst, frost, icy burst, shock, shocking burst. Armor enhancements, other types of elemental enhancements, and extensions to the durations of each can be gained through arcana feats.\n\nThe arcane pool size is half your magus level plus your intelligence modifier.\nThe enhancement pool is one at first level and one additional point for every eight additional levels.\n\nSee also: enhance, enhancements");
    set_required_for(({ "enduring arcana", "greater arcane pool", "corrosive arcana", "thundering arcana", "devoted arcana", "warding", "augment physical prowess" }));
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    if (!ob->is_class("magus")) {
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
    remove_feat(this_object());
    return;
}