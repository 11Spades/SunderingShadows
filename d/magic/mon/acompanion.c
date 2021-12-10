/*
  acompanion.c

  Animal companion for rangers. Will be fleshed
  out more over time.

  -- Tlaloc --
*/

inherit WEAPONLESS;

#include <daemons.h>
#include "/d/magic/mon/summoned_monster.h"

#define SAVEDIR "/d/save/summons/" + owner->query_name() + "/animal/"

object owner;
object tp;



void timer(object tp);

string saved_short,
       saved_long;

int setup,
    bonus;

int set_owner(object ob) { owner = ob; return 1; }
object query_owner()     { return owner; }

void create(){
    ::create();
    set_name("companion");
    set_id(({"companion", "greater summon"}));
    set_short("A generic animal companion");
    set_hd(4,1);
    set_hp(40);
    set_exp(1);
    set_damage(2, 6);
    set_size(2);
    set_gender("neuter");
    //set_funcs( ({ "special_attack" }) );
    //set_func_chance(35);
}

void init()
{
    ::init();

    if(this_player() != owner)
        return;

    saved_short = read_file(SAVEDIR + "short");
    saved_long = read_file(SAVEDIR + "long");

    //Used read_file here - don't want to save whole object for 2 variables
    if(!strlen(saved_short) && !strlen(saved_long))
    {
        mkdir("/d/save/summons/" + this_player()->query_name());
        mkdir(SAVEDIR);
    }
    else
    {
        set_short(saved_short);
        set_long(saved_long);
    }

    add_action("animal_command", "animal");
	add_action("sic", "sic");
}

int sic(string str) {

 string tname, aname, mess;
 object room, target;

  if(!str) {
    write("What would you like your pet to attack!");
    return 1;
  }

str = lower_case(str);
target = present(str, environment(this_player()));

    if(!target || !objectp(target))
        return;

    tname = target->query_name();
    aname = capitalize(this_object()->query_name());
    room = environment(this_object());

    if(environment(target) != room)
        return;

   if ((int)target->query_property("using sic") > time()) {
        tell_object(owner, "You can't try to knock someone down yet!");
        dest_effect();
        return 0;
    }
  force_me("kill "+str);
  tell_room(room, "%^BOLD%^" + sprintf("%s responds to the whistle and leaps into the air, knocking %s to the ground!", aname, tname));
            target && target->set_tripped(3, "%^WHITE%^You are struggling to regain your footing! %^RESET%^");
                delay_msg(30,"%^BOLD%^%^WHITE%^You can %^CYAN%^sic%^WHITE%^ again.%^RESET%^");
                target()->set_property("using sic",time() + 30);
            timer(owner);
  return 1;
} 

	
int animal_command(string str)
{
    string *input;

    if(this_player() != owner)
        return 0;

    input = explode(str, " ");

    if(sizeof(input) < 1)
    {
        tell_object(this_player(), "Syntax : animal [long/short/follow].");
        return 1;
    }

    if(sizeof(input) < 2 && (input[0] == "long" || input[0] == "short"))
    {
        tell_object(this_player(), "Syntax : animal [long/short] [input].");
        return 1;
    }

    switch(input[0])
    {
        case "short":
        this_object()->set_short(implode(input[1..], " "));
        tell_object(this_player(), "Your Animal Companion will now be seen as: \n" + query_short());
        rm(SAVEDIR + "short");
        write_file(SAVEDIR + "short", implode(input[1..], " "));
        break;
        case "long":
        this_object()->set_long(implode(input[1..], " "));
        tell_object(this_player(), "Your Animal Companion will now be described as: " + query_long());
        rm(SAVEDIR + "long");
        write_file(SAVEDIR + "long", implode(input[1..], " "));
        break;
        case "command":
        command(implode(input[1..], " "));
        break;
        case "follow":
        tell_object(this_player(), "Your Animal Companion is now following you.");
        this_player()->add_follower(this_object());
        return 1;
        default:
        tell_object(this_player(), "Please select 'long', 'short', 'follow' or 'command' as options.");
        return 1;
        break;
    }

    return 1;
}


void heart_beat()
{

    object *attackers,
           room;

    ::heart_beat();

    room = environment(this_object());

    if(!room || !objectp(room))
        return;

    if(!objectp(owner) || owner->query_property("animal_companion") != this_object())
    {
        this_object()->remove();
        return;
    }

    //Faithful companion finds his master
    if(objectp(owner) && room != environment(owner))
    {
        this_object()->move(environment(owner));
        owner->add_follower(this_object());
    }

    //Companion hides if master is hiding
    if(!this_object()->query_invis())
    {
        if(owner->query_hidden() || owner->query_invis())
        {
            this_object()->set_invis(1);
            tell_object(owner, "Your animal companion fades into the shadows.");
        }
    }
    else
    {
        if(!owner->query_hidden() && !owner->query_invis())
            this_object()->set_invis(0);
    }

    attackers = owner->query_attackers();

    this_object()->add_damage_bonus(-bonus);
    this_object()->add_attack_bonus(-bonus);

    if(sizeof(attackers))
    {
        foreach(object ob in attackers)
            this_object()->kill_ob(ob);

        if(FEATS_D->usable_feat(owner, "hunters bond") &&
        owner->is_favored_enemy(this_object()->query_current_attacker()))
        {
            bonus = 2 + (FEATS_D->usable_feat(owner, "second favored enemy") * 2) + (FEATS_D->usable_feat(owner, "third favored enemy") * 2);
        }
        else
            bonus = 2;
    }
    else
    {
        add_hp(query_max_hp() / 20);
        bonus = 0;
    }

    if(query_hp() < query_max_hp() / 2 && present("vial", this_object()))
        command("drink vial");

    this_object()->add_damage_bonus(bonus);
    this_object()->add_attack_bonus(bonus);

    //Do the specials if the attacker is valid
    if(this_object()->query_current_attacker() && !random(3))
        special_attack(this_object()->query_current_attacker());
}

void special_attack(object target)
{
    string tname, aname, mess;
    object room;
    int scale;
    mapping attacks;

    if(!target || !objectp(target))
        return;

    tname = target->query_name();
    aname = capitalize(this_object()->query_name());
    room = environment(this_object());

    if(environment(target) != room)
        return;

    scale = 1 + this_object()->query_level() / 10;
    attacks = ([  ]);

    switch(query_name())
    {
        case "ape":
        case "badger":
        case "bear":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s claws %s twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 4)), "slashing" }) ]);
        break;
        case "bird":
        tell_room(room, "%^BOLD%^" + sprintf("%s swoops in and bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s claws %s with its talons twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 4)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 4)), "slashing" }) ]);
        break;
        case "boar":
        tell_room(room, "%^BOLD%^" + sprintf("%s gores %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        break;
        case "camel":
        tell_room(room, "%^BOLD%^" + sprintf("%s spits on %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "untyped" }) ]);
        if(!random(5))
            target && "/std/effect/status/sickened"->apply_effect(target,2);
        break;
        case "fox":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites and trips %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 4)), "piercing" }) ]);
        if(!random(5))
            target && target->set_tripped(1, "%^WHITE%^You are struggling to regain your footing! %^RESET%^");
        break;        
        case "lion":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s claws %s twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 8)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 6)), "slashing" }) ]);
        break;
        case "cheetah":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites and trips %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s claws %s twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 3)), "slashing" }) ]);
        if(!random(5))
            target && target->set_tripped(1, "%^WHITE%^You are struggling to regain your footing!%^RESET%^");
        break;
        case "crocodile":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s slaps %s with its tail.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 8)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(1, 12)), "bludgeoning" }) ]);
        break;
        case "dinosaur":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s claws %s twice.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s rakes %s with its talons twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 4)), "slashing" }) ]);
        attacks += ([ "three" : ({ (scale * roll_dice(2, 8)), "slashing" }) ]);
        break;
        case "dog":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        break;
        case "horse":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        tell_room(room, "%^BOLD%^" + sprintf("%s kicks %s with its hooves twice.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 4)), "piercing" }) ]);
        attacks += ([ "two" : ({ (scale * roll_dice(2, 6)), "bludgeoning" }) ]);
        break;
        case "snake":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 4)), "piercing" }) ]);
        if(!random(5))
            POISON_D->ApplyPoison(target, "black_adder_venom", this_object(), "injury");
        break;
        case "wolf":
        tell_room(room, "%^BOLD%^" + sprintf("%s bites and trips %s.", aname, tname));
        attacks += ([ "one" : ({ (scale * roll_dice(1, 6)), "piercing" }) ]);
        if(!random(5))
            target && target->set_tripped(1, "%^WHITE%^You are struggling to regain your footing! %^RESET%^");
        break;
    }

    foreach(string str in keys(attacks))
    {
        if(!target)
            return;

        if(sizeof(attacks[str]) < 2)
            return;

        if(FEATS_D->usable_feat(owner, "silverclaw"))
            target->cause_typed_damage(target, "torso", attacks[str][0], "silver");
        else
            target->cause_typed_damage(target, "torso", attacks[str][0], attacks[str][1]);
    }

    return;
}

void timer(object target)
{
   //if(!objectp(tp))  return;  // added because it's in a callout *Styx*
   if(!target->query_property("using sic")) dest_effect();
   if(!sizeof(tp->query_attackers())) {
        target->remove_property("using sic");
        dest_effect();
        return;
   }
   call_out("timer",1,tp);
}

void die(object ob)
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "acompanion");
    owner && tell_object(owner, "%^RED%^Your animal companion screams in agony as it passes from this world!%^RESET%^");
    owner && owner->remove_property("animal_companion");
    owner && owner->remove_property("has_elemental");
    remove();
}

int remove()
{
    //"/daemon/yuck_d"->save_inventory(this_object(), SAVEDIR + "acompanion");
    //all_inventory(this_object())->remove();
    owner && owner->remove_property("animal_companion");
    owner && owner->remove_property("has_elemental");
    ::remove();
}
