#include <std.h>
#include <daemons.h>
#include <dirs.h>
#include <magic.h>

inherit FEAT;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("Presence");
    feat_name("claw and tooth");
    feat_syntax("claw_and_tooth");
    feat_classes("oracle");
    feat_desc("");
    allow_tripped(1);
}

int allow_shifted()
{
    return 1;
}

int cmd_claw_and_tooth(string str)
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
    
    if(ob->query_mystery() != "lunar")
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

    if (FEATS_D->is_active(caster, "claw and tooth")) {
        obj = query_active_feat("claw and tooth");
        obj->dest_effect();
        
        tell_object(caster, "%^CYAN%^You let go of your primal instincts and return to normal.");
        
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
        tell_object(caster, "%^BOLD%^You can't do that while you're casting a spell.%^RESET%^");
        dest_effect();
        return;
    }
    
    tell_object(caster, "%^YELLOW%^You howl and call upon the power of the moon, taking on a primal aspect.");
    tell_object(caster, "%^RED%^BOLD%^Your fingers extend into razor-sharp claws!");
    tell_object(caster, "%^RED%^BOLD%^Your teeth extend into insidious fangs!");
        
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
            tell_object(caster, "%^RESET%^%^CRST%^%^C255%^Cl%^C252%^a%^C255%^w%^C252%^s %^C125%^outspread, you %^C196%^lunge %^C125%^at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^ and %^C196%^gouge %^C125%^their flesh!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C255%^Cl%^C252%^a%^C255%^w%^C252%^s %^C125%^outspread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at you and %^C196%^gouges %^C125%^your flesh!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C255%^Cl%^C252%^a%^C255%^w%^C252%^s %^C125%^outspread, %^CRST%^" + my_name + "%^RESET%^%^CRST%^%^C196%^ lunges %^C125%^at %^CRST%^" + att_name + "%^RESET%^%^CRST%^%^C125%^ and %^C196%^gouges %^C125%^their flesh!%^CRST%^", ({ caster, attacker }));
            break;
        }
        
        dam = (roll_dice(1, 6) * (1 + flevel /  10)) + bonus;
        caster->cause_typed_damage(attacker,attacker->return_target_limb(),dam ,"piercing");    
    }
    
    //BITE ATTACK
    if(attacker && thaco(attacker, bonus))
    {
        switch(random(3))
        {
            case 0:
            tell_object(caster, "%^RESET%^%^CRST%^%^C100%^You dart forward, sinking your %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^ deep into "+att_name+"'s flesh!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C100%^"+my_name+"%^RESET%^%^CRST%^%^C100%^ darts forward, sinking their %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^ deep into your flesh!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C100%^"+my_name+"%^RESET%^%^CRST%^%^C100%^ darts forward, sinking their %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^ deep into "+att_name+"'s flesh!%^CRST%^", ({ caster, attacker }));
            break;
            
            case 1:
            tell_object(caster, "%^RESET%^%^CRST%^%^C100%^Biting down on "+att_name+"%^RESET%^%^CRST%^%^C100%^, you give a %^C124%^savage %^C196%^shake%^RESET%^%^C100%^ and rip out a chunk of meat!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C100%^Biting down on you, "+my_name+"%^RESET%^%^CRST%^%^C100%^ gives a %^C124%^savage %^C196%^shake%^RESET%^%^C100%^ and rips out a chunk of meat!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C100%^Biting down on "+att_name+"%^RESET%^%^CRST%^%^C100%^, "+my_name+"%^RESET%^%^CRST%^%^C100%^ gives a %^C124%^savage %^C196%^shake%^RESET%^%^C100%^ and rips out a chunk of meat!%^CRST%^", ({ caster, attacker }));
            break;
            
            default:
            tell_object(caster, "%^RESET%^%^CRST%^%^C100%^You tear into "+att_name+"%^RESET%^%^CRST%^%^C100%^ with your %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^, spurred on by the taste of %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C255%^!%^CRST%^");
            tell_object(attacker, "%^RESET%^%^CRST%^%^C100%^"+my_name+"%^RESET%^%^CRST%^%^C100%^ tears into you with their %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^, spurred on by the taste of %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C255%^!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C100%^"+my_name+"%^RESET%^%^CRST%^%^C100%^ tears into "+att_name+"%^RESET%^%^CRST%^%^C100%^ with their %^C255%^te%^C250%^e%^C255%^t%^C250%^h%^RESET%^%^C100%^, spurred on by the taste of %^C196%^bl%^C124%^o%^C196%^o%^C124%^d%^C255%^!%^CRST%^", ({ caster, attacker }));
            break;
        }
        
        dam = (roll_dice(1, 6) * (1 + flevel /  10)) + bonus;
        caster->cause_typed_damage(attacker,attacker->return_target_limb(),dam ,"piercing");    
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
