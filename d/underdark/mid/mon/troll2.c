#include <std.h>
#include "../../defs.h"
inherit WEAPONLESS;

void create() {
    ::create();
    set_id(({"troll","ugly troll","troll leader"}));
    set_name("troll");
    set_short("%^RESET%^%^GREEN%^large and ugly troll%^RESET%^");
    set_long("%^RESET%^The ugly brute standing before you has long and ungainly limbs, and while its frame "
"seems initially frail and thin, its movements betray a surprising strength. Its rubbery hide is a sickly hue "
"somewhere between %^GREEN%^swampy green %^RESET%^and %^BOLD%^%^BLACK%^dull gray%^RESET%^, and a tuft of "
"%^BOLD%^%^BLACK%^blackened hair %^RESET%^sprouts from the top of its head. Each of its long fingers ends in a "
"%^BOLD%^%^WHITE%^sharpened claw%^RESET%^, which it clicks together as it peers about with dull, sunken eyes. "
"It is hunched over and moves with an uneven gait, but you suspect it is much more %^CYAN%^agile %^RESET%^than "
"first appearances would suggest.");
    set_race("troll");
    set_body_type("humanoid");
    if (random(2)) set_gender("male");
    else set_gender("female");
    set_alignment(9);
    set_nogo(({MID+"tunnel09","/d/dagger/kinaro/mines/lower2q"}));
    set_speed(40);
    set_moving(1);
    set_class("fighter");
    set_hd(28,8);
    set_guild_level("fighter",28);
    set_mlevel("fighter",28);
    set_max_hp(300);
    set_hp(300);
    set_property("swarm",1);
    set_stats("strength",14);
    set_exp(2000);
    set_overall_ac(-6);
    set("aggressive",25);
    set_attack_limbs(({"left hand","right hand"}));
    set_attacks_num(2);
    set_nat_weapon_type("slashing");
    set_damage(2,4);
}

void heart_beat()
{
    int myhp;
    ::heart_beat();
    if(!objectp(TO)) { return; }
    if ((int)TO->query_hp() < (int)TO->query_max_hp()) {
      tell_room(ETO,"%^GREEN%^The troll's injuries start to heal as it regenerates from the damage!%^RESET%^");
      myhp = (int)TO->query_max_hp() - (int)TO->query_hp();
      if(myhp < 20) { TO->add_hp(myhp); }
      else { TO->add_hp(20); }
    }
}
