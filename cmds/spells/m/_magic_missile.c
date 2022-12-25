/*
  _magic_missile.c
  
  Completely rewritten to scale with number of darts. Should be a signature mage spell.
  
  -- Tlaloc --
*/

#include <spell.h>
#include <daemons.h>

inherit SPELL;

create()
{
    ::create();
    set_spell_name("magic missile");
    set_spell_level( ([ "mage" : 1, "magus" : 1 ]) );
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS magic missile on [TARGET]");
    set_damage_desc("force damage per missile. 1 missile + clevel / 6 additional missiles.");
    set_description("A signature spell of any would-be mage, magic missile forms glowing magical darts which cause force damage to the target. Every six caster levels, the mage can fire an additional missile which can hit additional targets. This spell gains damage with each additional missile and so scales far more than other level 1 spells. This spell always hits its target and does not require any ranged attack rolls or saving throws. This spell, however, is completely thwarted if the target has a shield spell active. If the caster specifies a target, then the target will get with with all of the missiles, otherwise, the missiles will hit different targets.");
    set_verbal_comp();
    set_somatic_comp();
    //set_target_required(1);
}

string query_cast_string()
{
    return "%^RESET%^%^CRST%^%^C032%^"+caster->query_cap_name()+" draws an %^C039%^a%^C045%^r%^C051%^ca%^C045%^n%^C039%^e s%^C045%^y%^C051%^mb%^C045%^o%^C039%^l %^C032%^in the air and a %^C220%^gl%^C226%^owi%^C220%^ng d%^C226%^ar%^C220%^t %^RESET%^%^C032%^begins to form.%^CRST%^";
}

void spell_effect(int prof)
{
    object *victims;
    int num, multi, scale;
    string t_name, c_name, t_obj, miss_str, verb_str;
    
    if(!objectp(caster))
        return;
    
    if(!target)
        victims = caster->query_attackers();
    else
        victims = ({ target });
    
    if(!sizeof(victims))
    {
        tell_object(caster, "Your target is not here.");
        dest_effect();
        return;
    }
    
    if(caster->query_property("empower spell"))
    {
        caster->remove_property("empower spell");
        ::spell_effect();
        caster->set_property("empower spell", 1);
    }
    else if(caster->query_property("maximize spell"))
    {
        caster->remove_property("maximize spell");
        ::spell_effect();
        caster->set_property("maximize spell", 1);
    }
    else
    {
        ::spell_effect();
    }
    
    num = 1 + (clevel / 6);
    
    //tell_object(caster, "Number of darts : " + num);
    //tell_object(caster, "Number of opponents : " + sizeof(victims));
    
    if(sizeof(victims) > num)
        victims = victims[0..(num - 1)];
    else if(num > sizeof(victims))
        multi = 1;
    
    miss_str = multi ? "%^C220%^mi%^C226%^ssil%^C220%^es%^C032%^" : "%^C220%^mi%^C226%^ssi%^C220%^le%^C032%^";
    verb_str = multi ? "%^C020%^slam%^C032%^" : "%^C020%^slams%^C032%^";

    c_name = caster->query_cap_name();
    
    //Adjusts spell damage formula to scale for number of darts.
    
    if(query_spell_type() == "mage" || query_spell_type() == "sorcerer")
        define_base_damage(max( ({ 0, min( ({ num - 1, 8 }) ) })));
    else
        define_base_damage(max( ({ 0, min( ({ num - 1, 5 }) ) })));        
    
    //tell_object(caster, "Damage per dart : " + sdamage);
    
    tell_object(caster, "%^RESET%^%^CRST%^%^C032%^" + sprintf("You motion with your hands and %smagical %s %s towards your %s.", num > 1 ? "" : "a ", num > 1 ? "missiles" : "missile", num > 1 ? "%^C032%^speed" : "%^C032%^speeds", sizeof(victims) > 1 ? "targets" : "target") + "%^CRST%^");
    tell_room(caster, "%^RESET%^%^CRST%^%^C032%^" + sprintf("%s motions with %s hands and %smagical %s %s towards %s %s.", c_name, caster->query_possessive(), num > 1 ? "" : "a ", miss_str, multi ? "%^C032%^speed" : "%^C032%^speeds", caster->query_possessive(), multi ? "targets" : "target") + "%^CRST%^", ({ caster }));
    
    foreach(object ob in victims)
    {
        if(!objectp(caster))
        {
            dest_effect();
            return;
        }
        
        spell_kill(ob, caster);
        
        if(objectp(ob) && ob->query_property("spell shield"))
        {
            tell_object(caster, "%^RESET%^%^CRST%^%^C051%^Your missile is absorbed by "+ob->query_cap_name()+"%^RESET%^%^CRST%^%^C051%^'s magical shield!%^CRST%^");
            tell_object(ob, "%^RESET%^%^CRST%^%^C051%^The missile is absorbed by your magical shield!%^CRST%^");
            tell_room(place, "%^RESET%^%^CRST%^%^C051%^The missile is absorbed by "+ob->query_cap_name()+"%^RESET%^%^CRST%^%^C051%^'s magical shield!%^CRST%^", ob);
            continue;
        }
        
        if(!objectp(ob) || !objectp(caster))
            continue;
        
        tell_object(caster, "%^RESET%^%^CRST%^%^C032%^" + sprintf("Your %s %s into %s with arcane force!", miss_str, verb_str, ob->query_cap_name() + "%^RESET%^%^CRST%^%^C032%^") + "%^CRST%^");
        tell_object(ob, "%^RESET%^%^CRST%^%^C032%^" + sprintf("The %s %s into you with arcane force!", miss_str, verb_str) + "%^CRST%^");
        tell_room(place, "%^RESET%^%^CRST%^%^C032%^" + sprintf("The %s %s into %s with arcane force!", miss_str, verb_str, ob->query_cap_name() + "%^RESET%^%^CRST%^%^C032%^") + "%^CRST%^", ({ ob, caster }));
        //tell_object(caster, "Total damage : " + ((sdamage * num) / sizeof(victims)));
        ob->cause_typed_damage(ob, "torso", sdamage / sizeof(victims), "force");
    }
    
    dest_effect();
    return;
}
        
/*  

//Previous version below

// Magic Missile
// Updated 11/23/07 by Circe to not show number of missiles
// based on a suggestion by a player, Catherine
// removed interactive query so monsters are not showing number of missiles cast. Nienne, 09/08.
#include <spell.h>

inherit SPELL;

create() {
    ::create();
    set_spell_name("magic missile");
    set_spell_level(([ "mage" : 1, "magus" : 1 ]));
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS magic missile on TARGET");
    set_damage_desc("force");
    set_description("Magic missile will shoot darts of magical energy from your hand and they will fly towards your "
"target with the unfailing ability to hit it.  The damage it causes increases by level.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
}

spell_effect(int prof) {
    int num, numdarts;
    string hardness, mynum;

    spell_successful();
    if (interactive(caster)) {
        tell_object(caster,"%^YELLOW%^You point the palm of your hand at "+target->QCN+"!");
        tell_object(target,"%^YELLOW%^"+caster->QCN+" points the palm of "+caster->QP+" hand at you!");
        tell_room(place,"%^YELLOW%^"+caster->QCN+" points the palm of "+caster->QP+" hand at "+target->QCN+"!", ({caster, target}) );
    }
    if(target->query_property("spell shield")) {
        tell_object(caster,"%^YELLOW%^Darts of energy burst forth from your hand and fizzle harmlessly upon "
+target->QCN+"'s magical shield!");
        tell_object(target,"%^YELLOW%^Darts of energy burst forth from "+caster->QCN+"'s hand and fizzle harmlessly upon "
"your magical shield!");
        tell_room(place,"%^YELLOW%^Darts of energy burst forth from "+caster->QCN+"'s hand and fizzle harmlessly upon "
+target->QCN+"'s magical shield!", ({caster, target}) );
        TO->dest_effect();
        return;
    }
    if (CLEVEL)
        numdarts=to_int((CLEVEL+1)/2);
    else 
        numdarts=to_int(((int)caster->query_guild_level("mage")+1)/2);

    switch (1+to_int(sdamage/numdarts)) {
    case 2:
        hardness="sting";
        break;
    case 3:
        hardness="shock";
        break;
    case 4:
        hardness="zap";
        break;
    default:
        hardness="blast";
        break;
    }
//    if (interactive(caster)) {
        if (numdarts > 1) {
           switch(numdarts){
              case 2..5:  mynum = "A few";
                          break;
              case 6..10:  mynum = "Many";
                           break;
              case 11..15: mynum = "A small swarm of";
                           break;
              default:  mynum = "A teeming legion of";
                        break;
           }
            tell_object(caster,"%^BOLD%^%^RED%^"+mynum+" ethereal darts shoot from your hand and "+hardness+" "+target->QCN+"!");
            tell_object(target,"%^BOLD%^%^RED%^"+mynum+" ethereal darts shoot from "+caster->QCN+"'s hand and "+hardness+" you!");
            tell_room(place,"%^BOLD%^%^RED%^"+mynum+
                      " ethereal darts shoot from "+caster->QCN+"'s hand and "+hardness+" "+target->QCN+"!",({caster, target}) );
        } else {
            tell_object(caster,"%^BOLD%^%^RED%^A dart of energy shoots from your hand and "+hardness+"s "+target->QO+"!");
            tell_object(target,"%^BOLD%^%^RED%^A dart of energy shoots from "+caster->QCN+"'s hand and "+hardness+"s you!");
            tell_room(place,"%^BOLD%^%^RED%^A dart of energy shoots from "+caster->QCN+"'s hand and "+hardness+"s "+target->QO+"!",({caster, target}) );
        }
    damage_targ(target, target->return_target_limb(), sdamage,"force");
    spell_successful();
    dest_effect();
    return;
}

*/

void dest_effect()
{
    ::dest_effect();
    if(objectp(this_object()))
        this_object()->remove();
}
