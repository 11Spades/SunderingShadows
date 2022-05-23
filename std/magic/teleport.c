/**
 * @file
 * @brief Teleport functions and checks. You can either include it or use as a "daemon" object.
 * Note that stric types are enabled for this object
 */

#pragma types

#include <std.h>
#include <daemons.h>

#pragma strict_types

mapping diminished_teleports = ([  ]);

/**
 * Checks whether object can be teleported, checking against environment and randomness.
 *
 * To disable rolls use noroll options.
 */
varargs int object_can_be_teleported(object teleportee, object destination, int clevel, int noroll)
{
    int roll;

    if (!(teleportee && destination && clevel)) {
        return 0;
    }
    
    if(catch(call_other(destination, "???")))
    {
        tell_object(teleportee, "Destination error.");
        return 0;
    }

    if (!objectp(destination)) {
        return 0;
    }
    if (!destination->is_room()) {
        return 0;
    }
    /*
    if (destination->is_flight_room()) {
        return 0;
    }
    */

    if (destination->query_property("no teleport") ||
        environment(teleportee)->query_property("no teleport")) {
        return 0;
    }
    
    if(FEATS_D->usable_feat(teleportee, "worldly traveler"))
        clevel += 2;
    
    if((int)teleportee->query_property("judgement_piercing"))
        clevel += (int)teleportee->query_property("judgement_piercing");
    
    if(is_diminish_teleport(teleportee->query_name(), destination) || is_diminish_teleport(teleportee->query_name(), environment(teleportee)))
        clevel -= 10;

    if (!noroll) {
        roll = roll_dice(1, 20);

        if (roll == 1) {
            return 0;
        }

        if (roll == 20) {
            return 1;
        }

        if (teleportee->query_property("teleport proof") && (teleportee->query_property("teleport proof") - 9 + random(20) > clevel)) {
            return 0;
        }

        {
            int startpower, endpower;
            startpower = environment(teleportee)->query_property("teleport proof");
            endpower = destination->query_property("teleport proof");
            if(startpower && (clevel - 9 + random(20) < startpower))
            {
                add_diminish_teleport(teleportee->query_name(), environment(teleportee));
                return 0;
            }
            if(endpower && (clevel - 9 + random(20) < endpower))
            {
                add_diminish_teleport(teleportee->query_name(), destination);
                return 0;
            }
            /*
            if ((startpower && (clevel - 9 + random(20) < startpower)) ||
                (endpower && (clevel - 9 + random(20) < endpower))) {
                add_diminish_teleport(teleportee->query_name(), destination);
                return 0;
            }
            */
        }
    }

    return 1;
}

int is_diminish_teleport(string person, object destination)
{
    if(!stringp(person) || !objectp(destination) || !find_player(person))
        return 0;
    
    if(member_array(person, keys(diminished_teleports)) < 0)
        return 0;
    
    if(!pointerp(diminished_teleports[person]))
        return 0;
    
    if(member_array(destination, diminished_teleports[person]) < 0)
        return 0;

    return 1;
}
    
int add_diminish_teleport(string person, object destination)
{
    if(!stringp(person) || !objectp(destination))
        return 0;
    
    if(!find_player(person))
        return 0;

    if(is_diminish_teleport(person, destination))
    {
        remove_call_out("shed_diminish_return");
        call_out("shed_diminish_return", 1800, person, destination);
        return 1;
    }

    if(member_array(person, keys(diminished_teleports)) < 0)
        diminished_teleports += ([ person : ({ destination }) ]);
    else
        diminished_teleports[person] += ({ destination });

    call_out("shed_diminish_return", 1800, person, destination);

    return 1;
}
    
int shed_diminish_return(string person, object destination)
{
    if(!stringp(person) || !objectp(destination))
        return 0;

    if(!is_diminish_teleport(person, destination))
        return 0;

    diminished_teleports[person] -= ({ destination });

    if(!sizeof(diminished_teleports[person]))
        map_delete(diminished_teleports, person);

    return 1;
}

/**
 * Looks for rooms in the same directory.
 */
object scatter_destination(mixed destination)
{
    string fname;
    string* files;
    object destobj;
    object tmp;

    fname = base_name(destination);

    files = dir_listing(fname);

    foreach(tmp in files)
    {
        if (catch(destobj = find_object_or_load(tmp))) {
            files -= ({ tmp });
        }

        if (!destobj->is_room()) {
            files -= ({ tmp });
        }
    }

    destobj = find_object_or_load(files[random(sizeof(files))]);

    return destobj;
}

/**
 * Performs teleportation and is bare minimum needed to teleport a player.
 */
mixed teleport_object(object invoker, mixed teleportee, mixed destination, int clevel)
{
    object tped, destroom;

    if (stringp(teleportee)) {
        tped = present(teleportee, invoker);
        if (!objectp(tped)) {
            write(teleportee + " can't be found");
            return 0;
        }
    } else if (objectp(teleportee)) {
        tped = teleportee;
    } else {
        return 0;
    }

    if (stringp(destination)) {
        if (!(destroom = invoker->query_rem_room(destination))) {
            tell_object(invoker, "You can't remember " + destination);
            return 0;
        }
    } else if (objectp(destination)) {
        destroom = destination;
    } else {
        return 0;
    }

    if (!object_can_be_teleported(tped, destroom, clevel, 1)) {
        return 0;
    }

    destroom->set_property("recent teleport", ENV(tped));
    ENV(tped)->set_property("recent teleport", destroom);

    tped->move_player(destroom);

    return destroom;
}

string* dir_listing(string tempfil)
{
    string* tmpstor, path;
    tmpstor = explode(tempfil, "/");

    path = "/" +
           implode(tmpstor - ({ tmpstor[sizeof(tmpstor) - 1] }), "/")
           + "/";

    tmpstor = map_array(get_dir(path + "*.c"), (: $2 + $1:), path);

    return tmpstor;
}
