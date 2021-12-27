#include <std.h>
#include <daemons.h>
#include <magic.h>
inherit FEAT;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("KiOffense");
    feat_name("quivering palm");
    feat_syntax("quivering_palm [TARGET]");
    feat_prereq("Monk L17, Way of The Fist or Grandmaster of The Way");
    feat_classes("monk");
    feat_desc("A monk specialized in the way of the fist, that is unarmored and unarmed, or wielding small weapons, may attempt a quivering palm attack on a target. In order for the attempt to be successful the monk must have at least 3 available Ki and must land a touch attack on the target. If successful a brief period of time later the target must roll a successful fortitude saving throw or be set to 0 health. Against certain monsters or if the saving throw is successful the target will take 1d8 damage per monk level.

If used without an argument this feat will pick up a random attacker.");
    set_save("fortitude");
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) return 0;
    if((int)ob->query_class_level("monk") < 17)
    {
        dest_effect();
        return 0;
    }
    if((string)ob->query("monk way") != "way of the fist" && !FEATS_D->usable_feat(ob, "grandmaster of the way"))
    {
        dest_effect();
        return 0;
    }
    if((int)ob->query_alignment() > 3)
    {

        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_quivering_palm(string str)
{
    object feat;
    if(!objectp(TP)) return 0;
    if((string)TP->query("monk way") != "way of the fist" && !FEATS_D->usable_feat(TP, "grandmaster of the way")) return 0;
    feat = new(base_name(TO));
    feat->setup_feat(TP,str);
    return 1;
}

int check_can_use()
{
    object *weapons;
    int x;
    if(!objectp(caster)) return 0;
    weapons = caster->query_wielded();
    for(x = 0;x < sizeof(weapons);x++)
    {
        if(!objectp(weapons[x])) continue;
        if((int)weapons[x]->query_size() > 1)
        {
            tell_object(caster, "%^BOLD%^%^GREEN%^Your "+weapons[x]->query_short()+
            " interferes with your quivering palm attempt!%^RESET%^");
            return 0;
        }
        continue;
    }
    if(!caster->is_ok_armour("barb"))
    {
        tell_object(caster, "%^BOLD%^%^GREEN%^Your armor interferes "+
        "with your quivering palm attempt!%^RESET%^");
        return 0;
    }
    if(caster->query_in_vehicle())
    {
        tell_object(caster,"You cannot use quivering palm while mounted!");
        return 0;
    }
    if(!(int)USER_D->can_spend_ki(caster, 3))
    {
        tell_object(caster, "%^CYAN%^You lack the needed ki to attempt "+
        "quivering palm.%^RESET%^");
        return 0;
    }
    return 1;
}

void execute_feat()
{
    mapping tempmap;
    int x;
    int damage, timerz, i, bonusdc;
    object *keyz, qob;
    ::execute_feat();

    tempmap = caster->query_property("using quivering palm");
    if (!objectp(target)) {
        object* attackers = caster->query_attackers();
        if (mapp(tempmap)) {
            attackers = filter_array(attackers, (: $2[$1] < time() :), tempmap);
        }
        if (!sizeof(attackers)) {
            tell_object(caster, "%^BOLD%^Nobody to hit.%^RESET%^");
            dest_effect();
            return;
        }
        target = attackers[random(sizeof(attackers))];
    }
    if (!objectp(caster)) {
        dest_effect();
        return;
    }
    if (caster->query_bound() || caster->query_tripped() || caster->query_paralyzed()) {
        caster->send_paralyzed_message("info", caster);
        dest_effect();
        return;
    }
    if ((int)caster->query_property("using instant feat")) {
        tell_object(caster, "You are already in the middle of using a feat!");
        dest_effect();
        return;
    }
    if (caster->query_casting()) {
        tell_object(caster, "%^BOLD%^You are already in the middle of casting a spell.%^RESET%^");
        dest_effect();
        return;
    }
    if (target == caster) {
        tell_object(caster, "There are better ways to kill yourself!");
        dest_effect();
        return;
    }
    if (!objectp(target)) {
        tell_object(caster, "That is not here!");
        dest_effect();
        return;
    }
    if (!present(target, place)) {
        tell_object(caster, "That is not here!");
        dest_effect();
        return;
    }
    if(!caster->spend_ki(3))
    {
        tell_object(caster, "%^CYAN%^You lack the needed ki to attempt "+
        "quivering palm!%^RESET%^");
        dest_effect();
        return;
    }
	
    if (mapp(tempmap)) {
        if (tempmap[target] > time()) {
            tell_object(caster, "The target is still cannot be impacted by that yet!");
            dest_effect();
            return;
        }
    }

    caster->set_property("using instant feat",1);

    tell_object(caster, "%^BOLD%^%^CYAN%^You focus intently on manipulating the ki in "+
    target->QCN+"%^BOLD%^%^CYAN%^'s body!%^RESET%^");

    tell_object(target, caster->QCN+"%^BOLD%^%^CYAN%^ begins focusing intently on "+
    "you!%^RESET%^");
    
    if (!mapp(tempmap)) {
        tempmap = ([]);
    }
    if (tempmap[target]) {
        map_delete(tempmap, target);
    }
    keyz = keys(tempmap);
    for (i = 0; i < sizeof(keyz); i++) {
        if (!objectp(keyz[i])) {
            map_delete(tempmap, keyz[i]);
        }
        continue;
    }
    timerz = time() + 120;
    delay_subject_msg(target,120,"%^BOLD%^%^WHITE%^"+target->QCN+" can be hit with %^CYAN%^quivering palm%^WHITE%^ again.%^RESET%^");
    tempmap += ([ target : timerz ]);
    caster->remove_property("using quivering palm");
    caster->set_property("using quivering palm",tempmap);

    tell_object(caster, "%^BOLD%^%^CYAN%^You slam your palm into "+
    target->QCN+" 's chest!%^RESET%^");
    tell_object(target, caster->QCN+"%^BOLD%^%^RED%^ drives their fist into your chest and your body begins violently vibrating!!!%^RESET%^");
	tell_room(place, "%^BOLD%^%^RED%^You see " + target->QCN + "'s body begin violently vibrating!", ({ target, caster }));

    bonusdc = BONUS_D->query_stat_bonus(caster, "wisdom");

    spell_kill(target, caster);
    if (target->query_property("no death") ||
        target->is_undead() ||
        do_save(target, bonusdc)) {
        int todamage;
        tell_object(target, "%^BOLD%^%^BLACK%^An excrutiating %^BOLD%^%^RED%^PAIN"+
        "%^BOLD%^%^BLACK%^ radiates throughout your entire body and "+
        "you %^GREEN%^S%^BOLD%^%^BLACK%^H%^GREEN%^"+
        "R%^BOLD%^%^BLACK%^I%^GREEN%^E%^BOLD%^%^BLACK%^K as "+
        "the vibrations finally stop!%^RESET%^");
		
		tell_room(place, "%^BOLD%^%^WHITE%^You see " + target->QCN + " %^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^H%^BOLD%^%^GREEN%^"+
            "R%^BOLD%^%^BLACK%^I%^BOLD%^%^GREEN%^E%^BOLD%^%^BLACK%^K%^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^ in "+
            "%^BOLD%^%^RED%^PAIN%^BOLD%^%^BLACK%^ suddenly as the vibrations "+
            "in " + target->QCN + "'s body finally stop!%^RESET%^", ({ target, caster }));
		
		tell_object(caster, "%^BOLD%^%^WHITE%^You see " + target->QCN + " %^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^H%^BOLD%^%^GREEN%^"+
            "R%^BOLD%^%^BLACK%^I%^BOLD%^%^GREEN%^E%^BOLD%^%^BLACK%^K%^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^ in "+
            "%^BOLD%^%^RED%^PAIN%^BOLD%^%^BLACK%^ suddenly as the vibrations "+
            "in " + target->QCN + "'s body finally stop!%^RESET%^", ({ target, caster }));
			
        if (target->query_max_hp() < caster->query_max_hp()) {
            todamage = roll_dice(flevel, 10);
        } else{
            todamage = roll_dice(flevel + BONUS_D->query_stat_bonus(caster, "wisdom"), 10);
        }
        target->cause_typed_damage(target, target->return_target_limb(), todamage, "divine");
    } else {
        tell_object(target, "%^BOLD%^%^BLACK%^An excrutiating %^BOLD%^%^RED%^PAIN"+
        "%^BOLD%^%^BLACK%^ radiates throughout your entire body and "+
        "you %^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^H%^BOLD%^%^GREEN%^"+
        "R%^BOLD%^%^BLACK%^I%^BOLD%^%^GREEN%^E%^BOLD%^%^BLACK%^K%^BOLD%^%^BLACK%^ as "+
        "you collapse in a heap!%^RESET%^");
        
		tell_room(place, "%^BOLD%^%^WHITE%^You see " + target->QCN + " %^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^H%^BOLD%^%^GREEN%^"+
            "R%^BOLD%^%^BLACK%^I%^BOLD%^%^GREEN%^E%^BOLD%^%^BLACK%^K%^BOLD%^%^GREEN%^S in "+
            "%^BOLD%^%^RED%^PAIN%^BOLD%^%^BLACK%^ suddenly before collapsing in "+
            "a heap!%^RESET%^", ({ target, caster }));
		
		tell_object(caster, "%^BOLD%^%^WHITE%^You see " + target->QCN + " %^BOLD%^%^GREEN%^S%^BOLD%^%^BLACK%^H%^BOLD%^%^GREEN%^"+
            "R%^BOLD%^%^BLACK%^I%^BOLD%^%^GREEN%^E%^BOLD%^%^BLACK%^K%^BOLD%^%^GREEN%^S in "+
            "%^BOLD%^%^RED%^PAIN%^BOLD%^%^BLACK%^ suddenly before collapsing in "+
            "a heap!%^RESET%^", ({ target, caster }));
			
		target->cause_typed_damage(target, target->return_target_limb(), target->query_max_hp() * 2, "divine");
    }
    spell_kill(target,caster);
    return;
}

void execute_attack()
{
    if (!objectp(caster)) {
        dest_effect();
        return;
    }
    ::execute_attack();

    caster->remove_property("using instant feat");
    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
