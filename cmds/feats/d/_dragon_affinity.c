#include <std.h>
#include <daemons.h>
#include <dirs.h>

#define VALID ({ "black", "blue", "brass", "bronze", "copper", "gold", "green", "red", "silver", "white" }) 

inherit FEAT;

void create()
{
    ::create();
    feat_type("permanent");
    feat_category("Presence");
    feat_name("dragon affinity");
    feat_syntax("dragon_affinity");
    feat_desc("This feat allows an oracle with the dragon mystery to choose their chosen dragon affinity. This will determine things like resistance granted and damage types for breath weapons.
    
%^CYAN%^BOLD%^The choices for dragon affinity are as follows: \n\%^RED%^" + implode(VALID,"\n") + "%^RESET%^");
    permanent(1);
    allow_tripped(1);
}

int allow_shifted()
{
    return 1;
}

int cmd_dragon_affinity(string args)
{
    if(this_player()->query("dragon_affinity"))
    {
        tell_object(TP,"%^BOLD%^%^WHITE%^You already have your dragon affinity set.");
        return 1;
    }

    tell_object(TP,"%^BOLD%^%^WHITE%^Select your dragon affinity:\n");
    tell_object(TP,"%^BOLD%^%^MAGENTA%^" + implode(map_array(VALID, (:"  " + $1:)), "\n"));
    tell_object(TP,"%^BOLD%^%^WHITE%^\nEnter anything else to abort.");
    input_to("select_affinity", 0);
    return 1;
}

void select_affinity(string args)
{
    if(member_array(args, VALID) == -1)
    {
        tell_object(TP,"%^BOLD%^%^WHITE%^Aborting...");
        return;
    }

    tell_object(TP,"%^BOLD%^%^WHITE%^You have selected %^CYAN%^" + args + "%^WHITE%^ as your dragon affinity.");
    tell_object(TP,"%^BOLD%^%^WHITE%^Is this a correct choice? Type %^GREEN%^yes%^WHITE%^ to confirm, anything else to abort.");
    input_to("confirm_selection", 0);
    return;
}

void confirm_selection(string args)
{
    if (args != "yes") {
        tell_object(this_player(), "%^BOLD%^%^WHITE%^Aborting...");
        return;
    }

    this_player()->set("dragon_affinity", args);
    tell_object(TP,"%^BOLD%^%^WHITE%^Your dragon affinity has been set.");
    return;
}

int prerequisites(object ob)
{
    if (!objectp(ob))
        return 0;
        
    if (!ob->is_class("oracle"))
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

void permanent_effects(object ob)
{
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob)
{
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void execute_attack()
{
    object attacker, *attackers;
    string my_name, att_name, my_poss, att_poss, dam_type;
    int level, bonus, dam;
    
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }

    if (caster->query_ghost() || caster->query_unconscious())
        return;

    if(caster->query_bound() || caster->query_paralyzed())
        return;
    
    attacker = caster->query_current_attacker();
    
    if(!attacker)
        return;
    
    my_name = caster->query_cap_name();
    att_name = attacker->query_cap_name();
    my_poss = caster->query_possessive();
    att_poss = attacker->query_possessive();
    level = caster->query_class_level("oracle");
    attackers = caster->query_attackers();
    place = environment(caster);
    bonus = COMBAT_D->unarmed_enchantment(caster) + max( ({ BONUS_D->query_stat_bonus(caster, "strength"), BONUS_D->query_stat_bonus(caster, "dexterity") }) );
    
    
    //CLAW ATTACK
    if(attacker && thaco(target, bonus))
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
            tell_object(attacker, "%^RESET%^%^CRST%^%^C255%^Tal%^C252%^o%^C255%^n%^C252%^s %^C125%^outpsread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at you and %^C196%^gouges %^C125%^your flesh!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C255%^Tal%^C252%^o%^C255%^n%^C252%^s %^C125%^outpsread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^ and %^C196%^gouges %^C125%^your flesh!%^CRST%^", ({ caster, attacker }));
            break;
        }
        
        dam = (roll_dice(1, 6) * (1 + flevel /  10)) + bonus;
        caster->cause_typed_damage(target,target->return_target_limb(),dam ,"piercing");    
    }
    
    if(level < 5)
        return;
    
    if(!objectp(caster))
        return;
    
    if(!caster->query("dragon_affinity"))
        return;
    
    attackers = caster->query_attackers();
    
    if(!sizeof(attackers))
        return;
    
    //BREATH ATTACK
    if(!random(5))
    {    
        switch(caster->query("dragon_affinity"))
        {
            case "black":
            case "copper":
            tell_object(caster, "%^GREEN%^BOLD%^You breath a gout of steaming acid at your enemies!%^RESET%^");
            tell_room(place, "%^GREEN%^BOLD%^" + my_name + " breathes a gout of steaming acid at their enemies!%^RESET%^");
            dam_type = "acid";
            break;
        
            case "blue":
            case "bronze":
            tell_object(caster, "%^YELLOW%^BOLD%^You breath great arcs of electricity at your enemies!%^RESET%^");
            tell_room(place, "%^YELLOW%^BOLD%^" + my_name + " breathes great arcs of electricity at their enemies!%^RESET%^");
            dam_type = "electricity";
            break;
        
            case "brass":
            case "red":
            case "gold":
            tell_object(caster, "%^RED%^BOLD%^You breath great gouts of flame at your enemies!%^RESET%^");
            tell_room(place, "%^YELLOW%^BOLD%^" + my_name + " breathes great gouts of flame at their enemies!%^RESET%^");
            dam_type = "fire";
            break;

            case "green":
            tell_object(caster, "%^GREEN%^You breath a cloud of poison at your enemies!%^RESET%^");
            tell_room(place, "%^GREEN%^" + my_name + " breathes a cloud of poison at their enemies!%^RESET%^");
            dam_type = "untyped";
            break;

            case "white":
            case "silver":
            tell_object(caster, "%^BLUE%^BOLD%^You breath sheets of ice and snow at your enemies!%^RESET%^");
            tell_room(place, "%^BLUE%^BOLD%^" + my_name + " breathes sheets of ice and snow at their enemies!%^RESET%^");
            dam_type = "cold";
            break;
        }
    
        dam = (roll_dice(1, 6) * (1 + flevel /  10));
    
        if(sizeof(attackers) > 6)
            attackers = attackers[0..6];
    
        foreach(object ob in attackers)
        {
            if(SAVING_THROW_D->reflex_save(ob, flevel + bonus))
            {
                tell_room(place, "%^BOLD%^" + ob->query_cap_name() + " scrambles out of the way of the breath!", ob);
                tell_object(ob, "%^BOLD%^You scramble out of the way of the breath!");
                ob->cause_typed_damage(ob, ob->return_target_limb(), dam / 2, dam_type);
            }
            else
            {
                ob->cause_typed_damage(ob, ob->return_target_limb(), dam, dam_type);
            }
        }
    }
    
    if(!objectp(caster))
        return;
    
    if(level < 21)
        return;
    
    attacker = caster->query_current_attacker();
    att_name = attacker->query_cap_name();
    
    if(objectp(attacker))
        return;
    
    //TAIL ATTACK
    switch(random(3))
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
    
    if(SAVING_THROW_D->reflex_save(attacker, flevel + bonus))
    {
        tell_room(place, "%^BOLD%^" + att_name + " avoids the tail swing!", attacker);
        tell_object(attacker, "You avoid the tail swing!");
    }
    else
    {
        attacker->set_tripped(roll_dice(1, 4) * 6, "%^BOLD%^You are struggling to get up!%^RESET%^");
        attacker->cause_typed_damage(attacker, "torso", dam, "bludgeoning");
    }
    
    return;
    
}


void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
