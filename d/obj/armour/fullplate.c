inherit "/std/armour";

void create() {
    ::create();
    set_name("fullplate");
    set("id", ({ "armor", "full plate armor","plate" }) );
    set("short", "A suit of full plate armor");
    set("long", 
	"This is the impressive, high gothic style armor of the late "
"middle ages and renaissance. It is perfectly forged and fitted. All the  "
"plates are interlocking and carefully angled to deflect blows. The metal "
"plates are backed by padding and chainmail. The weight is well " 
"distributed. The armor is hot and extremely expensive."
       );
    set_weight(70);
    set("value", 10000);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(9);
}
