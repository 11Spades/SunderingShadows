#include <std.h>
#include <daemons.h>
#include <dirs.h>
#include <magic.h>

#define VALID ({ "black", "blue", "brass", "bronze", "copper", "gold", "green", "red", "silver", "white" }) 

inherit FEAT;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("Presence");
    feat_name("dragon aspect");
    feat_syntax("dragon_aspect");
    feat_classes("oracle");
    feat_desc("This feat allows an oracle with the dragon mystery take on attributes of their chosen dragon type, such as claw attacks, tail swipe, and breath weapons. While dragon aspect is active, these dragon specials will automatically happen during combat.");
    allow_tripped(1);
}

int allow_shifted()
{
    return 1;
}

int cmd_dragon_aspect(string str)
{
    object feat;
    if (!objectp(this_player())) {
        return 0;
    }
    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);

    return 1;
}

int prerequisites(object ob)
{
    if (!objectp(ob))
        return 0;
        
    if (!ob->is_class("oracle"))
        return 0;
    
    if(ob->query_mystery() != "dragon")
        return 0;
    
    return ::prerequisites(ob);
}

void execute_feat()
{
    object obj;

    ::execute_feat();

    if (!objectp(caster)) {
        dest_effect();
        return;
    }

    if (FEATS_D->is_active(caster, "dragon aspect")) {
        obj = query_active_feat("dragon aspect");
        obj->dest_effect();
        
        tell_object(caster, "%^CYAN%^You let go of your dragon aspect and return to normal.");
        
        caster = 0;
        dest_effect();
        return;
    }

    if (caster->query_property("using instant feat")) {
        tell_object(caster, "%^BOLD%^You are already in the middle of using a feat.%^RESET%^");
        dest_effect();
        return;
    }
    if (caster->query_casting()) {
        tell_object(caster, "%^BOLD%^You take on your dragon aspect while you're casting a spell.%^RESET%^");
        dest_effect();
        return;
    }
    
    tell_object(caster, "%^YELLOW%^You call on your draconic blood, and feel your body taking on the attributes of your dragon aspect.");
    tell_object(caster, "%^RED%^BOLD%^Your fingers extend into razor-sharp claws!");
    if(caster->query_class_level("oracle") >= 5)
        tell_object(caster, "%^GREEN%^BOLD%^You feel energy well up in your lungs!");
    if(caster->query_class_level("oracle") >= 21)
        tell_object(caster, "%^BLUE%^BOLD%^You feel a tail form and grow, extending behind you!");
    if(caster->query_class_level("oracle") >= 31)
        tell_object(caster, "%^YELLOW%^You feel your mind and body harden with a dragon's resilience!");
        
    set_active(this_object());
    //caster->set_property("active_feats", ({ TO }));
    return;
}

void execute_attack()
{
    object attacker, *attackers;
    string my_name, att_name, my_poss, att_poss, dam_type;
    int level, bonus, dam;
    
    ::execute_attack();
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    
    if(!objectp(place))
    {
        dest_effect();
        return;
    }

    if (caster->query_ghost() || caster->query_unconscious())
    {
        place->addObjectToCombatCycle(this_object(), 1);
        return;
    }

    if(caster->query_bound() || caster->query_paralyzed())
    {
        place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
    
    attacker = caster->query_current_attacker();
    
    if(!objectp(attacker))
    {
        place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
         
    my_name = caster->query_cap_name();
    att_name = attacker->query_cap_name();
    my_poss = caster->query_possessive();
    att_poss = attacker->query_possessive();
    level = caster->query_class_level("oracle");
    attackers = caster->query_attackers();
    place = environment(caster);
    bonus = COMBAT_D->unarmed_enchantment(caster) + max( ({ BONUS_D->query_stat_bonus(caster, "strength"), BONUS_D->query_stat_bonus(caster, "dexterity") }) );
    
    
    //CLAW ATTACK
    if(attacker && thaco(attacker, bonus))
    {
        switch(random(3))
        {
            case 0:
            tell_object(caster, "%^RESET%^%^CRST%^%^C125%^You %^C127%^lash %^C125%^out at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^, %^C196%^raking %^C125%^them with %^C255%^raz%^C252%^o%^C255%^r s%^C252%^h%^C255%^ar%^C252%^p c%^C255%^law%^C252%^s%^C125%^!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C125%^" + my_name + "%^RESET%^%^CRST%^%^C127%^ lashes out at you, raking you with %^C255%^raz%^C252%^o%^C255%^r s%^C252%^h%^C255%^ar%^C252%^p c%^C255%^law%^C252%^s%^C125%^!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C125%^" + my_name + "%^RESET%^%^CRST%^%^C127%^ lashes out at %^CRST%^" + att_name + "%^RESET%^%^CRST%^, raking them with %^C255%^raz%^C252%^o%^C255%^r s%^C252%^h%^C255%^ar%^C252%^p c%^C255%^law%^C252%^s%^C125%^!%^CRST%^", ({ caster, attacker }));
            break;
            
            case 1:
            tell_object(caster, "%^RESET%^%^CRST%^%^C125%^You let out a %^C244%^l%^C250%^o%^C244%^w gr%^C248%^o%^C250%^w%^C244%^l %^C125%^as you %^C196%^rip %^C125%^and %^C196%^tear %^C125%^into %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C125%^" + my_name + "%^RESET%^%^CRST%^%^C125%^ lets out a %^C244%^l%^C250%^o%^C244%^w gr%^C248%^o%^C250%^w%^C244%^l %^C125%^as they %^C125%^and %^C196%^tear %^C125%^into you!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C125%^" + my_name + "%^RESET%^%^CRST%^%^C125%^ lets out a %^C244%^l%^C250%^o%^C244%^w gr%^C248%^o%^C250%^w%^C244%^l %^C125%^as they %^C125%^and %^C196%^tear %^C125%^into %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^!%^CRST%^", ({ caster, attacker }));
            break;
            
            default:
            tell_object(caster, "%^RESET%^%^CRST%^%^C255%^Tal%^C252%^o%^C255%^n%^C252%^s %^C125%^outspread, you %^C196%^lunge %^C125%^at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^ and %^C196%^gouge %^C125%^their flesh!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C255%^Tal%^C252%^o%^C255%^n%^C252%^s %^C125%^outspread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at you and %^C196%^gouges %^C125%^your flesh!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C255%^Tal%^C252%^o%^C255%^n%^C252%^s %^C125%^outspread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^ and %^C196%^gouges %^C125%^their flesh!%^CRST%^", ({ caster, attacker }));
            break;
        }
        
        dam = (roll_dice(1, 6) * (1 + flevel /  10)) + bonus;
        caster->cause_typed_damage(attacker,attacker->return_target_limb(),dam ,"piercing");    
    }
    
    if(level < 5)
    {
        place && place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
    
    if(!caster->query("dragon_affinity"))
    {
        place && place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
    
    //BREATH ATTACK
    if(!random(3) && sizeof(attackers))
    {    
        switch(caster->query("dragon_affinity"))
        {
            case "black":
            case "copper":
            tell_object(caster, "%^GREEN%^BOLD%^You breathe a gout of steaming acid at your enemies!%^RESET%^");
            tell_room(place, "%^GREEN%^BOLD%^" + my_name + " breathes a gout of steaming acid at their enemies!%^RESET%^", caster);
            dam_type = "acid";
            break;
        
            case "blue":
            case "bronze":
            tell_object(caster, "%^YELLOW%^BOLD%^You breathe great arcs of electricity at your enemies!%^RESET%^");
            tell_room(place, "%^YELLOW%^BOLD%^" + my_name + " breathes great arcs of electricity at their enemies!%^RESET%^", caster);
            dam_type = "electricity";
            break;
        
            case "brass":
            case "red":
            case "gold":
            tell_object(caster, "%^RED%^BOLD%^You breathe great gouts of flame at your enemies!%^RESET%^");
            tell_room(place, "%^YELLOW%^BOLD%^" + my_name + " breathes great gouts of flame at their enemies!%^RESET%^", caster);
            dam_type = "fire";
            break;

            case "green":
            tell_object(caster, "%^GREEN%^You breathe a cloud of poison at your enemies!%^RESET%^");
            tell_room(place, "%^GREEN%^" + my_name + " breathes a cloud of poison at their enemies!%^RESET%^", caster);
            dam_type = "untyped";
            break;

            case "white":
            case "silver":
            tell_object(caster, "%^BLUE%^BOLD%^You breathe sheets of ice and snow at your enemies!%^RESET%^");
            tell_room(place, "%^BLUE%^BOLD%^" + my_name + " breathes sheets of ice and snow at their enemies!%^RESET%^", caster);
            dam_type = "cold";
            break;
        }
    
        dam = (5 + roll_dice(1, 8) * (1 + flevel /  10) + BONUS_D->query_stat_bonus(caster, "charisma"));
    
        if(sizeof(attackers) > 6)
            attackers = attackers[0..6];
    
        foreach(object ob in attackers)
        {
            if(do_save(ob, bonus))
            {
                tell_room(place, "%^BOLD%^" + ob->query_cap_name() + " scrambles out of the way of the breath!", ob);
                tell_object(ob, "%^BOLD%^You scramble out of the way of the breath!");
                ob->cause_typed_damage(ob, ob->return_target_limb(), dam / 2, dam_type);
            }
            else
            {
                tell_room(place, "%^BOLD%^" + ob->query_cap_name() + " is caught in the breath!", ob);
                tell_object(ob, "%^BOLD%^You are caught in the breath!");
                ob->cause_typed_damage(ob, ob->return_target_limb(), dam, dam_type);
            }
        }
    }
    
    if(level < 21)
    {
        place && place->addObjectToCombatCycle(this_object(), 1);
        return;
    }
    
    attacker = caster->query_current_attacker();
    att_name = attacker->query_cap_name();
    
    //TAIL ATTACK
    switch(random(3) && objectp(attacker))
    {
        case 0:
        tell_object(caster, "%^RESET%^%^CRST%^%^C202%^Darting %^C130%^to the %^C208%^side%^C130%^, you bring your tail about to %^C196%^slam %^C130%^into %^CRST%^%^RESET%^%^CRST%^%^C130%^" + att_name + "!%^CRST%^");
        tell_object(attacker, "%^RESET%^%^CRST%^%^C202%^Darting %^C130%^to the %^C208%^side%^C130%^, %^CRST%^" + my_name + "%^RESET%^%CRST%^%^C130%^ brings their tail about to %^C196%^slam %^C130%^into you!%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C202%^Darting %^C130%^to the %^C208%^side%^C130%^, %^CRST%^" + my_name + "%^RESET%^%CRST%^%^C130%^ brings their tail about to %^C196%^slam %^C130%^into %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C130%^!%^CRST%^", ({ caster, attacker }));
        break;
        
        default:
        tell_object(caster, "%^RESET%^%^CRST%^%^C130%^You swing your body %^C202%^low %^C130%^and %^C208%^fast%^C130%^, your tail coming about like a whip at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C130%^!%^CRST%^");
        tell_object(attacker, "%^RESET%^%^CRST%^%^C130%^" + my_name + "%^RESET%^%^CRST%^%^C130%^ swings their body %^C202%^low %^C130%^and %^C208%^fast%^C130%^, their tail coming about like a whip at you!%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C130%^" + my_name + "%^RESET%^%^CRST%^%^C130%^ swings their body %^C202%^low %^C130%^and %^C208%^fast%^C130%^, their tail coming about like a whip at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C130%^!%^CRST%^", ({ attacker, caster }));
    }
    
    dam = (roll_dice(1, 10) * (1 + flevel /  10)) + bonus;
    
    if(do_save(attacker, bonus))
    {
        tell_room(place, "%^BOLD%^" + att_name + " avoids the tail swing!", attacker);
        tell_object(attacker, "You avoid the tail swing!");
    }
    else
    {
        attacker->set_tripped(roll_dice(1, 4) * 6, "%^BOLD%^You are struggling to get up!%^RESET%^");
        attacker->cause_typed_damage(attacker, "torso", dam, "bludgeoning");
    }
    
    if(place)
        place->addObjectToCombatCycle(this_object(), 1);
    else
        dest_effect();
    
    return;
    
}


void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
