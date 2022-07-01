#include <std.h>
#include "../graez.h"

inherit WEAPONLESS;

create() 
{
    int level;
    ::create();
    set_name("dire wolf");
    set_id(({"wolf", "dire wolf","vicious dire wolf"}));
    set_short("%^C059%^vi%^C242%^c%^C059%^io%^C247%^u%^C059%^s dir%^C245%^e%^C059%^ "+
        "w%^C244%^o%^C248%^l%^C059%^f%^CRST%^");
    set_long("%^CRST%^Standing near the size of a %^C060%^war horse%^CRST%^, "+
        "this %^C240%^dire wolf%^CRST%^ is an apex %^C124%^predator%^CRST%^ in "+
        "whatever %^C064%^forest%^CRST%^ it is hunting in. Its %^C243%^dark "+
        "fur%^CRST%^ is thick enough to block most blows and its size and "+
        "strength ensure that anything smaller than it is usually dead well "+
        "before it can be struck. %^C060%^Claws%^CRST%^, %^C058%^jaw%^CRST%^, "+
        "%^C255%^teeth%^CRST%^, each are vicious replicas of a normal "+
        "%^C060%^wolf%^CRST%^, just at a massive scale.\n");
    set_race("dire wolf");
    set_body_type("quadruped");
    set_class("fighter");
    set_mlevel("fighter",20);
    set_hd(15,8);
    set_hp(400);
    set_level(20);
    set_exp(5000);
    set_new_exp(25,"normal");
    set_alignment(9);
    set_size(2);
    set_stats("strength", 18);
    set_funcs(({"bite"}));
    set_func_chance(20);
    set("aggressive", 20);
    set_moving(1);
    set_speed(40);
}
    
void bite(object targ) 
{    
    if (random(40) > targ->query_stats("dexterity"))
    {
      
        tell_object(targ,"%^BOLD%^%^RED%^The Dire Wolf lunges at you, jaws wide open!\n"
            "%^BOLD%^%^RED%^His bite lands and tears into your flesh!");
        tell_room(ETO,"%^BOLD%^%^RED%^The Dire Wolf lunges at "+targ->QCN+" "
            "sinking its teeth into "+targ->QS+"!",targ);
        targ->cause_typed_damage(targ, targ->return_target_limb(),roll_dice(3,6),"piercing");
        return;
    } 

    tell_object(targ,"%^RED%^The Dire Wolf tears at your limbs keeping you pinned "
        "to the ground!%^RESET%^");
    tell_room(ETO,"%^BOLD%^%^RED%^The Dire Wolf lunges at "+targ->QCN+" "
        ",pinning "+targ->QO+" to the ground!",targ);    
    targ->set_paralyzed(roll_dice(3,6),"%^GREEN%^You struggle to free yourself "
        "from the Dire Wolf's deadly grasp!");
        targ->cause_typed_damage(targ, targ->return_target_limb(),roll_dice(6,6),"piercing");
    return;
}