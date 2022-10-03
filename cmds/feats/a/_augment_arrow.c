/*
  _augment_arrow.c
  
  Infused ranged attacks with different types of additional effects.
  For Peerless Archer PRC.
  
  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>

#define VALID ({ "barbed", "crippling", "enervating", "blinding", "exploding" })
#define EXPLODE_BASE 6
#define DELAY 30

inherit FEAT;

string type;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("PeerlessArcher");
    feat_name("augment arrow");
    feat_prereq("Peerless Archer L7");
    feat_syntax("augment_arrow [TYPE]");
    feat_desc("With the feat, the Peerless Archer is able to fire an extra arrow at their target, each round, with a special type of arrow head. If the extra arrow hits the target, an extra effect will occur, as follows:

    %^CYAN%^BOLD%^Barbed     : %^RED%^Rend%^RESET%^
    %^CYAN%^BOLD%^Crippling  : %^WHITE%^Trip%^RESET%^
    %^CYAN%^BOLD%^Enervating : %^GREEN%^Fatigue%^RESET%^
    %^CYAN%^BOLD%^Blinding   : %^MAGENTA%^Blind%^RESET%^
    %^CYAN%^BOLD%^Exploding  : %^YELLOW%^Splash Fire and Piercing Damage.%^RESET%^

This is a toggle feat. Once it is active, you can deactivate it by typing %^BOLD%^<augment_arrow>%^RESET%^ once more.

N.B. This feat only works while wielding a bow.");
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if (!objectp(ob))
    {
        return 0;
    }

    if ((int)ob->query_class_level("peerless_archer") < 7)
    {
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_augment_arrow(string str)
{
    object feat;
    if (!objectp(this_player()))
    {
        return 0;
    }
    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);
    return 1;
}

void execute_feat()
{
    object ob;
    
    ::execute_feat();
    
    place = environment(caster);
    
    if (caster->query_property("using instant feat"))
    {
        tell_object(caster, "%^BOLD%^You are already in the middle of using a feat.%^RESET%^");
        dest_effect();
        return;
    }
    
    if(ob = query_active_feat("augment arrow"))
    {
        tell_object(caster, "%^MAGENTA%^You put away your specialized arrows and will no longer use them.%^RESET%^");
        ob->dest_effect();
        dest_effect();
        return;
    }
    
    if(!arg || !strlen(arg) || member_array(arg, VALID) < 0)
    {
        tell_object(caster, "%^CYAN%^You must select a valid augmentation type. Valid choices are : %^YELLOW%^" + implode(VALID, ", ") + ".%^RESET%^");
        dest_effect();
        return;
    }
    
    if(caster->cooldown("augment arrow"))
    {
        tell_object(caster, "You can't augment your arrows yet.");
        dest_effect();
        return;
    }
    
    //These will become far more stylized descriptions
    switch(arg)
    {       
        case "barbed":
        tell_object(caster, "%^C246%^You attach a %^C160%^wicked-looking%^C246%^ %^C249%^b%^C251%^a%^C253%^r%^C255%^b%^C249%^ed head%^C246%^ to some of your arrows and place them in your quiver.%^CRST%^");
        break;
        case "crippling":
        tell_object(caster, "%^C246%^You attach a %^C172%^strange-looking%^C246%^ %^C190%^crippling head%^C246%^ to some of your arrows and place them in your quiver.%^CRST%^");
        break;
        case "enervating":
        tell_object(caster, "%^C246%^You attach a %^C112%^sickly-looking%^C246%^ %^C100%^enervating head%^C246%^ to some of your arrows and place them in your quiver.%^CRST%^");
        break;
        case "blinding":
        tell_object(caster, "%^C246%^You attach a %^C098%^violet-hued%^C246%^ %^C116%^blinding head%^C246%^ to some of your arrows and place them in your quiver.%^CRST%^");
        break;
        case "exploding":
        tell_object(caster, "%^C246%^You attach an %^C166%^i%^C172%^n%^C178%^c%^C184%^e%^C178%^n%^C172%^di%^C166%^ary%^C246%^ %^C196%^exploding head%^C246%^ to some of your arrows and place them in your quiver.%^CRST%^");
        break;
    }
    
    type = arg;
    
    caster->add_cooldown("augment arrow", 30);
    caster->set_property("active_feats", ({ this_object() }));
    return;
}

void execute_attack()
{
    int limit, affected, bonus, result, dam;
    string my_name, your_name, my_poss, your_poss, your_obj;
    object weapons;
    
    object attacker, *attackers;
    
    ::execute_attack();
    
    if(!strlen(type))
    {
        dest_effect();
        return;
    }
    
    if(!objectp(caster) || !objectp(place))
    {
        dest_effect();
        return;
    }
    
    place = environment(caster);
    
    if (caster->query_ghost() || caster->query_unconscious())
    {
        reset_attack_cycle();
        return;
    }

    if(caster->query_bound() || caster->query_paralyzed())
    {
        reset_attack_cycle();
        return;
    }
    
    if(!attacker = caster->query_current_attacker())
    {
        reset_attack_cycle();
        return;
    }
    
    weapons = caster->query_wielded();
    
    if(!weapons || !pointerp(weapons) || !sizeof(weapons) || member_array("bow", weapons[0]->query_id()) < 0)
    {
        tell_object(caster, "You need a bow to use augment arrow!");
        reset_attack_cycle();
        return;
    }
    
    attackers = caster->query_attackers() - ({ attacker });
    affected = roll_dice(1, 6) + 2;
    
    if(sizeof(attackers) > affected)
        attackers = attackers[0..affected];
    
    my_name = caster->query_cap_name();
    your_name = attacker->query_cap_name();
    my_poss = caster->query_possessive();
    your_poss = attacker->query_possessive();
    your_obj = attacker->query_objective();
    
    result = BONUS_D->process_hit(caster, attacker, 1, weapons[0], 0, 0);
    
    if(result <= 0)
    {
        tell_object(caster, "%^YELLOW%^You fire a %^CYAN%^" + type + "%^YELLOW%^ arrow at " + your_name + ", but miss!%^RESET%^");
        tell_object(attacker, "%^YELLOW%^" + my_name + " fires a %^CYAN%^" + type + "%^YELLOW%^ arrow at you, but miss!%^RESET%^");
        tell_room(place, "%^YELLOW%^" + my_name + " fires a %^CYAN%^" + type + "%^YELLOW%^ arrow at " + your_name + ", but misses!%^RESET%^", ({ caster, attacker }));
        reset_attack_cycle();
        return;
    }
    
    dam = weapons[0]->query_wc();
    bonus = COMBAT_D->get_lrdamage(caster, weapons[0], attacker);
    dam += BONUS_D->new_damage_bonus(caster, caster->query_stats("dexterity"));
    dam += weapons[0]->query_property("enchantment");
    dam += bonus;   
    dam = COMBAT_D->damage_done(caster, weapons[0], dam, 1);
    
    caster->cause_typed_damage(attacker,attacker->return_target_limb(),dam ,"piercing");
    
    if(!objectp(caster) || !objectp(attacker))
    {
        reset_attack_cycle();
        return;
    }
    
    switch(type)
    {
        case "barbed":
        tell_object(caster, "%^C246%^You fire a %^C166%^barbed arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, causing %^C160%^massive bleeding%^C246%^!%^CRST%^");
        tell_object(attacker, "%^C246%^" + my_name + " fires a %^C166%^barbed arrow%^C246%^ into %^C195%^you%^C246%^, causing %^C160%^massive bleeding%^C246%^!%^CRST%^");
        tell_room(place, "%^C246%^" + my_name + " fires a %^C166%^barbed arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, causing %^C160%^massive bleeding%^C246%^!%^CRST%^", ({ caster, attacker }));
        attacker->set_property("rend", 1 + flevel / 16);
        break;
        case "crippling":
        tell_object(caster, "%^C246%^You fire a %^C103%^crippling arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, causing %^C195%^" + your_obj + "%^C246%^ to trip!%^CRST%^");
        tell_object(attacker, "%^C246%^" + my_name + " fires a %^C103%^crippling arrow%^C246%^ into %^C195%^you%^C246%^, causing %^C195%^you%^C246%^ to trip!%^CRST%^");
        tell_room(place, "%^C246%^" + my_name + " fires a %^C103%^crippling arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, causing %^C195%^" + your_obj + "%^C246%^ to trip!%^CRST%^", ({ caster, attacker }) );
        attacker->set_tripped(1);
        break;
        case "enervating":
        tell_object(caster, "%^C246%^You fire an %^C137%^enervating arrow%^C146%^ %^C246%^into %^C195%^" + your_name + "%^C246%^, fatiguing %^C195%^" + your_obj + "%^C246%^!%^CRST%^");
        tell_object(attacker, "%^C246%^" + my_name + " fires an %^C137%^enervating arrow%^C146%^ %^C246%^into %^C195%^you%^C246%^, fatiguing %^C195%^you%^C246%^!%^CRST%^");
        tell_room(place, "%^C246%^" + my_name + " fires an %^C137%^enervating arrow%^C146%^ %^C246%^into %^C195%^" + your_name + "%^C246%^, fatiguing %^C195%^" + your_obj + "%^C246%^!%^CRST%^", ({ caster, attacker }));
        "/std/effect/status/fatigued"->apply_effect(target, 1);
        break;
        case "blinding":
        tell_object(caster, "%^C246%^You fire a %^C190%^blinding arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, rendering %^C195%^" + your_obj + "%^C246%^ sightless!%^CRST%^");
        tell_object(attacker, "%^C246%^" + my_name + " fires a %^C190%^blinding arrow%^C246%^ into %^C195%^you%^C246%^, rendering %^C195%^you%^C246%^ sightless!%^CRST%^");
        tell_room(place, "%^C246%^" + my_name + " fires a %^C190%^blinding arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, rendering %^C195%^you%^C246%^ sightless!%^CRST%^", ({ attacker, caster }));
        attacker->set_temporary_blinded(flevel + bonus);
        break;
        case "exploding":
        tell_object(caster, "%^C246%^You fire an %^C202%^exploding arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, exploding into a shower of sparks!%^CRST%^");
        tell_object(attacker, "%^C246%^" + my_name + " fires an %^C202%^exploding arrow%^C246%^ into %^C195%^you%^C246%^, exploding into a shower of sparks!%^CRST%^");
        tell_room(place, "%^C246%^" + my_name + " fires an %^C202%^exploding arrow%^C246%^ into %^C195%^" + your_name + "%^C246%^, exploding into a shower of sparks!%^CRST%^", ({ attacker, caster }));
        foreach(object ob in attackers)
        {
            tell_room(place, "%^C202%^" + ob->query_cap_name() + " is caught in the blast!%^CRST%^", ob);
            tell_object(ob, "%^C202%^You are caught in the blast!%^CRST%^", ob);
            ob->cause_typed_damage(ob, ob->return_target_limb(), dam / 2, "fire");
        }
        break;
    }
          
    reset_attack_cycle();
}

void reset_attack_cycle()
{
    if (objectp(place))
    {
        place->addObjectToCombatCycle(this_object(), 1);
    }
    else
    {
        dest_effect();
    }
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(this_object());
    return;
}
    