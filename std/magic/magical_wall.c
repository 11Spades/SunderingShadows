//
// magical_wall.c
//
// A standardized inherit file for any and all magical
// walls. Any future magical walls should inherit this file
// in the name of standardization.
//
// For BEST utilization, simple use this file and set its
// parameters from the spell itself.
//
// -- Tlaloc -- 11.1.21
//

#include <std.h>
#include <daemons.h>

#define MAX_DUR    10000
#define DEF_DUR       50

inherit OBJECT;

int damage,        //Spell strength of wall
    difficulty,    //DC of getting past the wall
    durability;    //The health of the wall

object owner;      //The original caster

string exit,       //Which exit is it blocking
       type;       //What type of wall is it?
       
/*
  These walls will block a specific exit, much like the previous ones. However, the
  room code itself (/std/room/exits.c) will check if there is a wall blocking the
  exit before allowing the player through (try_to_pass()).
  
  If you want to add additional effects for passing the wall, simply use this as
  an inherit and use try_to_pass() in your object for customization.
  
  From the spell, you must clone this object and move it into the room. Then within
  the spell, set the descriptions, difficulty (player rolls d20 + stat), damage
  (sdamage from the spell), the owner/caster object, the stat (used to bypass/break
  the wall), and then block(exit) last.
*/

//Variable Functions
int set_difficulty(int x)   { difficulty = x; return difficulty; }
int set_durability(int x)   { durability = x; return durability; }
int set_damage(int x)       { damage = x; return damage;         }
object set_owner(object ob) { owner = ob; return owner;          }
string set_exit(string str) { exit = str; return exit;           }
string set_type(string str) { type = str; return type;           }

int query_difficulty() { return difficulty; }
int query_durability() { return durability; }
int query_damage()     { return damage;     }
object query_owner()   { return owner;      }
string query_exit()    { return exit;       }
string query_type()    { return type;       }

int add_durability(int x)
{
    durability = min( ({ MAX_DUR, durability + x }) );
    return durability;
}
//End Variable Functions

int is_invincible() { return 1; }
int is_wall()       { return 1; }

void create()
{
    ::create();
    set_name("wall");
    set_id( ({ "wall", "magical wall" }) );
    set_weight(10000);
    set_value(0);
    set_durability(DEF_DUR);
}

void init()
{
    ::init();
    add_action("end_walls", "remove");
}

int block(string exitn)
{
    string wallname;
    object room;
    
    if(!strlen(exitn))
        return 0;
    
    if(!objectp(owner))
        return 0;
    
    room = environment(this_object());
    
    if(!objectp(room))
        return 0;
    
    set_exit(exitn);
    wallname = owner->query_name() + exitn + type + "wall";
    
    if(present(wallname, room))
        return 0;
    
    add_id("wallname");
    
    if(room->set_blocked(exitn, this_object()))
        return 1;
    
    return 0;
}

//Returns 1 if they can pass, 0 if not
int can_we_pass(object who)
{
    object room, room2;
    
    if(!objectp(who))
        return 0;
    
    room = environment(who);
    
    if(!objectp(room))
        return 0;
    
    room2 = room->query_exit(exit);
    
    if(!objectp(room2))
        return 0;
    
    if(!strlen(exit))
        return 1;
    
    if(!difficulty)
        return 1;
    
    if(durability <= 0)
        return 1;
    
    return 0;    
}

int try_to_pass(object who)
{
    int roll1, dam;
    
    if(can_we_pass())
        return 1;
}

void dest_effect()
{
    environment(this_object())->remove_blocker(exit);
    
    destruct(this_object());
}

/*
    roll1 = roll_dice(1, 20);
    my_name = who->query_cap_name();
    
    if(!strlen(stat))
        stat = "strength";
    
    roll1 += BONUS_D->stat_bonus(who, stat);
    
    switch(type)
    {
        //Fire does not hard block, but burns you on the way through
        case "fire":
        if(roll1 < difficulty)
        {
            tell_object(who, "%^RED%^BOLD%^You are burned by the flames as you try to pass!%^RESET%^");
            tell_room(room, "%^RED%^BOLD%^" + my_name + " is burned by the flames as " + who->query_pronoun() + " tries to pass!", who);
            tell_room(room2, "%^RED%^BOLD%^Someone is burned by flames as they try to enter!");
            who->cause_typed_damage(who, "torso", damage, "fire");
        }
        else
        {
            tell_object(who, "%^BOLD%^You skip past the flames, unharmed.%^RESET%^");
            tell_room(room, "%^BOLD%^" + my_name + " skips past the flames, unharmed.%^RESET%^", who);
            tell_room(room2, "%^BOLD%^Someone skips past the flames, unharmed.");
        }
        return 1;
        break;
        
        default:
        if(roll1 < difficulty)
        {
            tell_object(who, "%^MAGENTA%^You try to bash through the wall, to no avail.%^RESET%^");
            tell_room(room, "%^MAGENTA%^" + my_name + " tries to bash through the wall, to no avail.%^RESET%^", who);
            tell_room(room2, "%^MAGENTA%^Someone tries to bash through the wall, to no avail.%^RESET%^");
            return 0;
        }
        
        tell_object(who, "%^MAGENTA%^BOLD%^You bash on the wall, causing noticeable damage to it.%^RESET%^");
        tell_room(room, "%^MAGENTA%^BOLD%^" + my_name + " bashes on the wall, causing noticeable damage to it.%^RESET%^", who);
        tell_room(room2, "%^MAGENTA%^BOLD%^Someone bashes on the all, causing noticeable damage to it.%^RESET%^");
        
        dam = roll1 + who->query_character_level();
        add_durability(-dam);
        
        if(durability <= 0)
        {
            tell_object(who, "%^BOLD%^You break through the wall and pass to the other side!%^RESET%^");
            tell_room(room, "%^BOLD%^" + my_name + " breaks through the wall and passes to the other side!%^RESET%^", who);
            tell_room(room2, "%^BOLD%^Someone breaks through the wall and into the area!%^RESET%^");
            blocking = 0;
            return 1;
        }
        
        return 0;
        
        break;
    }
    
    return 0;
}

*/
    
    
        
            
        
        
    
    
    
    