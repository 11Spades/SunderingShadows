// Monolithic rebuild of the follower system 
// By Spade, June 2022

// TODO:
// Fix current race/class combos
// More classes
// Traits
// Area based dieties
// Writes and tell_objects need to be moved to message
// Influence validation needs to check for active followers

#include <std.h>

// Current class pool
#define CLASSES ({"fighter", "thief", "mage", "cleric", "monk"})

// Recruiting constants
#define RECRUIT_GENERATION_BASE_COOLDOWN 10800  // Three hours.
#define         RECRUITING_BASE_COOLDOWN 86400  // Twenty-four hours.
#define          POOL_CHECK_GRACE_PERIOD 300    // Five minutes

// Death constants
#define   DEATH_RECOVERY_TIME 10800  // Three hours.
#define RESOLVE_RECOVERY_TIME 43200  // Twelve hours.

// Our master record of who's who. Should always be kept accurate.
mapping retinue = ([  ]), last_follower_death_times = ([  ]), recruit_pool = ([  ]);
int last_recruit_time, last_recruit_generation_time, last_pool_check_time;

void clear_retinue()
{
    retinue = ([]);
}

void set_retinue_follower(int slot, string name, string title, string c, int level, string race)
{
    if (!mapp(retinue))
    {
        retinue = ([]);
    }
    
    retinue[slot] = (["name":name, "title":title, "class":c, "level":level, "race":race]);
}

mapping get_retinue_mapping()
{
    if (!mapp(retinue))
    {
        retinue = ([]);
    }
    
    return retinue;
}

mapping get_retinue_follower(int slot)
{
    if (!mapp(retinue))
    {
        retinue = ([]);
    }
    
    return retinue[slot];
}

void remove_retinue(int slot)
{
    object player = this_player();
    string retainer_directory = "/d/save/retainers/" + player->query_name() + "/";
    mixed* retainers_objects;
    int i;

    seteuid("SaveAccess");

    retainers_objects = get_dir(retainer_directory + slot + "/");

    mkdir(retainer_directory); // If the directory doesn't exist, make it.
    rm(retainer_directory + slot + ".o");
    for(i = 0; i < sizeof(retainers_objects); ++i)
    {
        rm(retainer_directory + slot + "/" + retainers_objects[i]);
    }
    rmdir(retainer_directory + slot + "/");

    if (!mapp(retinue))
    {
        retinue = ([]);
    }

    if(!mapp(last_follower_death_times))
    {
        last_follower_death_times = ([  ]);
    }
    
    map_delete(retinue, slot);
    map_delete(last_follower_death_times, slot);

    // Reorder the retinue
    for (slot = 0; slot < sizeof(retinue); ++slot)
    {
        if (!retinue[slot] && retinue[slot + 1])
        {
            retinue[slot] = retinue[slot + 1];
            map_delete(retinue, slot + 1);

            if (file_size(retainer_directory + (slot + 1) + ".ob") == -1)
            {
                continue;
            }

            rename(retainer_directory + (slot + 1) + "/", retainer_directory + slot + "/");
            rename(retainer_directory + (slot + 1) + ".ob", retainer_directory + slot + ".ob");
        }
    }

    for (slot = 0; slot < sizeof(retinue); ++slot)
    {
        if (!retinue[slot])
        {
            map_delete(retinue, slot);
        }
    }

    seteuid(getuid());
}

void init_retinue()
{
    object player = this_player(), old_follower;
    string retainer_directory = "/d/save/retainers/" + player->query_name() + "/";
    int next_slot_to_fill;
    mixed *file_names;
    
    if (!mapp(retinue))
    {
        retinue = ([]);
    }
    
    // LEGACY FOLLOWER SUPPORT
    // THIS IS BAD AND SHOULD BE REMOVED ASAP
    if (!sizeof(retinue) || !intp(keys(retinue)[0]))
    {
        clear_retinue();
        mkdir(retainer_directory); // If the directory doesn't exist, make it.
        file_names = get_dir(retainer_directory);
        next_slot_to_fill = 0;
        foreach (string name in file_names)
        {
            if ( !regexp(name, "[0-9]|\.o$"))
            {
                rename(retainer_directory + name + "/", retainer_directory + (string)next_slot_to_fill + "_temp" + "/");
                rename(retainer_directory + name + ".o", retainer_directory + (string)next_slot_to_fill + ".o");
                old_follower = new("/cmds/mortal/followers/fighter.c");
                old_follower->restore_follower_from(retainer_directory + next_slot_to_fill);
                set_retinue_follower(next_slot_to_fill, old_follower->query_name(), replace_string(old_follower->query_short(), old_follower->query_name(), "$N"), old_follower->query_class(), min( ({ old_follower->query_level(), 50 }) ), old_follower->query_race());
                ++next_slot_to_fill;
            }
        }
        
        file_names = get_dir(retainer_directory);
        foreach (string name in file_names)
        {
            if (regexp(name, "_temp$"))
            {
                rename(retainer_directory + name + "/", retainer_directory + replace_string(name, "_temp", "") + "/");
                ++next_slot_to_fill;
            }
        }
    }

    // Retinue validation
    for (next_slot_to_fill = 0; next_slot_to_fill < sizeof(next_slot_to_fill); ++next_slot_to_fill)
    {
        if (!retinue[next_slot_to_fill]["name"])
        {
            retinue[next_slot_to_fill]["name"] = "daemon/names"->getName();
        }

        if (member_array(retinue[next_slot_to_fill]["class"], CLASSES) == -1)
        {
            retinue[next_slot_to_fill]["class"] = CLASSES[random(sizeof(CLASSES))];
        }

        if (!retinue[next_slot_to_fill]["race"])
        {
            retinue[next_slot_to_fill]["race"] = "human";
        }

        if (!retinue[next_slot_to_fill]["level"])
        {
            retinue[next_slot_to_fill]["level"] = 25;
        }
    }
}

void generate_recruit_pool(int force_flag)
{
    string race, tobe;
    object player = this_player();
    int i, j, level, influence = player->query_skill("influence");

    string *city_recruitable_races = ({"human", "elf", "dwarf", "gnome", "half-elf", "half-orc", "saurian"});
    // string *city_recruitable_classes = ({"fighter", "thief", "mage", "cleric", "monk"}); // TODO (Spade)
    string *wild_recruitable_races = ({"beastkin", "centaur", "saurian", "voadkyn", "wemic", "firbolg", "gnome", "kitsune", "satyr"});
    // string *wild_recruitable_classes = ({"fighter", "thief", "mage", "cleric", "monk"}); // TODO (Spade)
    string *beast_recruitable_races = ({"goblin", "orc", "half-orc", "bugbear", "drow", "gnoll", "half-drow", "hobgoblin", "kobold", "ogre", "troll", "yuan-ti", "half-ogre", "ogre-mage"});
    // string *beast_recruitable_classes = ({"fighter", "thief", "mage", "cleric", "monk"}); // TODO (Spade)

    if (!mapp(recruit_pool))
    {
        recruit_pool = ([0: ([]), 1: ([]), 2: ([])]);
    }

    if (!force_flag && (time() < last_recruit_generation_time + RECRUIT_GENERATION_BASE_COOLDOWN - influence * 10 || time() < last_pool_check_time + POOL_CHECK_GRACE_PERIOD && last_recruit_generation_time))
    {
        return;
    }

    recruit_pool = ([0: ([]), 1: ([]), 2: ([])]);

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < (3 + influence / 20); ++j)
        {
            tobe = CLASSES[random(sizeof(CLASSES))];
            level = influence / 2 + random(influence / 2);
            switch(i)
            {
            case 0:
                race = city_recruitable_races[random(sizeof(city_recruitable_races))];
                race = validate_follower_race_class(tobe, race);

                recruit_pool[i][j] = (["name": "daemon/names"->getName(), "title": "$N, a bold retainer for " + player->query_cap_name(), "class": tobe, "level": min(({ level, 50 })), "race": race]);
                break;
            
            case 1:
                race = wild_recruitable_races[random(sizeof(wild_recruitable_races))];

                race = validate_follower_race_class(tobe, race);

                recruit_pool[i][j] = (["name": "daemon/names"->getName(), "title": "$N, a bold retainer for " + player->query_cap_name(), "class": tobe, "level": min(({ level, 50 })), "race": race]);
                break;
            
            case 2:
                race = beast_recruitable_races[random(sizeof(beast_recruitable_races))];

                race = validate_follower_race_class(tobe, race);

                recruit_pool[i][j] = (["name": "daemon/names"->getName(), "title": "$N, a bold retainer for " + player->query_cap_name(), "class": tobe, "level": min(({ level, 50 })), "race": race]);
                break;
            }
        }
    }

    last_recruit_generation_time = time();
}

mapping get_recruit_pool()
{
    if (!mapp(recruit_pool))
    {
        recruit_pool = ([0: ([]), 1: ([]), 2: ([])]);
    }

    return recruit_pool;
}

void viewed_recruits()
{
    if (!mapp(recruit_pool))
    {
        recruit_pool = ([0: ([]), 1: ([]), 2: ([])]);
    }

    last_pool_check_time = time();
}

void start_recruiting_cooldown()
{
    last_recruit_time = time();
}

int can_recruit()
{
    return last_recruit_time + RECRUITING_BASE_COOLDOWN - this_player()->query_skill("influence") * 100 < time();
}

int check_follower_status(int slot)
{
    if (!mapp(last_follower_death_times))
    {
        last_follower_death_times = ({});
        return 0;
    }

    if(!last_follower_death_times[slot])
    {
        return 0;
    }

    if (last_follower_death_times[slot] + DEATH_RECOVERY_TIME - time() > 0)
    {
        return last_follower_death_times[slot] + last_follower_death_times[slot] + DEATH_RECOVERY_TIME - time() > 0 - time();
    }

    map_delete(last_follower_death_times, slot);
    return 0;
}

void apply_follower_death_penalty(int slot, int severity)
{
    if (!mapp(last_follower_death_times))
    {
        last_follower_death_times = ([]);
    }

    // Because I'm scared that the universe will survive long enough for time() to roll over or something?  // Spade
    if (!last_follower_death_times[slot])
    {
        last_follower_death_times[slot] = time();
    }
    else if (last_follower_death_times[slot] + RESOLVE_RECOVERY_TIME > time())
    {
        write("%^C051%^" + retinue[slot]["name"] + "%^C030%^ has met final death.");
        // TODO: This should lock recruiting for a time.    // Spade
        remove_retinue(slot);
        return;
    }
    else
    {
        last_follower_death_times[slot] = time();
    }

    retinue[slot]["level"] -= severity;

    return;
}

void follower_level_up(int slot)
{
    if (!mapp(retinue))
    {
        retinue = ([]);
    }

    if (!retinue(slot))
        return;

    ++retinue[slot]["level"];

    return;
}

string validate_follower_race_class(string tobe, string race)
{
    switch(tobe)
    {
    case "fighter":
        if (race == "satyr")
        {
            return "elf";
        }
        return race;
        break;
    
    case "cleric":
        if (race == "ogre")
        {
            return "ogre-mage";
        }
        if (race == "voadkyn")
        {
            return "elf";
        }
        return race;
        break;

    case "mage":
        if (race == "dwarf" || race == "halfling")
        {
            return "gnome";
        }
        if (race == "ogre" || race == "hobgoblin")
        {
            return "ogre-mage";
        }
        if (race == "firbolg" || race == "beastkin" || race == "centaur" || race == "voadkyn" || race == "satyr")
        {
            return "elf";
        }
        if (race == "wemic" || race == "half-orc")
        {
            return "human";
        }
        if (race == "goblin" || race == "orc" || race == "ogre" || race == "bugbear" || race == "gnoll" || race == "troll")
        {
            return "kobold";
        }
        return race;
        break;
    
    case "thief":
        if (race == "ogre")
        {
            return "goblin";
        }
        if (race == "centaur" || race == "firbolg")
        {
            return "elf";
        }
        if (race == "wemic")
        {
            return "human";
        }
        return race;
        break;
    
    case "monk":
        if (race == "centaur" || race == "voadkyn" || race == "firbolg" || race == "satyr")
        {
            return "elf";
        }
        if (race == "wemic" || race == "saurian")
        {
            return "human";
        }
        return race;
        break;
    
    default:
        return race;
    }
}

void validate_retinue_influence()
{
    int my_influence = this_player()->query_skill("influence");

    if (my_influence / 5 - 1 < sizeof(retinue) && !random(10))
    {
        remove_retinue(random(sizeof(retinue)));
    }
}

int swap_follower_slots(int key_one, int key_two)
{
    string retainer_directory = "/d/save/retainers/" + this_player()->query_name() + "/";
    mapping temp_mapping;

    seteuid("SaveAccess");

    if (retinue[key_one] && retinue[key_two])
    {
        temp_mapping = retinue[key_two];
        retinue[key_two] = retinue[key_one];
        retinue[key_one] = temp_mapping;

        // Ensure the folders exist
        mkdir(retainer_directory);
        mkdir(retainer_directory + key_one);
        mkdir(retainer_directory + key_two);
        
        // Ensure the files exist
        if (file_size(retainer_directory + key_one + ".o") == -1)
        {
            if (!write_file(retainer_directory + key_one + ".o", "", 0))
            {
                write("%^C030%^Something is wrong and the swap cannot be completed.");
                seteuid(getuid());
                return -1;
            }
        }

        if (file_size(retainer_directory + key_two + ".o") == -1)
        {
            if (!write_file(retainer_directory + key_two + ".o", "", 0))
            {
                write("%^C030%^Something is wrong and the swap cannot be completed.");
                seteuid(getuid());
                return -1;
            }
        }

        // Swap folders
        rename(retainer_directory + key_one + "/", retainer_directory + key_two + "_temp/");
        rename(retainer_directory + key_two + "/", retainer_directory + key_one + "/");
        rename(retainer_directory + key_two + "_temp/", retainer_directory + key_two + "/");

        seteuid(getuid());
        return 1;
    }

    seteuid(getuid());
    return 0;
}
