// Chernobog & Titania (3/1/22)
// Wailing Isle - Unicorn

#include <std.h>
#include <daemons.h>
#include "../defs.h"

inherit MONSTER;

int powerlevel, counter, buffed, psize;

void create(){
    object ob;
    
    ::create();
    set_name("unicorn");
    set_id(({"unicorn"}));
    set_short("%^RESET%^%^CRST%^%^C109%^massive %^C255%^alabaster %^RESET%^%^C214%^u%^C220%^n%^C226%^ico%^C220%^r%^C214%^n %^RESET%^%^C109%^with a %^C189%^fl%^C195%^ow%^C189%^in%^C195%^g m%^C189%^an%^C195%^e%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C109%^This %^RESET%^%^C214%^u%^C220%^n%^C226%^ico%^C220%^r%^C214%^n %^RESET%^%^C109%^is a giant among equines, towering above most peers with his head held high and his long %^C255%^s%^C252%^p%^C249%^i%^C255%^r%^C252%^a%^C249%^l%^C255%^e%^C252%^d %^C249%^h%^C255%^o%^C252%^r%^C249%^n %^RESET%^%^C109%^on clear display. His coat is a beautiful %^C255%^alabaster white%^C109%^, radiant in its purity, with %^C189%^p%^C195%^ea%^C189%^rl%^C195%^es%^C189%^ce%^C195%^nt %^C189%^ha%^C195%^ir %^RESET%^%^C109%^in enchanting %^C189%^blues %^C109%^and %^C195%^greens %^RESET%^%^C109%^tumbling down from his mane and tail. Each leg ends in a large black hoof that has sunk a little in the ground, hinting at the enormous weight and power of such a massive creature.%^CRST%^\n");
    set_race("unicorn");
    set_body_type("equine");
    set_gender("male");
    set_size(3);
    set_alignment(4);
    add_limb("horn","head",0,0,0);
    set_attack_limbs(({"right fore hoof","left fore hoof","horn"}));
    set_base_damage_type("slashing");
    set_func_chance(100);
    set_funcs(({ 
        "round_cleanup" }));
    set_property("no death", 1);
    set_property("no sleep", 1);
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
        "epic weapon focus", }));
    set_spell_chance(100);
    set_spells(({
        "holy aura", }));
    set_powerlevel(5);
    counter = 1;
    buffed = 0;
    ob = new(OBJ"unicorn_horn");
    ob->move(this_object());
    psize = 1;
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 10));
    set_class("cleric");
    set_mlevel("cleric", (powerlevel * 10));
    set_guild_level("cleric", (powerlevel * 10));
    set_damage((powerlevel * 2), 5);
    set_attacks_num(powerlevel);
    set_overall_ac(-((powerlevel * 10) + 5));
    set_max_hp(powerlevel * powerlevel * 300);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "high");
    set_skill("athletics", (powerlevel * 10));
    set_property("magic resistance", (int)(powerlevel + 2));
    tell_room(environment(this_object()), "\n%^RESET%^%^CRST%^%^C109%^A magical aura %^C189%^sh%^C195%^im%^C189%^me%^C195%^rs %^RESET%^%^C109%^around the %^RESET%^%^C214%^u%^C220%^n%^C226%^ico%^C220%^r%^C214%^n%^RESET%^%^C109%^.%^CRST%^");
    return;
}

void init(){
    ::init();
    if((!buffed) && (powerlevel > 3)){
        new("/cmds/spells/h/_holy_aura.c")->use_spell(this_object(), 0, ((powerlevel + 1) * 10), 100, "cleric");
        buffed = 1;
    }
}

void round_cleanup(){
    object room;
    
    room = environment(this_object());
    check_psize();
    switch(counter){
        case 1 :
            if(powerlevel > 3) trample();
            if(psize > 1){
                tell_room(room, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^turns around for another pass!%^CRST%^");
                trample();
            }
            break;
        case 2 :
            trample();
            break;
        case 3 :
            charge_dispel();
            break;
        case 4 :
            horn_heal();
            if(psize > 2) trample();
            break;
        default :
            tell_room(room, "Something is wrong, please contact Chernobog.");
            break;
    }
    counter++;
    if(counter > 4) counter = 1;
    return;
}

void check_psize(){
    object *attackers;
    int i;
    
    attackers = query_attackers();
    //psize = sizeof(filter_array(attackers, (: userp($1) :)));
    psize = 0;
    for(i = 0; i < sizeof(attackers); i++){
        if(userp(attackers[i])) psize++;
        continue;
    }
    if(!psize) psize = 1;
    return;
}

void trample(){
    int i;
    object unicorn, room, target;
    object* attackers;
    
    unicorn = this_object();
    room = environment(unicorn);
    attackers = unicorn->query_attackers();
    
    tell_room(room, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^runs through the area, stomping about with his %^C059%^sharp hooves%^C130%^!%^CRST%^");

    for(i=0; i < (powerlevel); i++){
        target = attackers[random(sizeof(attackers))];
        if(userp(target)){
            if(SAVING_THROW_D->reflex_save(target, (powerlevel * 16))){
                tell_object(target, "%^RESET%^%^CRST%^%^C118%^You dodge away from the unicorn!%^CRST%^\n");
                tell_room(room, "%^RESET%^%^CRST%^%^C118%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ dodges away from the unicorn!%^CRST%^\n", target);
            }
            else{
                tell_object(target, "%^RESET%^%^CRST%^%^C196%^The unicorn spins, kicking you in the face with his hind hooves!%^CRST%^\n");
                tell_room(room, "%^RESET%^%^CRST%^%^C196%^The unicorn spins, kicking %^C230%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^ in the face with his hind hooves!%^CRST%^\n", target);
                target->cause_typed_damage(target, "torso", roll_dice((powerlevel * 20), 5), "bludgeoning");
                target->set_paralyzed(1, "%^RESET%^%^CRST%^%^C059%^You're still trying to get back to your feet!%^CRST%^");
            }
            if(counter == 2) tell_room(room, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^lowers its head, aiming its %^C214%^s%^C220%^o%^C226%^ft%^C220%^l%^C214%^y g%^C220%^l%^C226%^owi%^C220%^n%^C214%^g %^C220%^h%^C226%^o%^C220%^r%^C214%^n %^RESET%^%^C130%^and preparing to charge!%^CRST%^\n");
            return;
        }
        else{
            if(!objectp(target)) continue;
            tell_room(room, "%^RESET%^%^CRST%^%^C124%^"+target->query_cap_name()+" %^RESET%^%^CRST%^%^C124%^is trampled to death beneath the unicorn's hooves!%^CRST%^");
            target->die();
            attackers = unicorn->query_attackers();
            continue;
        }
    }
    if(counter == 2) tell_room(room, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^lowers its head, aiming its %^C214%^s%^C220%^o%^C226%^ft%^C220%^l%^C214%^y g%^C220%^l%^C226%^owi%^C220%^n%^C214%^g %^C220%^h%^C226%^o%^C220%^r%^C214%^n %^RESET%^%^C130%^and preparing to charge!%^CRST%^\n");
    return;
}

void charge_dispel(){
    object room, unicorn, target;
    object* attackers;
    
    unicorn = this_object();
    room = environment(unicorn);
    attackers = unicorn->query_attackers();
    target = attackers[random(sizeof(attackers))];
    
    tell_room(room, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^bears down on "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C130%^, charging directly at them!%^CRST%^", target);
    tell_object(target, "\n%^RESET%^%^CRST%^%^C130%^The %^C252%^u%^C255%^nic%^C252%^o%^C255%^r%^C252%^n %^RESET%^%^C130%^bears down on you, charging directly at you!%^CRST%^");

    if(userp(target)){
        if(SAVING_THROW_D->reflex_save(target, (powerlevel * 17))){
            tell_object(target, "%^RESET%^%^CRST%^%^C118%^You manage to dive out of the way!%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C118%^"+target->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ manages to dive out of the way!%^CRST%^\n", target);
            return;
        }
        tell_object(target, "%^RESET%^%^CRST%^%^C196%^The unicorn's horn drives deep into you!%^CRST%^\n");
        tell_room(room, "%^RESET%^%^CRST%^%^C196%^The unicorn's horn drives deep into "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^!%^CRST%^\n", target);
        target->cause_typed_damage(target, "torso", roll_dice(powerlevel * 20, 5), "piercing");
        if((target->query_alignment() == 3) || (target->query_alignment() == 6) || (target->query_alignment() == 9)){
            tell_object(target, "%^RESET%^%^CRST%^%^C226%^The horn glows brightly, reacting to you...%^CRST%^\n");
            tell_room(room, "%^RESET%^%^CRST%^%^C226%^The horn glows brightly, reacting to "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C226%^...%^CRST%^\n", target);
            new("/cmds/spells/g/_greater_dispel_magic.c")->use_spell(unicorn, target, (powerlevel * 10), 100, "mage");
        }
        return;
    }
    tell_room(room, "%^RESET%^%^CRST%^%^C226%^"+target->query_cap_name()+" %^RESET%^%^CRST%^%^C226%^is engulfed in %^C250%^w%^C252%^h%^C255%^i%^C252%^t%^C250%^e l%^C252%^i%^C255%^g%^C252%^h%^C252%^t %^RESET%^%^C226%^and banished!%^CRST%^\n");
    target->die();
    return;
}

void horn_heal(){
    object unicorn, room;
    unicorn = this_object();
    room = environment(unicorn);
    
    tell_room(room, "%^RESET%^%^CRST%^%^C226%^The unicorn's horn shines brilliantly with pulses of %^C252%^r%^C255%^adi%^C252%^a%^C255%^nc%^C252%^e%^RESET%^%^C226%^. Its wounds begin to close and heal!%^CRST%^\n");
    unicorn->cause_typed_damage(unicorn, "torso", powerlevel * psize * 300, "positive energy");
    return;
}

void die(){
    tell_room(environment(this_object()), "\n%^RESET%^%^CRST%^%^C109%^The %^C214%^u%^C220%^n%^C226%^ico%^C220%^r%^C214%^n %^RESET%^%^C109%^finally collapses to the ground in a bloody heap, only its %^C255%^s%^C252%^p%^C249%^i%^C255%^r%^C252%^a%^C249%^l%^C255%^e%^C252%^d %^C249%^h%^C255%^o%^C252%^r%^C249%^n %^RESET%^%^C109%^appearing untouched by the %^C124%^violence%^C109%^.%^CRST%^\n");
    ::die();
}

