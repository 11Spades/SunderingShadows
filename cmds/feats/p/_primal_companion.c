/*
  _primal_companion.c

  Similar to animal companion for lunar mystery oracle.

*/


#include <std.h>
#include <daemons.h>
#include <magic.h>

inherit FEAT;

//Format - type : ({ STR, DEX, CON, INT, WIS, CHA, SIZE, AC BONUS, }),
mapping valid_types = ([
                         "ape" :       ({ 13, 17, 10, 2, 12, 7, 3, 2,  }),
                         "badger" :    ({ 10, 17, 15, 2, 12, 10, 2, 4, }),
                         "bear" :      ({ 15, 15, 13, 2, 12, 6, 3, 4,  }),
                         "bird" :      ({ 15, 15, 13, 2, 14, 6, 1, 2,  }),
                         "boar" :      ({ 13, 12, 15, 2, 13, 4, 2, 12, }),
                         "camel" :     ({ 18, 16, 14, 2, 11, 4, 3, 2,  }),
                         "cheetah" :   ({ 12, 21, 13, 2, 12, 6, 2, 2,  }),
                         "crocodile" : ({ 15, 14, 15, 1, 12, 2, 2, 8,  }),
                         "dinosaur" :  ({ 11, 17, 17, 2, 12, 14, 2, 2, }),
                         "dog" :       ({ 13, 17, 15, 2, 12, 6, 2, 4,  }),
                         "fox" :       ({  9, 15, 13, 6, 12, 6, 1, 4,  }),
                         "horse" :     ({ 16, 13, 15, 2, 12, 6, 3, 8,  }),
                         "lion" :      ({ 13, 17, 13, 2, 15, 10, 3, 2, }),
                         "snake" :     ({ 15, 17, 13, 1, 12, 2, 3, 4,  }),
                         "wolf" :      ({ 13, 15, 15, 2, 12, 6, 2, 4,  }),
                       ]);

object companion;

void create()
{
    ::create();
    feat_type("instant");
    feat_category("Presence");
    feat_name("primal companion");
    feat_prereq("Lunar Oracle L5");
    feat_classes(({"oracle","ranger","druid"}));
    feat_syntax("primal_companion [TYPE] to summon or primal_companion to dismiss");
    feat_desc("Summons or dismisses your faithful primal companion. This companion will follow you through thick and thin, will level up with you, and gains several perks as it grows. The TYPE of animal will determine its base stats and natural armor.  The primal companion levels with the oracle.

The Primal Companion will hide if you use the 'hide_in_shadows' command, allowing you to effectively sneak about with your faithful friend.

The Primal Companion will allow you to use the 'sic' command, allowing you to command your companion to pounce on an enemy.

The Primal Companion can also be customized through several commands, which will allow you to change its description:

  'animal short [DESCRIPTION]' - Changes the short description of the companion.
  'animal long  [DESCRIPTION]' - Changes the long description of the companion.

  To have the animal companion follow you, use 'animal follow'.
  If your animal companion dies, you'll have to wait for a while before summoning it again.
  This feat DOES NOT stack with the animal companion feat.
  This feat counts your lunar oracle, druid, and ranger levels.
  To command the animal companion, use %^ORANGE%^<animal command %^ULINE%^ACTION%^RESET%^ORANGE%^>.%^RESET%^");

    set_target_required(0);
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob))
        return 0;

    if(ob->query_class_level("oracle") < 5)
    {
        dest_effect();
        return 0;
    }
    if(ob->query_mystery() != "lunar")
    {
        dest_effect();
        return 0;
    }

    return ::prerequisites(ob);
}

int cmd_primal_companion(string str)
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

    if (caster->query_casting())
    {
        tell_object(caster, "%^BOLD%^You can't summon your primal companion while you're casting a spell.%^RESET%^");
        dest_effect();
        return;
    }

    if(sizeof(caster->query_attackers()))
    {
        tell_object(caster, "You can't summon your primal companion during combat!");
        return;
    }
    
    if(caster->cooldown("primal companion"))
    {
        tell_object(caster, "You can't summon your primal companion yet!");
        return;
    }
    
    companion = caster->query_property("animal_companion");

    if(objectp(companion))
    {
        companion && tell_object(caster, "You dismiss your primal companion.");
        caster->remove_property("animal_companion");
        companion && companion->remove();

        return;
    }

    if(!arg || member_array(arg, keys(valid_types)) < 0)
    {
        tell_object(caster, "That is not a valid choice for your animal companion.");
        tell_object(caster, "Valid options are: (" + implode(m_indices(valid_types), ",") + ") ");
        return;
    }

    tell_object(caster, sprintf("You summon your trusty %s companion%s to your side.", arg, caster->query_chosen_animal() == arg ? "s" : ""));

    //class_level = caster->query_prestige_level("ranger") + caster->query_prestige_level("druid");
    class_level = flevel;

    comp_hd = class_level + 2;
    comp_ac = class_level + 10;

    companion = new("/d/magic/mon/acompanion");
    companion->set_race(arg);
    companion->set_name(arg);
    companion->set_id( ({ arg, "companion", "animal companion", "greater summon", "animal" }) );
    companion->set_short(sprintf("%s's faithful %s companion.",caster->query_cap_name(),arg));
    companion->set_level(class_level);
    companion->set_hd(comp_hd, 14);
    companion->set_attacks_num(2 + class_level / 8);
    companion->set_mlevel("fighter", comp_hd);
    companion->set_max_hp(50 + ( 25 * comp_hd));
    companion->set_hp(25 * comp_hd + 50);
    companion->set_alignment(caster->query_alignment());
    companion->set_owner(caster);

    caster->set_property("animal_companion", companion);
    caster->add_follower(companion);
    caster->add_protector(companion);

    companion->set_property("minion", caster);
    companion->move(environment(caster));
    companion->set_heart_beat(1);

    //Setting companion stats based on type per SRD
    companion->set_stats("strength", valid_types[arg][0] + min( ({ class_level / 5, 6 }) ) );
    companion->set_stats("dexterity", valid_types[arg][1] + min( ({ class_level / 5, 6 }) ) );
    companion->set_stats("constitution", valid_types[arg][2]);
    companion->set_stats("intelligence", valid_types[arg][3]);
    companion->set_stats("wisdom", valid_types[arg][4]);
    companion->set_stats("charisma", valid_types[arg][5]);
    companion->set_size(valid_types[arg][6]);
    companion->set_overall_ac(0 - comp_ac - valid_types[arg][7]);
    companion->set_property("spell damage resistance", 10);
    companion->set_monster_feats( ({ "death ward" }) );

    return;
}

void dest_effect()
{
    remove_feat(this_object());
    ::dest_effect();
    return;
}
