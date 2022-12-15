// Chernobog (7/22/22)
// Wailing Isle - Juvenile Kraken

#include <std.h>
#include <daemons.h>
#include "../defs.h"

inherit MONSTER;

int powerlevel, counter, tentacles, low_hp, retreat;
object stomach;

void create(){
    ::create();
    set_name("juvenile kraken");
    set_id(({"kraken", "sea monster", "juvenile kraken", "gigantic kraken"}));
    set_short("%^RESET%^%^CRST%^%^C097%^gi%^C103%^g%^C109%^an%^C103%^t%^C097%^ic %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^C109%^with a %^C107%^m%^C106%^ot%^C107%^t%^C108%^le%^C107%^d %^C106%^gr%^C107%^e%^C108%^en%^C107%^-%^C106%^br%^C107%^o%^C108%^wn %^RESET%^%^C107%^h%^C106%^id%^C107%^e%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C109%^The scale of the beast is massive, easily dwarfing the nearby ship. Its body is covered in a %^C107%^m%^C106%^ot%^C107%^t%^C108%^le%^C107%^d %^C106%^hi%^C107%^d%^C108%^e%^RESET%^%^C109%^, a mix of %^C106%^greens %^C109%^and %^C108%^blues %^RESET%^%^C109%^covering it from head to tail and along each of its many %^C108%^te%^C107%^n%^C106%^tacl%^C107%^e%^C108%^s%^RESET%^%^C109%^. Those unlucky enough to be the prey to such a beast also bear witness to a massive maw lined with rows and rows of gleaming %^C249%^d%^C252%^a%^C255%^gg%^C252%^e%^C249%^r-%^C252%^l%^C255%^i%^C252%^k%^C249%^e %^C255%^t%^C249%^e%^C255%^e%^C249%^t%^C255%^h%^RESET%^%^C109%^. A pair of massive %^C214%^a%^C220%^m%^C226%^b%^C220%^e%^C214%^r %^C220%^e%^C226%^y%^C220%^e%^C214%^s %^RESET%^%^C109%^gaze about with %^C125%^ma%^C124%^le%^C196%^vol%^C124%^en%^C125%^ce%^RESET%^%^C109%^, an eagerness for destruction radiating from within.%^CRST%^\n");
    set_race("kraken");
    set_body_type("snake");
    set_gender("neuter");
    set_size(3);
    set_alignment(9);
    add_limb("tentacle","torso",0,0,0);
    set_attack_limbs(({"tentacle"}));
    set_base_damage_type("bludgeoning");
    set_func_chance(100);
    set_funcs(({ "round_cleanup" }));
    set_property("no death", 1);
    set_property("no sleep", 1);
    set_property("no dominate", 1);
    set_property("fear_immunity", 1);
    set_property("confusion_immunity", 1);
    set_property("no bows", 1);
    set_property("no paralyze", 1);
    set_property("no_random_treasure", 1);
    set_property("hidden inventory", 1);
    set_property("darkvision", 1);
    set_property("swarm", 1);
    set_property("aggressive", 40);
    set_monster_feats(({
        "blind fight",
        "weapon training",
        "weapon focus",
        "greater weapon focus",
        "epic weapon focus",
        "combat_reflexes",
        }));
    set_resistance_percent("electricity", 100);
    set_powerlevel(5);
    tentacles = 0;
    counter = 1;
    low_hp = 0;
    stomach = new(ROOMS"kraken_stomach");
    stomach->set_controller(this_object());
    
    retreat = time() + 1800;
}

void set_powerlevel(int pwrlvl){
    powerlevel = pwrlvl;
    set_hd((powerlevel * 10), 0);
    set_class("fighter");
    set_mlevel("fighter", (powerlevel * 10));
    set_damage((powerlevel * 5), 6);
    set_attacks_num(3);
    set_overall_ac(-(powerlevel * 10) + 5);
    set_max_hp(powerlevel * powerlevel * 300);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "high");
    set_skill("athletics", (powerlevel * 10) + 10);
    return;
}

void init(){
    object player;
    
    ::init();
    player = this_player();
    if(userp(player) && !avatarp(player)) force_me("kill "+player->query_name()+"");
}

void heart_beat(){
    object kraken, room;
    
    ::heart_beat();
    
    if(retreat < time()){
        kraken = this_object();
        room = environment(kraken);
        
        message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^RESET%^%^C109%^ seems to grow bored, withdrawing its tentacles from the ship. It wastes no time in sinking back beneath the %^C111%^w%^C117%^a%^C123%^v%^C111%^e%^C117%^s%^RESET%^%^C109%^, quickly disappearing from sight.%^CRST%^", room);
        kraken->move("/d/shadowgate/void.c");
        kraken->remove();
    }
    return;
}

void round_cleanup(){
    object room;
    room = environment(this_object());
    
    if(!low_hp){
        if(query_hp() < (query_max_hp() / 4)){
            low_hp = 1;
            message("environment", "\n%^RESET%^%^CRST%^%^C101%^The whole of the %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^RESET%^%^C101%^seems to shiver with %^C196%^r%^C124%^a%^C196%^g%^C124%^e%^RESET%^%^C101%^, its attacks growing more %^C144%^severe %^C101%^and %^C144%^wild!%^CRST%^\n", room);
        }
    }
    
    switch(counter){
        case 1 :
            if(!low_hp) summon_tentacles(room);
            else if(powerlevel > 4) psi_storm(room);
            break;
        case 2 :
            if(!low_hp) grab_player(room);
            else psi_storm(room);
            break;
        case 3 :
            psi_storm(room);
            break;
        default :
            message("info", "Something is wrong, please contact Chernobog.", room);
            break;
    }
    counter++;
    if(counter > 3) counter = 1;
    return;
}

void psi_storm(room){
    object *targets;
    int i;
    targets = query_attackers();
    
    if(sizeof(targets) > 3) message("combat_special", "%^RESET%^%^CRST%^%^C109%^The %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^RESET%^%^C109%^raises its %^C108%^te%^C107%^n%^C106%^tac%^C107%^l%^C108%^es %^RESET%^%^C109%^high, ribbons of %^C220%^c%^C226%^r%^C220%^ac%^C226%^kl%^C220%^i%^C226%^n%^C220%^g %^C226%^e%^C230%^l%^C226%^ec%^C220%^t%^C226%^ri%^C230%^c%^C226%^i%^C230%^t%^C226%^y %^RESET%^%^C109%^gathering at the tips that begin to rain down upon the deck of the ship!%^CRST%^", room);
    else message("combat_special", "%^RESET%^%^CRST%^%^C109%^The %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^RESET%^%^C109%^gathers itself, looming over the ship and %^C205%^f%^C199%^o%^C201%^cusi%^C199%^n%^C205%^g %^RESET%^%^C109%^on those below...%^CRST%^", room);
    
    for(i = 0; i < sizeof(targets); i++){
        if(!objectp(targets[i])) continue;
        if(sizeof(targets) > 3){ // electric storm, half damage on save
            if(SAVING_THROW_D->reflex_save(targets[i], (powerlevel * 16))){
                message("combat_special", "%^RESET%^%^CRST%^%^C118%^You scramble out of the path of the lightning, narrowing avoiding it!%^CRST%^", targets[i]);
                message("combat_special", "%^RESET%^%^CRST%^%^C118%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ scrambles out of the way!%^CRST%^", room, targets[i]);
                targets[i]->cause_typed_damage(targets[i], "torso", roll_dice((powerlevel * 4), 10), "electricity");
            }
            else{
                message("combat_special", "%^RESET%^%^CRST%^%^C196%^You are too slow and suffer the brunt of the %^C226%^e%^C230%^l%^C226%^ec%^C220%^t%^C226%^ri%^C230%^c%^C226%^al s%^C220%^t%^C226%^o%^C230%^r%^C226%^m%^RESET%^%^C196%^!%^CRST%^", targets[i]);
                message("combat_special", "%^RESET%^%^CRST%^%^C196%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^ is too slow and is struck by %^C226%^l%^C230%^i%^C226%^gh%^C220%^t%^C226%^n%^C230%^in%^C226%^g%^RESET%^%^C196%^!%^CRST%^", room, targets[i]);
                targets[i]->cause_typed_damage(targets[i], "torso", roll_dice((powerlevel * 2), 10), "electricity");
            }
        }
        else{ // psionic storm, no damage on save
            if(SAVING_THROW_D->will_save(targets[i], (powerlevel * 16))){
                message("combat_special", "%^RESET%^%^CRST%^%^C118%^You feel the weight of its will pressing in on you... but you resist!%^CRST%^", targets[i]);
                message("combat_special", "%^RESET%^%^CRST%^%^C118%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ seems to shake off something.%^CRST%^", room, targets[i]);
            }
            else{
                message("combat_special", "%^RESET%^%^CRST%^%^C196%^A %^C205%^p%^C199%^s%^C201%^ych%^C199%^i%^C205%^c s%^C199%^c%^C200%^re%^C199%^a%^C205%^m %^RESET%^%^C196%^rips through your mind, sending you reeling backwards in pain!%^CRST%^", targets[i]);
                message("combat_special", "%^RESET%^%^CRST%^%^C196%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^ staggers backwards in pain!%^CRST%^", room, targets[i]);
                targets[i]->cause_typed_damage(targets[i], "torso", roll_dice((powerlevel * 6), 10), "mental");
            }
        }
        continue;
    }
    return;
}

void grab_player(object room){
    int i;
    object *targets;
    targets = query_attackers();
    
    message("combat_special", "%^RESET%^%^CRST%^%^C109%^Several %^C108%^te%^C107%^n%^C106%^tac%^C107%^l%^C108%^es %^RESET%^%^C109%^erupt from the violent waves, %^C103%^la%^C097%^shi%^C103%^ng %^RESET%^%^C109%^out!%^CRST%^", room);
    for(i = 0; i < sizeof(targets); i++){
        if(!objectp(targets[i])) continue;
        if(!userp(targets[i])) continue;
        if(targets[i]->query_property("kraken_bound")) continue;
        if(SAVING_THROW_D->reflex_save(targets[i], (powerlevel * 17))){
            message("combat_special", "%^RESET%^%^CRST%^%^C118%^With a leap, you manage to dodge an incoming tentacle!%^CRST%^", targets[i]);
            message("combat_special", "%^RESET%^%^CRST%^%^C118%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C118%^ leaps and dodges a tentacle!%^CRST%^", room, targets[i]);
        }
        else{
            message("combat_special", "%^RESET%^%^CRST%^%^C208%^You aren't fast enough as a tentacle wraps about your body and begins dragging you towards the kraken's %^C196%^gaping mouth%^C208%^!%^CRST%^", targets[i]);
            message("combat_special", "%^RESET%^%^CRST%^%^C208%^"+targets[i]->query_cap_name()+"%^RESET%^%^CRST%^%^C208%^ isn't fast enough as a tentacle wraps about their body and begins dragging them towards the kraken's %^C196%^gaping mouth%^C208%^!%^CRST%^", room, targets[i]);
            targets[i]->set_paralyzed(16, "%^RESET%^%^CRST%^%^C109%^You're still struggling against the hold of the tentacle!%^CRST%^");
        }
        call_out("devour_fun", 6, targets[i], room);
        continue;
    }
    return;
}

void devour_fun(object target, object room){
    //message("debug", "%^BOLD%^%^RED%^ATTEMPTING TO DEVOUR: "+target+"%^RESET%^", room);
    if(!target->query_paralyzed()) return;
    if(!objectp(room)) return;
    if(!present("juvenile kraken", room)) return;
    
    message("environment", "%^RESET%^%^CRST%^%^C109%^With a final heave, the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^ tosses you through the air in a slow arc... and down into the kraken's awaiting %^C124%^maw%^C109%^.%^CRST%^", target);
    message("environment", "%^RESET%^%^CRST%^%^C109%^With a final heave, the %^RESET%^%^C108%^te%^C107%^n%^C106%^ta%^C107%^c%^C108%^le%^RESET%^%^C109%^ tosses "+target->query_cap_name()+"%^RESET%^%^CRST%^%^C109%^ through the air in a slow arc... and down into the kraken's awaiting %^C124%^maw%^C109%^.%^CRST%^", room, target);
    
    target->move(stomach);
    return;
}

void summon_tentacles(object room){
    object tentacle, kraken;
    int i, num;
    kraken = this_object();
    
    num = powerlevel - tentacles;
    for(i = 0; i < num; i++){
        tentacle = new(MON"kraken_tentacle");
        tentacle->set_controller(kraken);
        tentacle->move(room);
        kraken->add_protector(tentacle);
        message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C111%^w%^C117%^a%^C123%^t%^C117%^e%^C111%^r %^RESET%^%^C109%^suddenly froths as a %^C108%^te%^C107%^n%^C106%^tac%^C107%^l%^C108%^e %^RESET%^%^C109%^erupts from the sea!%^CRST%^", room);
        tentacles++;
    }
    return;
}

void remove_tentacle(){
    tentacles--;
    if(tentacles < 0) tentacles = 0;
    return;
}

void die(){
    object kraken, room, *targets, reward, tentacle, stone;
    int i;
    kraken = this_object();
    room = environment(kraken);
    targets = all_living(room);
    
    if(stomach){
        stomach->empty_stomach();
        stomach->remove();
    }
    
    while(tentacle = present("kraken tentacle")) tentacle->die();
    
    message("environment", "%^RESET%^%^CRST%^%^C109%^The %^C106%^k%^C112%^r%^C118%^ak%^C112%^e%^C106%^n %^RESET%^%^C109%^lets out a %^C103%^s%^C097%^h%^C091%^ri%^C097%^l%^C103%^l k%^C097%^e%^C091%^eni%^C097%^n%^C103%^g %^C097%^w%^C091%^a%^C097%^i%^C103%^l %^RESET%^%^C109%^that stops you cold for a moment, quivering before dousing you and the ship in a %^C059%^t%^C243%^hic%^C059%^k, %^C243%^oi%^C245%^l%^C243%^y i%^C245%^n%^C243%^k%^RESET%^%^C109%^. It wastes no time in sinking back beneath the %^C111%^w%^C117%^a%^C123%^v%^C111%^e%^C117%^s%^RESET%^%^C109%^, quickly disappearing from sight.%^CRST%^", room);
    for(i = 0; i < sizeof(targets); i++){
        if(!objectp(targets[i])) continue;
        if(!userp(targets[i])) continue;
        if(targets[i]->query("wailing isle quest") == 13){
            message("environment", "\n%^RESET%^%^CRST%^%^C101%^You take a %^C144%^small rag %^C101%^and wipe away most of the %^C243%^i%^C245%^n%^C243%^k%^RESET%^%^C101%^, tucking it away. Hopefully this will be enough for Mae.%^CRST%^", targets[i]);
            reward = new(OBJ"kraken_ink");
            reward->move(targets[i]);
        }
    }
    if(!random(4)){
        tell_room(room, "\n%^RESET%^%^CRST%^%^C109%^Something skitters across the deck, dislodged from the scaly hide of the kraken in its departure...%^CRST%^\n");
        stone = new(OBJ"ioun_stone");
        stone->choose_stone();
        stone->move(room);
    }
    
    kraken->move("/d/shadowgate/void.c");
    kraken->remove();
    
    return;
}

