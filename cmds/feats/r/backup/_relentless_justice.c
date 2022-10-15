#include <std.h>
#include <daemons.h>
#include <magic.h>
#include <teleport.h>
inherit FEAT;

int DELAY = 300;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("CrimsonTemplar");
    feat_name("relentless justice");
    feat_syntax("relentless_justice TARGET");
    feat_prereq("Crimson Templar L7");
    set_save("will");
    feat_desc("You can only escape the sins of your past for so long. With this feat, the Crimson Templar becomes the long arm of holy justice, using their divinely gifted power to seek out and locate their target, attempting to pull them to the Templar to answer for their sins. The target must make a will save or be instantly pulled to the caster. This feat uses the caster's highest casting stat for the purposes of save DC. This feat gains a bonus against those of the opposite alignment.");
    set_target_required(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) return 0;
    if((int)ob->query_class_level("crimson_templar") < 7)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_relentless_justice(string str)
{
    object ob,location;
    string target;
    int bonus;

    if(!objectp(TP))
        return 0;
    if(!stringp(str))
        return 0;
    if(!str)
        return 0;

    if (caster->query_bound() || caster->query_unconscious() || caster->query_paralyzed())
    {
        caster->send_paralyzed_message("info",ETO);
    }

    if(this_player()->cooldown("relentless justice")){
        tell_object(caster, "You must wait longer to use relentless justice.");
        return 1;
	}

    target = TP->realNameVsProfile(str);
    ob = find_player(target);

    if(!ob)
    {
        notify_fail("Your target doesn't exist.");
        return 1;
    }
    
    if(member_array(ob->query_true_align(), ({ 3, 6, 7, 8, 9 })) < 0)
    {
        tell_object(caster, "You can only seek out those with a chaotic or evil heart.");
        return 1;
    }
           
    tell_object(caster, "%^BOLD%^%^WHITE%^You utter a call to the heavens to reveal your target and use you as its instrument of justice. You summon them to answer for their crimes!%^RESET%^");
    tell_object(ob, "%^BOLD%^WHITE%^A beacon of brilliant light falls upon you and you feel yourself being pulled from afar!%^RESET%^");
    this_player()->add_cooldown("relentless justice", DELAY);
    
    location = environment(caster);
    bonus = max(({ BONUS_D->query_stat_bonus(caster, "wisdom"), BONUS_D->query_stats_bonus(caster, "charisma"), BONUS_D->query_stat_bonus(caster, "intelligence") }));
    bonus += (PLAYER_D->opposed_alignment(caster, ob) * 3);

    if(!TELEPORT->object_can_be_teleported(ob,location,caster->query_base_character_level()))
    {
        notify_fail("Something is blocking your path.");
        tell_object(ob, "%^BOLD%^The brilliant pull seems to be blocked.%^RESET%^");
        return 1;
    }
    else
    {
        if(do_save(ob, bonus))
        {
            tell_object(caster, "%^CYAN%^Your attempt to pull your target fails.%^RESET%^");
            tell_object(ob, "%^CYAN%^BOLD%^You manage to resist the relentless pull of justice!%^RESET%^");
            return 1;
        }
        else
        {
            ob->move_player(location);
            tell_object(ob, "%^BOLD%^WHITE%^You are pulled through the ether in a flash of holy light!%^RESET%^");
            tell_object(caster,"%^BOLD%^%^WHITE%^Your holy light graps your target and pulls them to you!%^RESET%^");
        }
    }

    return 1;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(this_object());
    return;
}
