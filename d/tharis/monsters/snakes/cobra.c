//copperhead.c

#include <std.h>

inherit WEAPONLESS;

void create(){
	::create();
	set_name("cobra");
	set_id(({"cobra","Cobra","snake"}));
	set_short("A Cobra");
	set_long(
@OLI
	This snake is a long slightly hooded creature. It has long
fangs protruding from its mouth. Small in size you are sure it 
can still hurt you.
OLI
	);
	set_hd(2,1);
	set_hp(16);
	set_body_type("snake");
	set_damage(1,3);
	set_attacks_num(1);
	set_attack_limbs(({"fangs"}));
	set_hit_funcs((["fangs":(:TO,"poison":)]));
	set_nat_weapon_type("piercing");
	set_gender("male");
	set_race("snake");
	set_exp(200);
	set_alignment(5);
	set_overall_ac(6);
}

int poison(object targ){
	tell_object(targ,"%^BOLD%^%^RED%^The bite of this snake sends fear through you body!\n");
	if("daemon/saving_d"->saving_throw(targ, "paralyzation_poison_death",2))
		return 0;
	
	tell_player(targ,"%^BOLD%^%^RED%^You feel the horrid poison filter into your blood. Death is at hand!");
	targ->add_poisoning(5);
	return 10;
}
