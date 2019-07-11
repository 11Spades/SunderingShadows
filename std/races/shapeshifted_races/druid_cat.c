#include <std.h>
#include <daemons.h>

inherit SHAPESHIFT;

// all of the functions set in create below need to be there so it doesn't bug when trying to shapeshift -Ares
// when making a new shape, be sure to include those functions or it'll fall back to the defaults
void create()
{
    ::create();

    set_attack_limbs( ({ "fangs","right fore claw","left fore claw","right rear claw","left rear claw" }) );
    set_new_damage_type("piercing");    
    set_limbs( ({ "fangs","head","torso","right fore claw", "left fore claw", "right rear claw","left rear claw","right foreleg","right forepaw","left foreleg","left forepaw","right rear leg","right rear paw","left rear leg","left rear paw","tail" }) );
    set_attack_functions( ([ "fangs" : (:TO,"bite_attack":), "right fore claw" : (:TO,"claw_attack":), "left fore claw" : (:TO,"claw_attack":), "right rear claw": (:TO,"grab_attack":),"left rear claw" : (:TO,"grab_attack":)   ]) );
    set_ac_bonus(-5); // ac bonus is different from the other bonuses because of the way ac is calculated with different body types -Ares
    set_base_attack_num(4); 
    set_castable(0);
    set_can_talk(0);
    set_shape_race("cat");
    set_shape_language("sylvan");
    set_shape_profile("druid_cat_999"); // needs to be something the player is unlikely to name one of their profiles when disguise goes in
    set_shape_bonus("perception",2);
    set_shape_bonus("survival",4);
    set_shape_bonus("athletics",2);
    set_shape_bonus("stealth",2); 
    set_shape_bonus("sight bonus",5);
    set_shape_bonus("damage bonus",2);
    set_shape_bonus("attack bonus",2);
    set_shape_height(36+random(12));
    set_shape_weight(200+random(100));
    set_shape_mastery_feat("whirl");
}

string * query_subraces() {
    return ({ "cat","tiger","leopard","panther","lion","lynx","cheetah","jaguar","ocelot" });
}

// custom descriptions here, override this function
int default_descriptions(object obj)
{
    if(!objectp(obj)) { return 0; }

    obj->set_description("'s long feline body is covered in smooth fur from tip of snout to the end of "
        ""+obj->QP+" long tail.  The graceful movements of "+obj->QP+" body show "+obj->QS+" to be a "
        "dangerous predator.");

    obj->setDescriptivePhrase("agile cat $R with predatory eyes");

    obj->set("speech string","growl");
    obj->set("describe string","angrily");

    obj->force_me("message in slinks in");
    obj->force_me("message out stalks off to the $D");

    return 1;
}


// custom shapeshift messages here, override this function
int change_into_message(object obj)
{
    if(!objectp(obj)) { return 0; }
    tell_object(obj,"%^RESET%^%^GREEN%^You turn your mind out to the wilds as you focus on the core of your spirit.");
    tell_object(obj,"%^RESET%^%^BOLD%^You can feel your body beginning to change!");
    tell_object(obj,"%^RESET%^%^BLUE%^Your senses heighten, you can feel the pulse of the world, smell countless scents, "
        "you can taste the very air.  Your body grows long and lean, your reflexes are amplified and you feel yourself growing "
        "faster.  You are CAT!%^RESET%^");

    tell_room(environment(obj),"%^RESET%^%^BOLD%^"+obj->QCN+" grows very still and appears to concentrate deeply.",obj);
    tell_room(environment(obj),"%^RESET%^%^YELLOW%^"+obj->QCN+" begins to change in front of your very eyes!",obj);
    tell_room(environment(obj),"%^RED%^Where "+obj->QCN+" once stood, now stands a large CAT!",obj);

    return 1;
}


// custom unshapeshift messages here, override this function
int change_outof_message(object obj)
{
    if(!objectp(obj)) { return 0; }

    tell_object(obj,"%^RESET%^%^BOLD%^You relax your focus on the natural world.");
    tell_object(obj,"%^RESET%^%^BLUE%^You can feel your reflexes dulling and the keen edge of intellect returning.");
    tell_object(obj,"%^RESET%^%^GREEN%^You inhale a breath and stretch as you grow accustomed to the foreign sensation of your own body once again.");

    tell_room(environment(obj),"%^RESET%^%^BOLD%^"+obj->QCN+"'s muscles slacken and "+obj->QS+" gets a far-away look in "+obj->QP+" eyes.",obj);
    tell_room(environment(obj),"%^RESET%^%^BLUE%^"+obj->QCN+"'s body begins to change shape, shrinking and quickly loosing fur!",obj);
    tell_room(environment(obj),"%^RESET%^%^GREEN%^Where "+obj->QCN+" once stood, now stands a "+obj->query_race()+"!",obj);
    
    return 1;
}

int can_cast() 
{ 
    if(!objectp(query_owner())) { return 0; }
    if(FEATS_D->usable_feat(query_owner(),"wild spellcraft")) { return 1; }
    return can_cast_spells; 
}


int bite_attack(object tp, object targ)
{
    object etp,*attackers;
    string *specials=({}),*active_specials=({});
    int i,chance,dice;
 
    etp = environment(tp);

    if(!objectp(tp)) { return 0; }
    attackers = (object*)tp->query_attackers();    
    if(!objectp(targ) && !sizeof(attackers)) { return 0; }

    chance = (int)tp->query_guild_level("druid");

    if(chance > 60) { chance = 60; }
    if(chance > 29 && !FEATS_D->usable_feat(TP,"savage instincts iii")) { chance = 29; }
    if(chance > 19 && !FEATS_D->usable_feat(TP,"savage instincts ii")) { chance = 19; }
    if(chance > 9 && !FEATS_D->usable_feat(TP,"savage instincts i")) { chance = 9; }

    dice = ( chance / 4) + 2;
    
    if(FEATS_D->usable_feat(tp,"perfect predator")) 
    { 
        dice += 3; 
        tp->add_hp(dice);
    }

    if(roll_dice(1,100) > chance) { return roll_dice(2,dice); }
    
    // switch falls through intentionally 
    switch(chance)
    {
        case 35..60: specials += ({ "blind" });
        case 30..34: specials += ({ "stun" });
        case 25..29: specials += ({ "extra attack" });
        case 20..24: specials += ({ "high damage" });
        case 15..19: specials += ({ "extra attack" });
        case 10..14: specials += ({ "extra attack" });
        default:     specials += ({ "high damage"  });
    }

    //////////////
    i=0;

    do
    {
        active_specials += ({ specials[random(sizeof(specials))] });
        i += 4;
    }
    while(roll_dice(1,100) < (chance - i));
    //////////////

    set_new_damage_type("piercing");
  
    for(i=0;i<sizeof(active_specials);i++)
    {
        if(!objectp(tp) || !objectp(targ)) { return 0; }

        switch(active_specials[i])
        {

        case "blind":
            if(!random(3)){
//               tell_object(tp,"%^B_BLUE%^%^BOLD%^%^GREEN%^You failed to blind "+targ->QCN+". ~Debugging Message~%^RESET%^");
               break;
            }else{
            tell_object(tp,"%^GREEN%^You clamp your fangs deep into "+targ->QCN+"'s forehead!");
            tell_object(targ,"%^GREEN%^"+tp->QCN+" clamps "+tp->QP+" fangs into your forehead, blinding you!");
            tell_room(etp,"%^GREEN%^"+tp->QCN+" clamps "+tp->QP+" fangs into "+targ->QCN+"'s forehead, blinding "+targ->QO+"!",({tp,targ}));

            if(!targ->fort_save(chance)) { targ->set_temporary_blinded(dice/6); }
            break; 
            }           

        case "high damage":

            tell_object(tp,"%^RED%^You dig your claws into "+targ->QCN+"'s spine, running up "+targ->QP+" back and biting down hard on the back of "+targ->QP+" neck!");
            tell_object(targ,"%^RED%^"+tp->QCN+" digs "+tp->QP+" claws into your spine and darts up your back, biting down hard on the back of your neck!");
            tell_room(etp,"%^RED%^"+tp->QCN+" digs "+tp->QP+" claws into "+targ->QCN+"'s spine and runs up "+targ->QP+" back, biting down hard on the back of "+targ->QP+" neck!",({tp,targ}));

            targ->cause_typed_damage(targ,targ->return_target_limb(),roll_dice(dice,4),get_new_damage_type());
            break;

        case "stun":

            tell_object(tp,"%^CYAN%^You lunge at "+targ->QCN+"'s throat, narrowly missing a kill!");
            tell_object(targ,"%^CYAN%^"+tp->QCN+" lunges at your throat, almost killing you!  You fall into a better defensive posture!");
            tell_room(etp,"%^CYAN%^"+tp->QCN+" lunges at "+targ->QCN+"'s throat, almost killing "+targ->QO+".  "+targ->QCN+" falls back into a better defensive stance!",({tp,targ}));

            targ->set_paralyzed(roll_dice(1,dice/2),"%^RESET%^%^YELLOW%^You're busy finding a better way to protect your throat!");
            break;

        case "extra attack":

            tell_object(tp,"%^YELLOW%^You sink your fangs into "+targ->QCN+"'s shoulder and start kicking "+targ->QO+" in the stomach with your hind legs!");
            tell_object(targ,"%^YELLOW%^"+tp->QCN+" sinks "+tp->QP+" fangs into your shoulder and starts kicking your midsection with his hind legs!");
            tell_room(etp,"%^YELLOW%^"+tp->QCN+" sinks "+tp->QP+" fangs into "+targ->QCN+"'s shoulder and starts kicking "+targ->QP+" stomach with "+tp->QP+" hind legs!",({tp,targ}));

            tp->execute_attack();
            break;

        }
    }

    return roll_dice(2,dice);
}


int claw_attack(object tp, object targ)
{
    object etp,*attackers;
    string *specials=({}),*active_specials=({});
    int i,chance,dice;
 
    etp = environment(tp);

    if(!objectp(tp)) { return 0; }
    attackers = (object*)tp->query_attackers();    
    if(!objectp(targ) && !sizeof(attackers)) { return 0; }

    chance = (int)tp->query_guild_level("druid");

    if(chance < 10) { chance = 10; }
    if(chance > 60) { chance = 60; }

    dice = ( chance / 4) + 2;

    if(roll_dice(1,100) > chance) { return roll_dice(2,dice); }
    
    // switch falls through intentionally 
    switch(chance)
    {
        case 35..60: specials += ({ "blind" });
        case 30..34: specials += ({ "extra attack" });
        case 25..29: specials += ({ "extra attack" });
        case 20..24: specials += ({ "high damage" });
        case 15..19: specials += ({ "stun" });
        case 10..14: specials += ({ "extra attack" });
        default:     specials += ({ "high damage"  });
    }

    //////////////
    i=0;

    do
    {
        active_specials += ({ specials[random(sizeof(specials))] });
        i += 5;
    }
    while(roll_dice(1,100) < (chance - i));
    //////////////

    set_new_damage_type("slashing");
  
    for(i=0;i<sizeof(active_specials);i++)
    {
        if(!objectp(tp) || !objectp(targ)) { return 0; }

        switch(active_specials[i])
        {

        case "blind":
            if(!random(3)){
//               tell_object(tp,"%^B_BLUE%^%^BOLD%^%^GREEN%^You failed to blind "+targ->QCN+". ~Debugging Message~%^RESET%^");
               break;
            }else{

            tell_object(tp,"%^BOLD%^%^BLUE%^You rake your claws straight across "+targ->QCN+"'s eyes!");
            tell_object(targ,"%^BOLD%^%^BLUE%^"+tp->QCN+" rakes "+tp->QP+" claws straight across your eyes, blinding you!");
            tell_room(etp,"%^BOLD%^%^BLUE%^"+tp->QCN+" rakes "+tp->QP+" claws straight across "+targ->QCN+"'s eyes, blinding "+targ->QO+"!",({tp,targ}));

            if(!targ->reflex_save(chance)) { targ->set_temporary_blinded(dice/6); }
            break;
            }            

        case "high damage":

            tell_object(tp,"%^RED%^You dart underneath "+targ->QCN+" flipping onto your back and digging your claws deeply into "+targ->QP+" loins!");
            tell_object(targ,"%^RED%^"+tp->QCN+" darts underneath you, flipping onto "+tp->QP+" back and digging "+tp->QP+" claws deeply into your loins!");
            tell_room(etp,"%^RED%^"+tp->QCN+" darts underneath "+targ->QCN+", flipping onto "+tp->QP+" back and digging "+tp->QP+" claws deeply into "+targ->QP+" loins!",({tp,targ}));

            targ->cause_typed_damage(targ,targ->return_target_limb(),roll_dice(4,dice),get_new_damage_type());
            break;


        case "stun":

            tell_object(tp,"%^BOLD%^%^GREEN%^You leap high into the air, landing squarely on "+targ->QCN+", knocking the wind out of "+targ->QO+"!");
            tell_object(targ,"%^BOLD%^%^GREEN%^"+tp->QCN+" leaps high into the air and lands on you, knocking the wind out of you!");
            tell_room(etp,"%^BOLD%^%^GREEN%^"+tp->QCN+" leaps high into the air and lands on "+targ->QCN+", knocking the wind out of "+targ->QO+"!",({tp,targ}));

            targ->set_paralyzed(roll_dice(1,dice/2),"%^RESET%^%^YELLOW%^You're struggling to regain your breath!");
            break;


        case "extra attack":

            tell_object(tp,"%^ORANGE%^You run repeatedly around "+targ->QCN+", using "+targ->QP+" own body for traction!");
            tell_object(targ,"%^ORANGE%^"+tp->QCN+" runs around you repeatedly, "+tp->QP+" claws digging into your body for traction!");
            tell_room(etp,"%^ORANGE%^"+tp->QCN+" runs around "+targ->QCN+" repeatedly, using "+targ->QP+" own body for traction!",({tp,targ}));

            tp->execute_attack();
            break;
        }
    }

    return roll_dice(2,dice);
}


int grab_attack(object tp, object targ)
{
    object etp,*attackers;
    string *specials=({}),*active_specials=({}),my_limb;
    int i,chance,dice;
 
    etp = environment(tp);

    if(!objectp(tp)) { return 0; }
    attackers = (object*)tp->query_attackers();    
    if(!objectp(targ) && !sizeof(attackers)) { return 0; }

    chance = (int)tp->query_guild_level("druid");

    if(chance < 10) { chance = 10; }
    if(chance > 60) { chance = 60; }

    dice = ( chance / 4) + 2;

    if(roll_dice(1,100) > chance) { return roll_dice(2,dice); }
    
    // switch falls through intentionally 
    switch(chance)
    {
        case 35..60: specials += ({ "blind" });
        case 30..34: specials += ({ "trip" });
        case 25..29: specials += ({ "trip" });
        case 20..24: specials += ({ "high damage" });
        case 15..19: specials += ({ "high damage" });
        case 10..14: specials += ({ "extra attack" });
        default:     specials += ({ "trip"  });
    }

    //////////////
    i=0;

    do
    {
        active_specials += ({ specials[random(sizeof(specials))] });
        i += 5;
    }
    while(roll_dice(1,100) < (chance - i));
    //////////////

    set_new_damage_type("slashing");
  
    for(i=0;i<sizeof(active_specials);i++)
    {
        if(!objectp(tp) || !objectp(targ)) { return 0; }

        switch(active_specials[i])
        {

        case "blind":
            if(!random(3)){
//               tell_object(tp,"%^B_BLUE%^%^BOLD%^%^GREEN%^You failed to blind "+targ->QCN+". ~Debugging Message~%^RESET%^");
               break;
            }else{

            tell_object(tp,"%^MAGENTA%^You bite down onto "+targ->QCN+"'s "+(my_limb=targ->return_target_limb())+" and furiously kick at "+targ->QO+" with your hind legs, hitting "+targ->QO+" in the eye!");
            tell_object(targ,"%^MAGENTA%^"+tp->QCN+" bites down onto your "+my_limb+" and furiously kicks at you with "+tp->QP+" hind legs, hitting you in the eye!");
            tell_room(etp,"%^MAGENTA%^"+tp->QCN+" bites down onto "+targ->QCN+"'s "+my_limb+" and furiously kicks at "+targ->QO+" with "+tp->QP+" hind legs, hitting "+targ->QO+" in the eye!",({tp,targ}));

            if(!targ->fort_save(chance)) { targ->set_temporary_blinded(dice/6); }
            break;
            }            

        case "trip":

            tell_object(tp,"%^ORANGE%^You latch on to "+targ->QCN+" with all four claws, dragging "+targ->QO+" to the ground!");
            tell_object(targ,"%^ORANGE%^"+tp->QCN+" latches onto you with all for claws, dragging you to the ground!");
            tell_room(etp,"%^ORANGE%^"+tp->QCN+" latches onto "+targ->QCN+" with all four claws, dragging "+targ->QO+" to the ground!",({tp,targ}));

            if(!targ->reflex_save(chance)) { targ->set_tripped(roll_dice(1,dice/2),"%^RESET%^%^YELLOW%^You are struggling to get your feet back under you!"); }
            break;

        case "high damage":

            tell_object(tp,"%^RED%^You leap onto "+targ->QCN+", holding on with both front claws as you visciously rake your hind legs down over "+targ->QP+" middle!");
            tell_object(targ,"%^RED%^"+tp->QCN+" leaps onto you, holding on with both front claws and visciously raking "+tp->QP+" hind legs down over your middle!");
            tell_room(etp,"%^RED%^"+tp->QCN+" leaps onto "+targ->QCN+", holding on with both front claws and visciously raking "+tp->QP+" hind legs down over "+targ->QP+" middle!",({tp,targ}));

            targ->cause_typed_damage(targ,targ->return_target_limb(),roll_dice(dice,6),get_new_damage_type());
            break;


        case "extra attack":

            tell_object(tp,"%^BOLD%^%^CYAN%^You dig your rear claws into "+targ->QCN+" and push off, launching yourself into the air!  On the way by "+targ->QP+" face, you quickly lash out and strike "+targ->QO+" again!");
            tell_object(targ,"%^BOLD%^%^CYAN%^"+tp->QCN+" digs "+tp->QP+" rear claws into you and launches into the air!  On the way by "+tp->QS+" your face, "+tp->QS+" quickly lashes out and strikes you again!");
            tell_room(etp,"%^BOLD%^%^CYAN%^"+tp->QCN+" digs "+tp->QP+" rear claws into "+targ->QCN+" and launches "+tp->QO+"self into the air!  On the way by "+targ->QP+" face, "+tp->QS+" lashes out and quickly strikes "+targ->QO+" again!",({tp,targ}));
            
            tp->execute_attack();
            break;

        }
    }

    return roll_dice(2,dice);
}