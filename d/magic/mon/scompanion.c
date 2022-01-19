/*
  scompanion.c

  Bones Oracle summoned companion.

  -- Tlaloc --
*/

inherit WEAPONLESS;

#include <daemons.h>
#include "/d/magic/mon/summoned_monster.h"

#define SAVEDIR "/d/save/summons/" + owner->query_name() + "/skeleton/"

object owner;

string saved_short,
       saved_long;

int setup,
    bonus;

int set_owner(object ob) { owner = ob; return 1; }
object query_owner()     { return owner; }

void create(){
    ::create();
    set_name("companion");
    set_id(({"companion", "greater summon"}));
    set_short("A generic skeleton companion");
    set_race("undead");
    set_hd(4,1);
    set_hp(40);
    set_exp(1);
    set_damage(2, 6);
    set_size(2);
    set_gender("neuter");
    set_funcs( ({ "special_attack" }) );
    set_func_chance(35);
    set_property("function and attack",1);
}

int is_undead() { return 1; }

void init()
{
    ::init();

    if(this_player() != owner)
        return;

    saved_short = read_file(SAVEDIR + "short");
    saved_long = read_file(SAVEDIR + "long");

    //Used read_file here - don't want to save whole object for 2 variables
    if(!strlen(saved_short) && !strlen(saved_long))
    {
        mkdir("/d/save/summons/" + this_player()->query_name());
        mkdir(SAVEDIR);
    }
    else
    {
        set_short(saved_short);
        set_long(saved_long);
    }

    add_action("skeleton_command", "skeleton");
}

int skeleton_command(string str)
{
    string *input;

    if(this_player() != owner)
        return 0;

    input = explode(str, " ");

    if(sizeof(input) < 1)
    {
        tell_object(this_player(), "Syntax : skeleton [long/short/follow].");
        return 1;
    }

    if(sizeof(input) < 2 && (input[0] == "long" || input[0] == "short"))
    {
        tell_object(this_player(), "Syntax : skeleton [long/short] [input].");
        return 1;
    }

    switch(input[0])
    {
        case "short":
        this_object()->set_short(implode(input[1..], " "));
        tell_object(this_player(), "Your Skeleton will now be seen as: \n" + query_short());
        rm(SAVEDIR + "short");
        write_file(SAVEDIR + "short", implode(input[1..], " "));
        break;
        case "long":
        this_object()->set_long(implode(input[1..], " "));
        tell_object(this_player(), "Your Skeleton will now be described as: " + query_long());
        rm(SAVEDIR + "long");
        write_file(SAVEDIR + "long", implode(input[1..], " "));
        break;
        case "command":
        command(implode(input[1..], " "));
        break;
        case "follow":
        tell_object(this_player(), "Your Skeleton is now following you.");
        this_player()->add_follower(this_object());
        return 1;
        default:
        tell_object(this_player(), "Please select 'long', 'short', 'follow' or 'command' as options.");
        return 1;
        break;
    }

    return 1;
}


void heart_beat()
{

    object *attackers,
           room;

    ::heart_beat();

    room = environment(this_object());

    if(!room || !objectp(room))
        return;

    if(!objectp(owner) || owner->query_property("skeleton_companion") != this_object())
    {
        this_object()->remove();
        return;
    }

    //Faithful companion finds his master
    if(objectp(owner) && room != environment(owner))
    {
        this_object()->move(environment(owner));
        owner->add_follower(this_object());
    }

    //Companion hides if master is hiding
    if(!this_object()->query_invis())
    {
        if(owner->query_hidden() || owner->query_invis())
        {
            this_object()->set_invis(1);
            tell_object(owner, "Your skeleton fades into the shadows.");
        }
    }
    else
    {
        if(!owner->query_hidden() && !owner->query_invis())
            this_object()->set_invis(0);
    }

    attackers = owner->query_attackers();

    if(!sizeof(attackers))
    {
        add_hp(query_max_hp() / 20);
        bonus = 0;
    }

    if(query_hp() < query_max_hp() / 2 && present("vial", this_object()))
        command("drink vial");
}

void special_attack(object target)
{
    string tname, aname, mess;
    object room;
    int scale;
    mapping attacks;

    if(!target || !objectp(target))
        return;

    tname = target->query_name();
    aname = capitalize(this_object()->query_name());
    room = environment(this_object());

    if(environment(target) != room)
        return;

    scale = 1 + this_object()->query_level() / 10;
    attacks = ([  ]);

    switch(query_name())
    {
        case "skeleton":
        tell_room(room, "%^BOLD%^" + sprintf("%s tears into %s with its claws.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        break;
    }

    foreach(string str in keys(attacks))
    {
        if(!target)
            return;

        if(sizeof(attacks[str]) < 2)
            return;

        target->cause_typed_damage(target, "torso", attacks[str][0], attacks[str][1]);
    }

    return;
}

void die(object ob)
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "acompanion");
    owner && tell_object(owner, "%^RED%^Your skeletonin crumbles into a pile of bones as it passes from this world!%^RESET%^");
    owner && owner->remove_property("skeleton_companion");
    owner && owner->remove_property("has_elemental");
    remove();
}

int remove()
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "acompanion");
    //all_inventory(this_object())->remove();
    owner && owner->remove_property("skeleton_companion");
    owner && owner->remove_property("has_elemental");
    ::remove();
}
