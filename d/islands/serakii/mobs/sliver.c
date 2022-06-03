#include <std.h>
#include <magic.h>
#include <daemons.h>
#include "../serakii.h"
// sliver is magical immune

inherit MONSTER;

int powerlevel, counter, buffed, psize;

void create(){
    object ob;
    
    ::create();
    set_name("sliver");
    set_id(({"sliver","construct","half-build construct", "legs"}));
    set_short("%^C040%^Sliver%^C035%^, a t%^C041%^o%^C035%^r%^C040%^s%^C035%^o "+
        "of a c%^C042%^o%^C035%^nstru%^C040%^c%^C035%^t%^CRST%^");
    set_long("A %^C042%^strange sight%^CRST%^ indeed, this construct is just "+
        "the %^C028%^torso%^CRST%^ of a humanoid made from some %^C036%^strange "+
        "alloy%^CRST%^. It has been made to look like a %^C188%^human%^CRST%^ but "+
        "is roughly constructed and alien enough that it could never pass unless it "+
        "was covered in a %^C244%^heavy cowled cloak%^CRST%^. It is missing "+
        "its %^C035%^lower half%^CRST%^ and crawls along the %^C058%^ground%^CRST%^ by "+
        "dragging itself by its %^C035%^arms%^CRST%^.\n");
    set_race("construct");
    set_body_type("humanoid");
    set_size(3);
    set_alignment(4);
    remove_limb("waist","left leg","left foot","right leg","right foot");
    set_attack_limbs(({"left hand","right hand"}));
    set_base_damage_type("slashing");
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
    set_class("psion");
    set_mlevel("psion", (powerlevel * 10));
    set_guild_level("psion", (powerlevel * 10));
    set_damage((powerlevel * 2), 5);
    set_attacks_num(powerlevel);
    set_overall_ac(-((powerlevel * 10) + 5));
    set_max_hp(powerlevel * powerlevel * 300);
    set_hp(query_max_hp());
    set_new_exp((powerlevel * 10), "boss");
    set_skill("athletics", (powerlevel * 10));
    set_property("magic resistance", 100);
    return;
}

void init(){
    ::init();

    if((!buffed)){
        new("/cmds/spells/b/_blink.c")->use_spell(this_object(), 0, ((powerlevel + 1) * 10), 100, "mage");
        buffed = 1;
    }
}


void round_cleanup(){
    object room, targ;
    
    room = environment(this_object());

    check_psize();
    switch(counter){

        case 1 :
            tell_room(room, "\n%^C066%^The half-built torso of a construct "+
                "skitters backwards and looks around at the battle.%^CRST%^");
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
                tell_room(room, "\n%^C022%^The construct glows "+
                    "a %^C040%^bright green%^C022%^ and starts to move!%^CRST%^");

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

            tell_room(room, "\n%^C246%^The construct "+
                "glows a %^C255%^brilliant white%^C246%^ and starts to shake!%^CRST%^");

            new("/cmds/spells/b/_bolt_of_force.c")->use_spell(TO, targ, ((powerlevel + 1) * 10), 100, "psion");
            new("/cmds/spells/h/_hail_of_crystals.c")->use_spell(TO, targ, ((powerlevel + 1) * 10), 100, "psion");
            break;

        default :
            tell_room(room, "Something is wrong, please contact LoKi.");
            break;
    }
    counter++;
    if(counter > 3) counter = 1;
    return;
}

void check_psize(){
    object* attackers;
    
    attackers = query_attackers();
    psize = sizeof(filter_array(attackers, (: userp($1) :)));
    if(!psize) psize = 1;
    return;
}

void wave() {
    // AOE
    // Deals 10d10 + 100 force damage to every attacker.
    object *players;
    object room;
    int i,j;

    room = environment(this_object());

    tell_room(room, "\n%^C067%^The construct focuses "+
        "an %^C075%^arcane beam%^C067%^ that %^C195%^rips%^C067%^ "+
        "across the room!%^CRST%^\n");
    players = filter_array(all_inventory(room),"is_non_immortal_player",FILTERS_D);
    j = sizeof(players);
    for(i=0;i<j;i++) {
        object targ;
        targ = players[i];
        targ->cause_typed_damage(targ,"torso",roll_dice((10,10+100)),"force");
    }
}

void grab(object target) {
    // Targetted stun with no damage.

    object room;

    room = environment(this_object());

    tell_object(target,"\n%^C036%^The construct skitters "+
        "across the floor and tries to grab onto you!%^CRST%^");
    tell_room(room,"%^C036%^The construct tries to "+
        "grab %^CRST%^"+target->QCN+"%^C036%^!%^CRST%^",({target}));
    if(!target->dex_save(50)) {
        tell_object(target,"%^C029%^The construct grabs "+
            "onto your leg!%^CRST%^");
        tell_room(room,"%^C029%^"+target->QCN+"%^C029%^ is caught "+
            "in the grasp of the construct!%^CRST%^",({target}));
            target->set_paralyzed(roll_dice(1,2),"%^C143%^You are still trying "+
                "to get the construct off of you!%^CRST%^");
        return;
    }
    else {
        tell_object(target,"%^C029%^You avoid the grasp of the construct and kick it across the room!%^CRST%^");
        tell_room(ETO,"%^C029%^"+target->QCN+"%^C029%^ kicks the half-built construct across the room!%^CRST%^",({target}));
        return;
    }
}

void headache(object target) {
    // Targeted damage 10d10 + 200.

    object room;

    room = environment(this_object());

    tell_object(target,"%^C080%^The half-built construct meets your gaze and starts to glow brighter!%^CRST%^");
    tell_room(room,"%^C080%^The half-built construct meets%^CRST%^ "+target->QCN+"%^C080%^'s gaze and glows brighter!%^CRST%^",({target}));
    if(!target->will_save(50)) {
        tell_object(target,"%^C062%^You feel the construct's alien intelligence intrude into your mind! It scorches through your memories!%^CRST%^");
        tell_room(room," "+target->QCN+"%^C167%^ grabs their head and screams!%^CRST%^",({target}));
        target->cause_typed_damage(target,"torso",roll_dice((10,10+200)),"mental");
        return;
    }
    else {
        tell_object(target,"%^C062%^You feel the construct's alien intelligence try to intrude into your mind! You resist before it can do too much damage!%^CRST%^");
        tell_room(room," "+target->QCN+"%^C167%^ grabs their head and groans!%^CRST%^",({target}));
        target->cause_typed_damage(target,"torso",roll_dice((5,10+100)),"mental");
        return;
    }
}


object pick_target()
{
    object* attackers;
    if (!objectp(TO)) {
        return 0;
    }

    attackers = query_attackers();

    if (!sizeof(attackers)) {
        return 0;
    }
    return attackers[random(sizeof(attackers))];
}