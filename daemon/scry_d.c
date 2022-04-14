/*
  New scrying system handler.
  
  -- Tlaloc --
*/

#include <std.h>
#include <security.h>

/*
  New scrying system handler.
  
  -- Tlaloc --
*/

//This is a spot scry check
int scry_check(object target, object scryer, int power)
{
    object room;
    int block_power, room_block, detect_power, result;
    
    if(!objectp(target) || !objectp(scryer) || !power)
        return 0;
    
    room = environment(target);
    
    if(!objectp(room))
        return 0;
    
    if(room->query_property("no scry"))
        return 0;
    
    if(target->query_property("block scrying"))
        return 0;
    
    detect_power = target->query_property("scry detect power");
    room_block = room->query_property("scry proof");    
    block_power = target->query_property("scry block power");    
    block_power = max( ({ room_block, block_power }) );
   
    //Reverse check for detection
    result = (detect_power + roll_dice(1, 20)) - (power + 10);
    if(result >= 0)
    {
        if(target->query_property("false vision"))
        {
            tell_object(scryer,"%^BOLD%^%^MAGENTA%^Suddenly, horrific images of your worst fears appear before your eyes, and you can't help but to stagger away in fright, losing your concentration!");
            scryer->cause_typed_damage(scryer, "head", roll_dice(power, 6), "mental");
            return 0;
        }
        tell_object(target,"%^BOLD%^MAGENTA%^You detect someone scrying you!%^RESET%^");
        if(result >= 5)
        {
            tell_object(target,"%^BOLD%^YELLOW%^You get an image of where they are!%^RESET%^");
            long_look_room(scryer, target);
        }   
    }
        
    if(block_power + 10 > power + roll_dice(1, 20))
        return 0;
    
    return 1;
}

void long_look_room(object victim, object detector)
{
    string file, desc;
    object *inv, dest;
    int i,j;
    
    if(!objectp(victim))
        return;
    
    dest = environment(victim);
    
    if(!dest || !objectp(dest))
        return;
    
    if(!detector || !objectp(detector))
        return;
    
    message("room_description","\n%^YELLOW%^[S] %^RESET%^"+(string)dest->query_short()+"\n", detector);
    message("room_description","\n%^YELLOW%^[S] %^RESET%^"+(string)dest->query_long()+"\n", detector);
    inv = all_inventory(dest);

    foreach(object ob in inv)
    {
        if(!objectp(ob)) continue;
        if(ob->query_invis()) continue;
        if(ob->is_detectable()) continue;
        tell_object(detector, "%^WHITE%^BOLD%^[S] %^RED%^"+inv[i]->query_short());
    }
    return;
}