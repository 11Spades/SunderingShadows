inherit "/std/armour";

void create() {
    ::create();
    set_name("ring");
    set("id", ({ "ring","armor", "ring mail","mail" }) );
    set("short", "A suit of ring mail armor");
    set("long", 
	"This armor is an early, and less effective version of chain mail " 
	"in which metal rings are sewn directly to leather backing, instead "
	"of being interlaced. "
       );
    set_weight(30);
    set("value", 100);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(3);
}
