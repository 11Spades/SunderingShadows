/*
  _raise_the_dead.c

  Feat that allows a Bones Oracle to summon a skeleton companion.

  -- Tlaloc --
*/

#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit FEAT;

//Format - type : ({ STR, DEX, CON, INT, WIS, CHA, SIZE, AC BONUS, }),
mapping valid_types = ([
                         "skeleton" :       ({ 13, 17, 10, 2, 12, 7, 3, 2 }),
                      ]);

object companion;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("DivineSpellcraft");
    feat_name("raise the dead");
    feat_prereq("Bones Oracle L5");
    feat_classes(({"druid", "ranger"}));
    feat_syntax("raise_the_dead to summon or raise_the_dead to dismiss");
    feat_desc("Summons or dismisses your faithful animal companion. This companion will follow you through thick and thin, will level up with you, and gains several perks as it grows. The TYPE of animal will determine its base stats and natural armor.  The animal companion gains its own feats as follows:

  LEVEL  3 - Evasion
  LEVEL  6 - Resistance
  LEVEL  9 - Precise Strikes
  LEVEL 15 - Stalwart

The Animal Companion will hide if you use the 'hide_in_shadows' command, allowing you to effectively sneak about with your faithful friend.

The Animal Companion can also be customized through several commands, which will allow you to change its description:

  'animal short [DESCRIPTION]' - Changes the short description of the companion.
  'animal long  [DESCRIPTION]' - Changes the long description of the companion.

  To have the animal companion follow you, use 'animal follow'.
  To command the animal companion, use %^ORANGE%^<animal command %^ULINE%^ACTION%^RESET%^ORANGE%^>.%^RESET%^");

    set_target_required(0);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob))
        return 0;
    
    if(ob->query_mystery() != "bones")
    {
        dest_effect();
        return 0;
    }

    if(ob->query_class_level("oracle") < 5)
    {
        dest_effect();
        return 0;
    }

    return ::prerequisites(ob);
}

int cmd_raise_the_dead(string str)
{
    object feat;

    if(!objectp(this_player()))
        return 0;

    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(), str);

    return 1;
}

void execute_feat()
{
    object ob;

    int class_level,
        comp_hd,
        comp_ac;

    ::execute_feat();

    if(caster->query_property("using instant feat"))
    {
        tell_object(caster,"You are already in the middle of using a feat!");
        dest_effect();
        return;
    }


    if(sizeof(caster->query_attackers()))
    {
        tell_object(caster, "You can't summon your skeleton during combat!");
        return;
    }


    companion = caster->query_property("skeleton_companion");

    if(objectp(companion))
    {
        companion && tell_object(caster, "You dismiss your skeleton.");
        caster->remove_property("skeleton_companion");
        companion && companion->remove();
        return;
    }

    /*
    if(!arg || member_array(arg, keys(valid_types)) < 0)
    {
        tell_object(caster, "That is not a valid choice for your skeleton.");
        tell_object(caster, "Valid options are: (" + implode(m_indices(valid_types), ",") + ") ");
        return;
    }
    */

    tell_object(caster, "You raise a skeleton companion to your side.");

    class_level = flevel;

    comp_hd = class_level + 2;
    comp_ac = class_level + 10;

    companion = new("/d/magic/mon/scompanion");
    companion->set_race("skeleton");
    companion->set_name("skeleton");
    companion->set_id( ({ "skeleton", "companion", "skeleton companion", "greater summon", caster->query_name() + "'s ally" }) );
    companion->set_short(sprintf("%s's faithful skeleton.",capitalize(caster->query_name())));
    companion->set_level(class_level);
    companion->set_hd(comp_hd, 14);
    companion->set_attacks_num(2 + class_level / 8);
    companion->set_mlevel("fighter", comp_hd);
    companion->set_max_hp(14 + (14 * comp_hd));
    companion->set_hp(14 * comp_hd + 14);
    companion->set_alignment(caster->query_alignment());
    companion->set_owner(caster);

    caster->set_property("skeleton_companion", companion);
    caster->add_follower(companion);
    caster->add_protector(companion);

    companion->set_property("minion", caster);
    companion->move(environment(caster));
    companion->set_heart_beat(1);

    //Setting companion stats based on type per SRD
    companion->set_stats("strength", valid_types["skeleton"][0] + min( ({ class_level / 5, 6 }) ) );
    companion->set_stats("dexterity", valid_types["skeleton"][1] + min( ({ class_level / 5, 6 }) ) );
    companion->set_stats("constitution", valid_types["skeleton"][2]);
    companion->set_stats("intelligence", valid_types["skeleton"][3]);
    companion->set_stats("wisdom", valid_types["skeleton"][4]);
    companion->set_stats("charisma", valid_types["skeleton"][5]);
    companion->set_size(valid_types["skeleton"][6]);
    companion->set_overall_ac(0 - comp_ac - valid_types["skeleton"][7]);

    //Based on SRD - companion gets "specials" at certain caster levels
    if(class_level >= 3)
        companion->set_monster_feats( ({ "evasion" }) );
    if(class_level >= 6)
        companion->set_monster_feats( ({ "evasion", "resistance" }) );
    if(class_level >= 9)
        companion->set_monster_feats( ({ "evasion", "resistance", "precise strikes" }) );
    if(class_level >= 15)
        companion->set_monster_feats( ({ "evasion", "resistance", "precise strikes", "stalwart" }) );

    return;
}

void dest_effect()
{
    remove_feat(this_object());
    ::dest_effect();
    return;
}
