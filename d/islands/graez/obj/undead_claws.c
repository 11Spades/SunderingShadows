/*
Jagged Undead Claws
*/

#include <std.h>
#include <daemons.h>
#include "../graez.h"

#define HIT_INTERVAL 5

inherit "/d/common/obj/weapon/claw.c";

int counter,bonus;
object owner;

void create()
{
    ::create();
    set_name("jagged undead claws");
    set_id( ({ "jagged undead claws", "undead claws", "claws"}) );
    set_short("%^C245%^j%^C059%^a%^C245%^gg%^C059%^e%^C245%^d %^C172%^undead %^C245%^claws%^CRST%^");
    set_obvious_short("%^C245%^jagged %^C172%^undead %^C245%^claws%^CRST%^");
    set_long("These claws are actually just a set of %^C222%^brass "+
        "knuckles%^CRST%^ where someone has taken %^C247%^claws%^CRST%^ "+
        "and %^C151%^talons%^CRST%^ from different %^C054%^undead "+
        "creatures%^CRST%^ and attached them with %^C245%^metal thread%^CRST%^. "+
        "The visual impact is jarring and while it is obviously homemade, "+
        "it is secure enough that %^C088%^terrible wounds%^CRST%^ could be "+
        "struck with the %^C245%^claws%^CRST%^.\n");
    set_lore("%^C144%^If I see one more patrol come back "+
        "with 'trophies' from the field I will personally "+
        "burn down every still, confiscate every dice, and force "+
        "all you dock rats to triple duty. We are here to save "+
        "this gods' damned island, not decorate the barracks with "+
        "trinkets we ripped off of undead!"+
        "\n%^C067%^  Commander Ashton, General Orders Summerstime 760%^CRST%^\n");
    set_property("lore difficulty", 20);
    set_property("id difficulty", 20);

    // Enchantment and Bonuses
    set_property("enchantment", 5);
    set_item_bonus("attack bonus", 3);



    // Wield and Unwield
    set_wield((: TO, "extra_wield" :));
    set_unwield((: TO, "extra_unwield" :));
    set_hit((: TO, "extra_hit" :));

}

int extra_wield()
{
   object room,player;
   string playername;
   
   player = environment(this_object());    
   room = environment(this_player());
   playername = player->query_cap_name();
   
     
    tell_object(player, "%^C137%^You slide your hand into the %^C240%^knuckles%^C137%^, careful to not touch the claws themselves.%^CRST%^");
    tell_room(room, ""+ playername +" %^C137%^wields the %^C088%^vicious %^C137%^looking %^C240%^claws%^C137%^.%^CRST%^", player);
	
    return 1;
}

int extra_unwield()
{
   object room,player;
   string playername;
   
   player = environment(this_object());    
   room = environment(this_player());
   playername = player->query_cap_name();
   
    tell_object(player, "%^C143%^You remove the %^C243%^claws%^C143%^, stretching your fingers.%^CRST%^");
    tell_room(room, "%^C143%^"+ playername +" %^C143%^unwields the %^C088%^vicious %^C143%^looking %^C243%^claws%^C143%^.%^CRST%^", player);
    return 1;
}

int extra_damage(object ob)
{
    int bonus;
    
    if(!objectp(owner))
        return 0;
    
    bonus = this_object()->query_wc() + this_object()->query_property("enchantment") + owner->query_damage_bonus();
    bonus += BONUS_D->new_damage_bonus(this_object(), owner->query_stats("strength"));
    
    return bonus;
}

int extra_hit(object target)
{
    object player, room, sapper, ob;
    int damage, strength;
    string playername, targetname;
    
    sapper = this_object();
    player = environment(sapper);
    room = environment(player);
    
    if(!living(player) || !living(target) || !room) return 0;
    
    counter++;
    if(counter < HIT_INTERVAL) return 0;

    
    playername = player->query_cap_name();
    targetname = target->query_cap_name();
    strength = sapper->query_property("enchantment");
	
    switch(random(3))
    {
        case 0:
        tell_object(player, "%^C137%^You shove your attacker's blow aside and attack again!%^CRST%^");
		counter = 0;
        player->execute_attack();
        break;
        case 1:
        tell_object(player, "%^C160%^You rake the talons across%^CRST%^ " + targetname + "%^C160%^'s body, leaving a %^C245%^wicked %^C160%^wound!%^CRST%^");
        tell_object(targetname, "%^C160%^Your blood boils as the %^C242%^claws %^C160%^rip into your flesh%^CRST%^");
        target->set_property("rend", 2);
		counter = 0;
        break;
        case 2:
        tell_object(player, "%^C146%^With a fierce growl you shove both claws deep into " + targetname + "%^C146%^'s body, the claws' energy seeping into them!%^CRST%^");
        tell_object(target, "%^C072%^As%^CRST%^ "+playername+" %^C072%^attacks they implant their claws deep into your body!%^CRST%^");
        target->cause_typed_damage(target, "torso", extra_damage(target), "negative energy");
		counter = 0;
        break;

    }
    
    return (bonus + roll_dice(3, 4));
}   
    
