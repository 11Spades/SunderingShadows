/*
  _eldritch_strikes.c

  Adds your blast type to your weapon.

  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

object weapon, feat;

void create()
{
    ::create();

    set_author("tlaloc");
    feat_type("instant");
    feat_category("PactBond");
    feat_name("eldritch strikes");
    feat_prereq("Warlock L1");
    feat_syntax("eldritch_strikes");
    feat_desc("This feat allows the warlock to infuse their current mainhand weapon with eldritch energy, effectively applying their eldritch essence (blast type) to that weapon. This will cause the weapon to periodically perform an extra hit in combat based on the blast type chosen. The essence type changes whenever the warlock changes blasttype.");
    set_target_required(0);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) {
        return 0;
    }
    if(ob->query_class_level("warlock") < 1)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_eldritch_strikes(string str)
{
    if(!this_player())
        return 0;

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);
    return 1;
}

void execute_feat()
{
    string type;
    mapping info;
    int timer, glvl;

    ::execute_feat();

    if(!caster)
        return;

    if(caster->query_property("using instant feat"))
    {
        write("You are already in the middle of using a feat!");
        return;
    }

    if(sizeof(caster->query_wielded()))
        weapon = caster->query_wielded()[0];

    if(!weapon)
    {
        write("You must be wielding a weapon in your main hand to use Eldritch Strikes.");
        return;
    }

    if(caster->query_property("eldritch strikes"))
    {
        write("Your weapon is already magically enhanced.");
        dest_effect();
        return;
    }

    write("%^BOLD%^BLACK%^You infuse your weapon with %^GREEN%^eldritch%^BLACK%^ potency.");
    tell_room(environment(caster),"%^BOLD%^"+caster->query_cap_name()+" infuses their weapon with eldritch essence.", ({ caster }));

    weapon->set_property("added short", ({ "%^BLACK%^BOLD%^ [%^GREEN%^eldritch%^BLACK%^]%^RESET%^" }) );
    caster->set_property("using instant feat",1);
    caster->remove_property("eldritch strikes");
    caster->set_property("eldritch strikes", ({ weapon, arg }));
}

void execute_attack()
{
    if(!objectp(caster))
    {
        dest_effect();
        return;
    }
    caster->remove_property("using instant feat");
    ::execute_attack();
}


void dest_effect()
{
    caster && tell_object(caster, "%^BOLD%^You sense the eldritch essence fading from your weapon.%^RESET%^");
    caster && caster->remove_property("eldritch strikes");
    weapon && weapon->remove_property_value("added short", ({ "%^BLACK%^BOLD%^ [%^GREEN%^eldritch%^BLACK%^]%^RESET%^" }) );
    ::dest_effect();
    remove_feat(this_object());
    return;
}
