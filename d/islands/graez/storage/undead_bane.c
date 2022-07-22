/*
Undead Bane
*/

#include <std.h>
#include <daemons.h>

#define HIT_INTERVAL 5

inherit "/d/common/obj/weapon/two_hand_sword.c";

int counter, bonus;
object owner;

void create()
{
    ::create();
    set_name("undead bane");
    set_id( ({ "undead bane", "gleaming two handed sword", "bane", "sword", "gleaming sword"}) );
    set_short("undead bane");
    set_obvious_short("%^C254%^gle%^C247%^a%^C254%^mi%^C244%^n%^C254%^g tw%^C247%^o%^C254%^ "+
        "h%^C248%^a%^C254%^nd%^C249%^e%^C254%^d s%^C250%^w%^C254%^o%^C252%^r%^C254%^d%^CRST%^");
    set_long("This %^C247%^two handed sword%^CRST%^, forged from %^C239%^iron%^CRST%^ and "+
        "measuring over six feet from %^C060%^pommel%^CRST%^ to %^C254%^tip%^CRST%^, has "+
        "seen many battles over its life. The length of the sword is marred with %^C060%^small "+
        "nicks%^CRST%^ and the %^C068%^wrapping%^CRST%^ around the hilt is slightly %^C249%^frayed%^CRST%^. "+
        "What is astounding though is that there seems to be a constant %^C255%^soft hue%^CRST%^ from "+
        "along the blade as if blessed with some %^C193%^divine power%^CRST%^. The pommel ends in a "+
        "small %^C231%^pearl%^CRST%^.");
        set_lore("%^C066%^Crafted in the forges of Graez by the smiths there "+
        "in the days before the Silence, weapons seemed to take on a greater "+
        "power. It is unknown still why, but collectors have sought them to "+
        "determine if this was the last of Tempus' power, or the glimpse of "+
        "Cevahir aiding the defenders."+
        "\n%^RESET%^%^ORANGE%^  Father Belanos, the Weapons of Light, Second Edition%^RESET%^%^RESET%^");
    set_property("lore difficulty", 20);
    set_property("id difficulty", 20);

    // Enchantment and Bonuses
    set_property("enchantment", 4);
    set_item_bonus("attack bonus", 2);
    set_item_bonus("damage bonus", 2);


    // Wield and Unwield
    set_wield((: TO, "extra_wield" :));
    set_unwield((: TO, "extra_unwield" :));
    set_hit((: TO, "extra_hit" :));

}

int extra_wield()
{
    owner = environment(this_object());
     
    tell_object(owner, "You grip the sword and feel holy purpose fill you.");
    tell_room(environment(owner), owner->query_cap_name() + " wields the sword and nods resolutely.", owner);
    return 1;
}

int extra_unwield()
{
    
    tell_object(owner, "You set aside the sword, feeling holy purpose leave you.");
    tell_room(environment(owner), owner->query_cap_name() + " unwield the sword with a slight frown.", owner);
    return 1;
}

int extra_damage(object ob)
{
    int bonus;
    
    bonus = this_object()->query_wc() + this_object()->query_property("enchantment") + owner->query_damage_bonus();
    bonus += BONUS_D->new_damage_bonus(this_object(), owner->query_stats("strength"));
    
    return bonus;
}

int extra_hit(object target)
{
    object player, room, undeadbane, ob;
    int damage, strength;
    string playername, targetname;
    
    undeadbane = this_object();
    player = environment(undeadbane);
    room = environment(player);
    
    if(!living(player) || !living(target) || !room) return 0;
    
    counter++;
    if(counter < HIT_INTERVAL) return 0;
    counter = 0;
    
    playername = player->query_cap_name();
    targetname = target->query_cap_name();
    
    switch(random(3))
    {
        case 0:
        tell_object(player, "%^C160%^You slide to the right and find an opening for another attack!%^CRST%^");
	     tell_room(room,"%^C136%^"+ playername +"%^C136%^ takes advantage and steps forward for another%^C072%^ %^C160%^wicked attack%^C136%^!%^CRST%^",player);       
        player->execute_attack();
        break;
        case 1:
        tell_object(player, "%^BOLD%^As you strike " + targetname + "%^BOLD%^ with the sword it glows, searing " + targetname + "%^BOLD%^!");
        tell_object(target, "%^BOLD%^As the sword strikes you, it glows with a fiece holy fire!%^RESET%^");
	     tell_room(room,"%^C248%^"+ playername +"%^C248%^'s sword flashes with a %^C195%^bright light%^C248%^ as it strikes%^CRST%^ "+ targetname +"%^C248%^!%^CRST%^",player,target); 
        target->cause_typed_damage(target, "torso", extra_damage(target), "divine");
        break;
        case 2:
        tell_object(player, "%^C160%^You slash " + targetname + " %^C160%^with your sword!%^CRST%^");
        tell_object(target, "%^C160%^" + playername + "%^C160%^ slices you with their sword!%^CRST%^");
	     tell_room(room,"%^C160%^"+ playername +"%^C160%^'s sword slashes along "+ targetname +"%^C160%^'s body!%^CRST%^",player,target); 
        target->cause_typed_damage(target, "torso", extra_damage(target), "slashing");
        break;
    }
    
    return (bonus + roll_dice(3, 4));
}   
    
