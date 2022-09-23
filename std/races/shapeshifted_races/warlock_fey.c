#include <std.h>
#include <daemons.h>

inherit SHAPESHIFT;

void create()
{
    ::create();

    set_attack_limbs(({ "right hand", "left hand" }));
    set_limbs(({ "mouth", "head", "torso", "waist", "left arm", "left hand", "right arm", "right hand", "left leg", "left foot", "right leg", "right foot" }));
    set_base_attack_num(5);
    set_ac_bonus(5);
    set_castable(1);
    set_can_talk(1);
    set_shape_bonus("survival", 4);
    set_shape_bonus("athletics", 4);
    set_shape_bonus("endurance", 4);

    set_shape_bonus("damage bonus",5);
    set_shape_bonus("attack bonus",5);
    set_shape_bonus("spell resistance", 4);
    set_shape_bonus("damage resistance", 10);
    set_shape_bonus("spell damage resistance", 10);

    set_shape_race("fey");
    set_shape_profile("warlock_fey_999");
}

int default_descriptions(object obj){
    if(!objectp(obj)) return 0;
    
    obj->set_description("%^RESET%^%^CRST%^%^C084%^could be mistaken for an elf at a glance, %^C082%^slender %^C084%^of limb and %^C046%^graceful %^C084%^in movement, but even those fair folk don't possess such a measure of %^C228%^g%^C229%^l%^C230%^a%^C231%^m%^C230%^o%^C229%^u%^C228%^r %^RESET%^%^C084%^and %^C228%^b%^C229%^e%^C230%^au%^C229%^t%^C228%^y %^RESET%^%^C084%^as this. Light seems to pause, casting faint sparkles amid their features, from their benevolent gaze, to the faint grin on their lips, even to the gentle point of their ears.%^CRST%^");
    obj->setDescriptivePhrase("%^RESET%^%^CRST%^%^C084%^lithe, %^C082%^diminutive %^C084%^$R with %^C228%^e%^C229%^l%^C230%^f%^C229%^i%^C228%^n %^RESET%^%^C084%^features%^CRST%^");

    return 1;
}

// custom shapeshift messages here, override this function
int change_into_message(object obj){
    if(!objectp(obj)) return 0;
    
    tell_object(obj, "%^RESET%^%^CRST%^%^C208%^You seek a pathway along your bond, calling upon the pact that binds your soul to your patron...%^CRST%^");
    tell_object(obj, "%^RESET%^%^CRST%^%^C202%^Your plea is answered and the bond strengthens, power flowing through it and into you.%^CRST%^");
    tell_object(obj, "%^RESET%^%^CRST%^%^C196%^It overwhelms you, pain wracking through your very essence as you are remade to your patron's whim!%^CRST%^");

    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C208%^"+obj->QCN+"%^RESET%^%^CRST%^%^C208%^ grows very still and appears to concentrate deeply.%^CRST%^", obj);
    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C202%^"+obj->QCN+"%^RESET%^%^CRST%^%^C202%^ begins to convulse, pain obvious in their expression as their body begins to warp and twist!%^CRST%^", obj);
    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C196%^Where "+obj->QCN+"%^RESET%^%^CRST%^%^C196%^ once stood, is now a "+obj->query_race()+"!%^CRST%^", obj);

    return 1;
}

// custom unshapeshift messages here, override this function
int change_outof_message(object obj){
    if(!objectp(obj)) return 0;
    
    tell_object(obj, "%^RESET%^%^CRST%^%^C196%^The power given is suddenly withdrawn...");
    tell_object(obj, "%^RESET%^%^CRST%^%^C202%^You grit your teeth as yet again, your body is mercilessly remade!");
    tell_object(obj, "%^RESET%^%^CRST%^%^C208%^With a shuddered breath, you find your former self returned.");

    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C196%^"+obj->QCN+"%^RESET%^%^CRST%^%^C196%^ suddenly begins to shudder, seeming to shrink before your eyes.", obj);
    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C202%^"+obj->QCN+"%^RESET%^%^CRST%^%^C202%^ begins to convulse, pain obvious in their expression as their body begins to warp and twist!", obj);
    tell_room(environment(obj), "%^RESET%^%^CRST%^%^C208%^Where "+obj->QCN+"%^RESET%^%^CRST%^%^C208%^ once stood, now stands a "+obj->query_race()+"!", obj);

    return 1;
}

int can_cast()
{
    return 1;
}

int shape_attack(object tp, object targ)
{
    return 0;
}

int init_shape(object obj, string str)
{
    if (!objectp(obj)) {
        return 0;
    }
    if (obj->query_property("altered") || obj->query_property("shapeshifted")) {
        return 0;
    }                                                                                       // can't shapeshift twice
    obj->set_property("altered", shape = new(base_name(TO) + ".c"));
    shape->set_owner(obj);
    shape->change_into_message(obj);
    shape->set_base_profile((string)obj->query("relationship_profile"));
    shape->set_shape_race("fey");
    shape->apply_bonuses(shape->query_owner());

    obj->add_id("fey");
    obj->set("relationship_profile", shape->query_shape_profile());
    obj->add_id(obj->query_race());

    if (objectp(to_object(DESC_D))) {
        desc = new(DESC_D); //
        if (!desc->restore_profile_settings(obj, shape->query_shape_profile())) {
            shape->default_descriptions(obj);
            desc->initialize_profile(obj);
        }
    }
    return 1;
}

int reverse_shape(object obj)
{
    if (!objectp(obj)) {
        return 3;
    }
    if (!objectp(shape = obj->query_property("altered"))) {
        return 5;
    }
    obj->set("relationship_profile", shape->query_base_profile());
    obj->remove_id("fey");
    if (objectp(to_object(DESC_D))) {
        desc = new(DESC_D);
        desc->restore_profile_settings(obj, shape->query_base_profile());
    }
    shape->reverse_bonuses(shape->query_owner());
    shape->change_outof_message(obj);
    shape->set_owner(0);
    obj->remove_property("altered");
    clean_me = 1;
    destruct(TO);
    return 1;
}
