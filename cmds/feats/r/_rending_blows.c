#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

int FEATTIMER = (60 - (FEATS_D->usable_feat(caster, "abundant tactics") * 12));

void create() 
{
    ::create();
    feat_type("instant");
    feat_category("AdvancedTraining");
    feat_name("rending blows");
    feat_prereq("Fighter L21, Advanced Training Feat");
    feat_syntax("rending_blows");
    feat_desc("With this feat, the fighter shifts their stance and method of attack to cause bleeding wounds on their foes. They gain -5 damage on their attacks in return for each successful hit causing 1 stack of Rend on their target. This feat will last three rounds and has a cooldown. This feats requires a wielded weapon to perform.");
}


int allow_shifted() { return 0; }


int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }
    if((int)ob->query_class_level("fighter") < 21)
    {
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}


string cm(string str) { return CRAYON_D->color_string(str,"red"); }


int cmd_rending_blows(string str)
{
    object feat;
    
    if(!objectp(this_player()))
        return 0;
    
    feat = new(base_name(this_object()));
    feat->setup_feat(this_player(),str);
    return 1;
}

void execute_feat()
{
    int bonus;
    object obj, *weapons;
    
    if((int)caster->query_property("using instant feat")) 
    {
        tell_object(caster,"You are already in the middle of using a feat!");
        dest_effect();
        return;
    }
    
    if(FEATS_D->is_active(caster,"rending blows"))
    {
        obj = query_active_feat("rending blows");
        tell_object(caster, "%^YELLOW%^You return to your normal combat stance.%^RESET%^");
        obj->dest_effect();
        dest_effect();
        return;
    }
    
    if(caster->cooldown("rending blows"))
    {
        tell_object(caster, "You aren't ready to use rending blows yet.");
        dest_effect();
        return;
    }
    
    weapons = caster->query_wielded();
    
    if(!sizeof(weapons))
    {
        tell_object(caster, "You need to wield weapons to use Rending Blows.");
        dest_effect();
        return;
    }
    
    tell_object(caster, cm("You shift your stance and method of attack to cause bleeding on your foes."));   

    caster->set_property("active_feats",({ this_object() }));
    caster->add_cooldown("rending blows", FEATTIMER);
    
    ::execute_feat();
    call_out("dest_effect", 18);
    return;
}


void dest_effect()
{
    object obj;
    
    if(objectp(caster))
    {
        caster->remove_property_value("active_feats",({ this_object() }));
        tell_object(caster, "%^YELLOW%^You return to your normal combat stance.%^RESET%^");
    }

    obj = query_active_feat("rending blows");
    obj && obj->dest_effect();
    
    ::dest_effect();
    remove_feat(this_object());
    return;
}

