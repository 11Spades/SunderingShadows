/*
  _warrior_path.c

  Allows the psywarrior to change their chosen warrior path.

  -- Tlaloc -- 
*/

#include <std.h>
#include <daemons.h>
#include <dirs.h>

#define DELAY 259200

inherit FEAT;

string *valid_choices = ({ "ascetic", "assassin", "gladiator", "infiltrator", "survivor", "weaponmaster" });

void create()
{
    ::create();
    set_author("tlaloc");
    feat_type("instant");
    feat_category("Psionics");
    feat_name("warrior path");
    feat_prereq("Psywarrior L3");
    feat_syntax("warrior_path [PATH]");
    feat_desc("This feat allows the psywarrior to choose their warrior path.

Warrior paths grant unique bonuses when using trance and also allow for special maneuvers while under trance.

%^BOLD%^You can select from the following warrior paths:
 Ascetic
 Assassin
 Gladiator
 Infiltrator
 Survivor
 Weaponmaster

A psywarrior that has not made their choice will merely be precluded from access to the path-specific bonuses and maneuvers.

To start selection process type <warrior_path>.

%^RED%^%^BOLD%^See also :%^RESET%^ ascetic path, assassin path, gladiator path, infiltrator path, survivor path, weaponmaster path");
    allow_tripped(1);
}

int allow_shifted() { return 1; }

int cmd_warrior_path(string str)
{
    object feat;

    if(!objectp(this_player()))
        return 0;

    if(this_player()->query_class_level("psywarrior") < 3)
    {
        dest_effect();
        return 0;
    }

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);

    return 1;
}

int execute_feat()
{
    ::execute_feat();

    if(!arg)
    {
        if(!strlen(this_player()->query("warrior path")))
            write("You have no warrior path chosen");
        else
            write("%^BOLD%^You current warrior path is: %^RESET%^RED%^" + this_player()->query("warrior path"));
        return 1;
    }

    if(this_player()->cooldown("warrior path change"))
    {
        write("%^BOLD%^You may only change your warrior path once every three weeks.");
        return 1;
    }

    if(member_array(arg, valid_choices) < 0)
    {
        write("%^BOLD%^Valid choices are : %^RESET%^RED%^" + implode(valid_choices, ", "));
        return 1;
    }

    write("You have selected the %^CYAN%^ " + arg + "%^RESET%^ warrior path. Type <yes> to confirm. Anything else will abort.");
    input_to("confirm_selection", 0);

    return 1;
}

void confirm_selection(string str)
{
    if (str != "yes") {
        tell_object(this_player(), "Aborting...");
        return;
    }

    write("%^BOLD%^You declare your psychic warrior path as : %^CYAN%^" + arg + ".");
    this_player()->set("warrior path", arg);
    this_player()->add_cooldown("warrior path change", DELAY);
    dest_effect();
    return;
}

int prerequisites(object ob)
{
    if (!objectp(ob)) {
        return 0;
    }
    if (!(ob->is_class("psion")))
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
