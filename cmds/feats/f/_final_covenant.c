#include <std.h>
#include <daemons.h>

#define SHAPE_DIR "/std/races/shapeshifted_races/"
#define DELAY 180

inherit FEAT;

void reverse_shape();

void create()
{
    ::create();
    feat_type("instant");
    feat_category("PactBond");
    feat_name("final covenant");
    feat_prereq("Warlock L31");
    feat_syntax("final_covenant");
    feat_desc("You've done the work. You've shown your willingness to do the uthinkable. And now you're ready for the final step. You will open your soul to your patron completely, allowing them to enter this world for a short period of time, using you as its glove in the world. With this feat, you fully take on the characteristics of your patron, becoming a fearsome extraplanar creature for a short time. The basic template of this form depends on your patron type.");
    set_target_required(0);
    allow_blind(1);
    set_required_for(({}));
}

int allow_shifted() { return 1; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }

    if((int)ob->query_class_level("warlock") < 31)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}

int cmd_final_covenant(string str)
{
    object feat;
    if(!objectp(this_player())) { return 0; }
    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(),str);
    return 1;
}

void execute_feat()
{
    if (FEATS_D->is_active(caster, "final covenant"))
    {
        tell_object(caster, "%^CYAN%^You let go of your fearsome shape and return to normal.%^RESET%^");
        reverse_shape();
        return;
    }
    
    if(caster->query_casting())
    {
        tell_object(caster,"%^BOLD%^You can't use final covenant while you're casting a spell.");
        dest_effect();
        return;
    }
    
    if(caster->query_property("using instant feat"))
    {
        tell_object(caster,"You are already in the middle of using a feat!");
        dest_effect();
        return;
    }
    
    if(caster->cooldown("final covenant"))
    {
        tell_object(caster, "You aren't ready to use final covenant yet.");
        dest_effect();
        return;
    }
    
    ::execute_feat();

    tell_object(caster,"You open yourself to possession by your patron.");
    //tell_room(place,"Shifting into message room",caster);
    caster->set_property("using instant feat",1);
    caster->set_property("active_feats", ({ this_object() }));
}

void reverse_shape()
{
    object shape;
    
    if(caster)
    {
        if(shape = caster->query_property("shapeshifted"))
            shape->reverse_shape(caster);
        else if(shape = caster->query_property("altered"))
            shape->reverse_shape(caster);
    }
    dest_effect();
}

void execute_attack()
{
    object shape;
    string pact, file;

    if(!objectp(caster)) { return; }

    caster->remove_property("using instant feat");
    ::execute_attack();

    if(caster->query_casting())
    {
        tell_object(caster,"%^BOLD%^You can't shapeshift while you're casting a spell.");
        dest_effect();
        return;
    }

    pact = caster->query("warlock heritage");
    
    switch(pact)
    {
        case "abyssal":
        case "demonic":
        file = "warlock_abyssal.c";
        break;
        case "infernal":
        file = "warlock_infernal.c";
        break;
        case "gloom":
        file = "warlock_gloom.c";
        break;
        case "astral":
        file = "warlock_astral.c";
        break;
        case "fey":
        file = "warlock_fey.c";
        break;
    }
    
    strlen(file) && catch(shape = new(SHAPE_DIR + file));
    objectp(shape) && shape->init_shape(caster);
    caster->add_cooldown("final covenant", DELAY);
    
    return;
}

void dest_effect()
{   
    ::dest_effect();
    remove_feat(this_object());
    return;
}
