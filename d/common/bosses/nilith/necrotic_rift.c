/*
  necrotic_rift.c
  
  Used by the Nightwalker boss.
  Increases its strength and causes damage to those nearby.
  
  -- Tlaloc --
*/

#include <std.h>

inherit OBJECT;

int destroyed;

void create()
{
    ::create();
    set_name("rift");
    set_id( ({ "necrotic rift", "rift" }) );
    set_short("%^C074%^rift%^C062%^ of n%^C068%^e%^C074%^c%^C080%^r%^C086%^o%^C080%^t%^C074%^i%^C062%^c e%^C068%^n%^C074%^e%^C080%^r%^C068%^g%^C062%^y%^CRST%^");
    set_long("This appears to be a rift in reality, leading, most likely, to the Plane of Shadows. It pulses and warps with dark necrotic energy. You should probably 'mend rift' before it gets out of hand!");
    set_weight(10000);
    set_property("not living", 1);
    set("value", 0);
    set_heart_beat(3);
}

void init()
{
    ::init();
    add_action("mend_fun", "mend");
}

void heart_beat()
{
    object *targets;
    object room;
    
    room = environment(this_object());
    
    targets = all_living(room);
    targets = filter_array(targets, (: !$1->is_undead() :));
    
    tell_room(room, "%^C057%^The %^C245%^r%^C247%^i%^C249%^f%^C245%^t%^C057%^ p%^C063%^u%^C069%^l%^C075%^s%^C081%^e%^C057%^s with d%^C063%^a%^C069%^r%^C057%^k, d%^C063%^e%^C069%^s%^C075%^t%^C081%^r%^C087%^u%^C081%^c%^C075%^t%^C069%^i%^C063%^v%^C057%^e e%^C063%^n%^C069%^e%^C075%^rg%^C081%^i%^C075%^e%^C057%^s!%^CRST%^");
    
    foreach(object ob in targets)
        ob->cause_typed_damage(ob, "body", 50, "void");
}    
    

int mend_fun(string str)
{
    if(!str || !strlen(str) || str != "rift")
        return 0;
    
    if(this_player()->query_paralyzed())
    {
        tell_object(this_player(), "You can't do that while paralyzed.");
        return 1;
    }
    
    if(destroyed)
    {
        tell_object(this_player(), "%^BOLD%^Someone is already mending that rift!%^RESET%^");
        return 1;
    }
    
    destroyed = 1;
    
    tell_object(this_player(), "%^WHITE%^BOLD%^As you mend the rift, you feel a shock of void energy, stunning you!%^RESET%^");
    this_player()->cause_typed_damage(this_player(), "body", 100, "void");
    this_player()->set_paralyzed(6, "%^YELLOW%^You're still recovering from the rift's shock!%^RESET%^");
    
    remove();
    return 1;
}

void remove()
{
    tell_room(environment(this_object()), "%^C074%^The rift twists and caves into itself, disappearing....%^CRST%^");
    return ::remove();
}
    
    
    
