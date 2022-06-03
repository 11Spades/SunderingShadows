#include <std.h>
#include <magic.h>
#include <daemons.h>
#include "../serakii.h"
// Echo is mostly physical immune 

inherit MONSTER;

int powerlevel, counter, buffed, psize;

void create(){
    object ob;
    
    ::create();
    set_name("echo");
    set_id(({"echo","construct","half-build construct", "legs"}));
    set_short("%^C160%^E%^C196%^c%^C160%^h%^C088%^o%^C160%^, %^C196%^l%^C160%^egs "+
        "o%^C196%^f%^C160%^ a c%^C088%^o%^C160%^nstru%^C197%^c%^C160%^t%^CRST%^");
    set_long("This half built construct is a %^C196%^mad creation%^CRST%^. "+
        "It stands on %^C160%^two legs%^CRST%^ as if it was simply the lower "+
        "half of a %^C195%^humanoid%^CRST%^. Instead of a torso, a number "+
        "of %^C088%^strange appendages%^CRST%^ extend from the top of the "+
        "waist. The construct seems to never stand still and has been "+
        "constructed out of a %^C124%^strange colored alloy%^CRST%^.\n");    
    set_race("construct");
    set_body_type("humanoid");
    set_gender("male");
    set_size(2);
    set_alignment(4);
    remove_limb("neck","head","torso","left arm","left hand","right arm","right hand");
    set_attack_limbs(({"left foot","right foot"}));
    set_base_damage_type("bludgeoning"); 
    set_func_chance(100);
    set_funcs(({ 
        "round_cleanup" }));
    set_property("no death", 1);
    set_property("no fear", 1);
    set_property("fear_immunity", 1);
    set_property("no bows", 1);
    set_property("no knockdown", 1);
    set_property("no trip", 1);
    set_property("no tripped", 1);
    set_property("no paralyze", 1);
    set_property("no steal", 1);
    set_property("no dominate", 1);
    set_property("no hold", 1);
    set_property("no_random_treasure", 1);
    set_property("hidden inventory", 1);
    set_property("function and attack", 1);
    set_property("cast and attack", 1);
    set_property("darkvision", 1);
    set_true_seeing(1);
    set_monster_feats(({
        "weapon training",
        "weapon focus",
        "greater weapon focus",
        "epic weapon focus", 
        "perfect caster"}));
    set_powerlevel(5);
    counter = 1;
    buffed = 0;
    psize = 1;
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 10));
    set_class("barbarian");
    set_mlevel("barbarian", (powerlevel * 10));
    set_damage((powerlevel * 2), 5);
    set_attacks_num(powerlevel);
    set_overall_ac(-((powerlevel * 10) + 5));
    set_max_hp(powerlevel * powerlevel * 600);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "high");
    set_skill("athletics", (powerlevel * 10));
    set_property("magic resistance", (int)(powerlevel / 2));
    set_resistance_percent("piercing", 100);   
    set_resistance_percent("slashing", 100);   
    set_resistance_percent("bludgeoning", 100);   
    return;
}

void init(){
    ::init();
        new("/cmds/spells/s/_stoneskin.c")->use_spell(this_object(), 0, ((powerlevel + 1) * 10), 100, "mage");
}

void round_cleanup(){
    object room, targ;
    
    room = environment(this_object());

    check_psize();
    switch(counter){

        case 1 :
            tell_room(room, "\n%^C147%^The half-built construct stops and a small arm pops out of the waist.%^CRST%^");
            if(psize > 5){
                //Too much stuff in the room, lets wipe some out.
                wave();
                break;
            }
                // Focused attack. 

                if (!objectp(targ)) {
                   targ = pick_target();
                }

                headache(targ);
            
            break;

        case 2 :
            // Trip someone
                tell_room(room, "\nThe construct crouches low on the ground!");

                if (!objectp(targ)) {
                   targ = pick_target();
                }

                grab(targ);
            break;

        case 3 :
            // Spell Time

            if (!objectp(targ)) {
               targ = pick_target();
            }

            tell_room(room, "\nThe construct stops in the middle of the room!");

            new("/cmds/spells/b/_bolt_of_force.c")->use_spell(TO, targ, ((powerlevel + 1) * 10), 100, "psion");
            new("/cmds/spells/h/_hail_of_crystals.c")->use_spell(TO, targ, ((powerlevel + 1) * 10), 100, "psion");
            break;

        default :
            tell_room(room, "Something is wrong, please contact LoKi.");
            break;
    }
    counter++;
    if(counter > 4) counter = 1;
    return;
}

void check_psize(){
    object* attackers;
    
    attackers = query_attackers();
    psize = sizeof(filter_array(attackers, (: userp($1) :)));
    if(!psize) psize = 1;
    return;
}

void wave(object target) {
    // AOE
    // Deals 10d10 + 100 force damage to every attacker.
    object *players;
    object room;
    int i,j;

    room = environment(this_object());

    tell_room(room, "%^C249%^The small arm on the construct pulls a small sphere from its depths and throws it into the melee!%^CRST%^\n");
        tell_room(room, "\n%^C244%^tick..%^CRST%^\n");
        tell_room(room, "\n%^C244%^tick..%^CRST%^\n");
        tell_room(room, "\n%^C160%^BOOM!..%^CRST%^\n");
    players = filter_array(all_inventory(room),"is_non_immortal_player",FILTERS_D);
    j = sizeof(players);
    for(i=0;i<j;i++) {
        object targ;
        targ = players[i];
        targ->cause_typed_damage(targ,"torso",roll_dice((5,10+50)),"fire");
        targ->cause_typed_damage(targ,"torso",roll_dice((5,10+50)),"force");
    }
}

void grab(object target) {
    // Targetted stun with no damage.

    object room;

    room = environment(this_object());

    tell_object(target,"%^C031%^The construct runs across the room madly!%^CRST%^");
    tell_room(room,"%^C031%^The construct tries to sweep "+target->QCN+"%^C031%^'s leg!%^CRST%^",({target}));
    if(!target->dex_save(50)) {
        tell_object(target,"%^C027%^The construct sweeps your leg!%^CRST%^");
        tell_room(room,"%^C027%^"+target->QCN+"%^C027%^ gets tipped by the construct's leg sweep!%^CRST%^",({target}));
            target->set_tripped(roll_dice(1,2),"%^C194%^You are still trying to get back up!%^CRST%^");
        return;
    }
    else {
        tell_object(target,"%^C073%^You step back from the construct's weak attempt at a leg sweep!%^CRST%^");
        tell_room(room,"%^C073%^"+target->QCN+" %^C073%^avoid's the constructs leg sweep!%^CRST%^",({target}));
        return;
    }
}

void headache(object target) {
    // Targetted damage 10d10 + 200.

    object room;

    room = environment(this_object());

    tell_object(target,"%^C059%^The half-built construct runs towards you!%^CRST%^");
    tell_room(room,"%^C059%^The half-built construct leaps up and kicks "+target->QCN+" squarly in the chest!%^CRST%^",({target}));
    if(!target->will_save(50)) {
        tell_object(target,"%^C067%^The construct leaps up and kicks you perfectly in the chest!%^CRST%^");
        tell_room(room,"%^C067%^"+target->QCN+"%^C067%^ gets kicked in the chest!%^CRST%^",({target}));
        target->cause_typed_damage(target,"torso",roll_dice((10,10+200)),"bludgeoning");
        return;
    }
    else {
        tell_object(target,"%^C074%^The construct leaps up and kicks you but at the last moment you turn away and only take a glancing blow!%^CRST%^");
        tell_room(room,"%^C074%^"+target->QCN+"%^C074%^ turns as the construct kicks them!%^CRST%^",({target}));
        target->cause_typed_damage(target,"torso",roll_dice((5,10+100)),"bludgeoning");
        return;
    }
}


object pick_target()
{
    object* attackers;
    if (!objectp(this_object())) {
        return 0;
    }

    attackers = query_attackers();

    if (!sizeof(attackers)) {
        return 0;
    }
    return attackers[random(sizeof(attackers))];
}