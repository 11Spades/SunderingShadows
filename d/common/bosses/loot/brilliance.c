/*
  brilliance.c
  
  Staff weapon dropped by the Nightwalker Boss.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>

//Hit interval instead of proc chance. Procs every 3 hits.
#define HIT_INTERVAL 5

inherit "/d/common/obj/weapon/mstaff.c";

object owner;
int hit_count;

string color(string str)
{
    return CRAYON_D->color_string(str, "lightning yellow");
}

void create()
{
    ::create();
    
    set_name("brilliance");
    set_id( ({ "rod", "staff", "novelty" }) );
    set_short("brilliance, the flames of inspiration");
    set_obvious_short(color("a brilliant staff"));
    set_long("");
    set_lore("");
    set_value(100000);
    set_property("no_curse", 1);
    set_property("no steal", 1);
    set_property("lore difficulty", 40);
    set_property("id difficulty", 40);
    set_property("able to cast", 1);
    set_property("enchantment", 7);
    
    set_item_bonus("caster level bonus", 3);
    set_item_bonus("fire resistance percent", 25);
    
    set_wield( (: this_object(), "wield_func" :) );
    set_unwield( (: this_object(), "unwield_func" :) );
    set_hit( (: this_object(), "hit_func" :) );
}

void init()
{
    object holder;
    
    ::init();
    
    holder = environment(this_object());
    
    if(!holder || !userp(holder))
        return;
    
    hit_count = 0;
    
    if(!owner)
    {          
        owner = holder;
        tell_object(holder, color("As you lift the hammer, you feel its flames entwine itself with your life force."));
    }
}

int hit_func(object target)
{
    int dam;
    string ename, pname;
    
    if(!owner || !target)
        return 0;
    
    hit_count++;
    
    if(hit_count < HIT_INTERVAL)
        return 0;
    
    pname = owner->query_cap_name();
    ename = target->query_cap_name();

}

int wield_func()
{
    if(environment(this_object()) != owner)
    {
        tell_object(environment(this_object()), "The staff rejects your touch!");
        return 0;
    }
    
    tell_object(owner, color("As you wield it, the staff alights with radiant flames!"));
    tell_room(environment(owner), color(owner->query_cap_name() + "'s staff alights with radiant flames."), owner);
    return 1;
}

int unwield_func()
{
    owner && tell_object(owner, "%^CYAN%^You feel the warmth of the staff disappate as you release it.");
    return 1;
} 