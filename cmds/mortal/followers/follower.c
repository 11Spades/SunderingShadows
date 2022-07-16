// test thief monster
// Modified by Spade Jun. 2022 for the follower system update

#include <std.h>
#include <daemons.h>

inherit NPC;

#define FILE "/d/save/retainers/" + followee->query_name() + "/" + (string)slot


object followee;
int set = 0;
int save_counter, level_up_counter, tick, slot;


void create()
{
    ::create();
    set_spoken("common");
}

void save_follower()
{
    if(!objectp(TO))
    {
        return;
    }
    if(objectp(followee))
    {
        mkdir("/d/save/retainers/" + followee->query_name());
    }
    if(!objectp(ETO))
    {
        return;
    }

    saveMonster(FILE);
}

// This function exists to restore legacy followers for addition 
// to the new retinue.If the time comes to delete the old follower
// support, please remove this function too. Thanks, Swus.
void restore_follower_from(string file_path)
{
    restoreMonster(file_path);
}

void restore_follower()
{
    restoreMonster(FILE);
}

void set_followee(object f)
{
    followee = f;
    set = 1;
}

object get_followee()
{
    return followee;
}

int clean_up()
{
    if (!objectp(followee))
    {
        save_follower();
        return ::clean_up();
    }
    
    return 1;
}

void heart_beat()
{
    int i;
    object me = this_object();
    object my_environment = environment(me);

  	::heart_beat();

  	if (!objectp(me) || !objectp(my_environment))
    {
        return;
    }

    if (set && !objectp(followee))
    {
        tell_room(ETO,"%^BOLD%^%^GREEN%^The retainer goes about his business.");
        move("/d/shadowgate/void");
        remove();
        return;
    }

  	if (query_hp_percent() < 70 && present("vial",TO))
    {
        for(i = 0; i < 4; ++i)
        {
            command("quaff vial");
        }
	}

    if (present(followee->query_name(), my_environment) && !random(2))
    {
        ++level_up_counter;

        if (level_up_counter > 59 && query_level() < 50)
        {
            set_level(query_level() + 1);
            followee->follower_level_up(slot);
            level_up_counter = 0;
        }
    }

    ++save_counter;
    if (save_counter > 30)
    {
        if(objectp(TO) && interactive(followee))
        {
            save_counter = 0;
            save_follower();
        }
    }
}

void die(object me)
{
    int level_penalty = roll_dice(1, 3), i;
    object* my_inventory;

    me->set_level(me->query_level() - level_penalty);   // Not actually necessary, but... Good to be sure?  // Swus
    followee->apply_follower_death_penalty(slot, level_penalty);

    // Destroy every enchanted item in a follower's inventory
    my_inventory = all_inventory(me);
    for (i = 0; i < sizeof(my_inventory); ++i)
    {
        if (!objectp(my_inventory[i]))
        {
            continue;
        }
        if (!my_inventory[i])
        {
            continue;
        }
        if (objectp(my_inventory[i]))
        {
            if (my_inventory[i]->query_property("enchantment") > 0)
            {
                my_inventory[i]->drop();
                continue;
            }
        }
    }

    set_hp(10);
    save_follower();
    ::die(me);
}

string knownAs(string str)
{
    if(!objectp(followee))
    {
        return 0;
    }
    return followee->knownAs(str);
}

string realName(string str)
{
    if(!objectp(followee))
    {
        return 0;
    }
    return followee->realName(str);
}

void receive_message(string cl, string msg)
{
    ::receive_message(cl,msg);
    if (cl == "reply")
    {
        force_me("say "+msg);
    }
}

int remove()
{
    save_follower();
    return ::remove();
}

void set_slot(int follower_slot)
{
    slot = follower_slot;
}

int get_slot()
{
    return slot;
}

int is_retinue()
{
    return 1;
}
