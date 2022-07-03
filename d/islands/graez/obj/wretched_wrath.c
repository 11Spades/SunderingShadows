/*
Wretched Wrath = LoKi - 2022
*/

#include <std.h>
#include <daemons.h>

#define HIT_INTERVAL 5

inherit "/d/common/obj/weapon/large_battle_axe.c";

int counter, bonus;
object owner;

void create()
{
    ::create();
    set_name("wretched wrath");
    set_id( ({ "wretched wrath", "axe", "ebon handled iron battle axe", "battle axe", "iron battle axe"}) );
    set_short("%^C244%^wr%^C061%^e%^C244%^tc%^C056%^h%^C244%^ed w%^C061%^r%^C244%^a%^C056%^t%^C244%^h%^CRST%^");
    set_obvious_short("ebon handled iron battle axe");
    set_long("The %^C060%^handle%^CRST%^ of this %^C241%^battle axe%^CRST%^ is four feet long and formed from %^C240%^ebon wood%^CRST%^. At the very bottom of the handle is a %^C231%^small human skull%^CRST%^ that has been fused to the handle with %^C124%^heat %^CRST%^and %^C056%^magic%^CRST%^, %^C059%^melting %^CRST%^it in such a way that it is almost unrecognizable. The %^C245%^axe blade%^CRST%^ itself is made from %^C239%^iron %^CRST%^and is viciously sharp.");
    set_lore("%^C144%^I've seen the death knight from "+
	"a distance. That axe! I will have nightmares of "+
	"that axe till my final days! I don't have the men "+
	"to face that creature and privately I do not know "+
	"how we can prevail unless I take the field.%^CRST%^"+
        "\n%^C067%^  Commander Ashton, Personal Ledger - Summerstime 759%^CRST%^\n");
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
     
    tell_object(owner, "%^C243%^Shadows gather around your hands "+
	"as you tighten the grip on the battle axe.%^CRST%^");
    tell_room(environment(owner), owner->query_cap_name() + " %^C243%^wields the axe, and shadows seep from it.%^CRST%^", owner);
    return 1;
}

int extra_unwield()
{
    
    tell_object(owner, "%^C243%^The shadows retreat from you as you set aside the axe.%^CRST%^");
    tell_room(environment(owner), owner->query_cap_name() + "%^C243%^ unwields the axe and shadows disapate.%^CRST%^", owner);
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
    object player, room, thisweapon, ob;
    int damage, strength;
    string playername, targetname;
    
    thisweapon = this_object();
    player = environment(thisweapon);
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
        tell_object(player, "%^C124%^You leap forward and use the momentum of your backswing to strike again!%^CRST%^");
	     tell_room(room,"%^C124%^"+ playername +"%^C124%^ leaps foward and manages another attack!%^CRST%^",player);       
        player->execute_attack();
        break;
        case 1:
        tell_object(player, "%^C240%^You leap and swing the axe down on " + targetname + "%^C240%^'s body!%^RESET%^");
        tell_object(target, "%^C240%^"+ playername +" jumps and with a mighty swing buries the axe deep into you!%^RESET%^");
	     tell_room(room,"%^C240%^"+ playername +"%^C240%^buries their axe deep into "+ targetname +"%^C240%^!%^CRST%^",player,target); 
        target->cause_typed_damage(target, "torso", extra_damage(target), "slashing");
        break;
        case 2:
        tell_object(target, "%^C239%^" + playername + "%^C239%^ holds up their axe and shadows leap out from it to envelop you!%^CRST%^");
        tell_object(player, "%^C239%^Shadows leap from the axe and entwine" + targetname + "%^C239%^!");
	     tell_room(room,"%^C239%^"+ playername +"%^C239%^'s axe bleeds shadows that leap out to envelop "+ targetname +"%^C239%^!%^CRST%^",player,target); 
        target->cause_typed_damage(target, "head", extra_damage(target), "negative energy");
        break;
    }
    
    return (bonus + roll_dice(3, 4));
}   