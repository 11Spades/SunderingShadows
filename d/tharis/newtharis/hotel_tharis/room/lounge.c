// Chernobog (9/6/21)
// Tharis Hotel

#include <std.h>
#include "../defs.h"
inherit "/std/library";

void create(){
    ::create();
    set_terrain(CITY);
    set_travel(PAVED_ROAD);
    set_property("light", 2);
    set_property("indoors", 1);
    set_name("Hotel Lounge");
    set_short("%^MAGENTA%^H%^BOLD%^%^BLACK%^ote%^RESET%^%^MAGENTA%^l L%^BOLD%^%^BLACK%^oung%^RESET%^%^MAGENTA%^e%^WHITE%^");
    set_long("%^BOLD%^%^BLACK%^This is a comfortable study replete with a well-stocked %^RESET%^bar%^BOLD%^%^BLACK%^, a wall of built-in %^RESET%^bookshelves%^BOLD%^%^BLACK%^, and a large welcoming %^WHITE%^f%^RESET%^i%^BOLD%^r%^RESET%^e%^BOLD%^pl%^RESET%^a%^BOLD%^c%^RESET%^e%^BOLD%^%^BLACK%^. An assortment of %^RESET%^%^MAGENTA%^pl%^BOLD%^u%^BLACK%^s%^RESET%^%^MAGENTA%^h r%^BOLD%^u%^BLACK%^g%^RESET%^%^MAGENTA%^s %^BOLD%^%^BLACK%^have been spread about the middle of the room, with a half dozen lounge chairs placed in a semicircle. Each is accompanied by a small ebony wood side table with a coaster and s%^RESET%^i%^BOLD%^l%^RESET%^v%^BOLD%^%^BLACK%^er a%^RESET%^s%^BOLD%^h%^BLACK%^tr%^RESET%^a%^BOLD%^%^BLACK%^y, except for one that features a small %^BOLD%^%^BLACK%^s%^RESET%^i%^BOLD%^l%^RESET%^v%^BOLD%^%^BLACK%^er b%^RESET%^e%^BOLD%^l%^BLACK%^l instead. An impressive %^RESET%^portrait %^BOLD%^%^BLACK%^peers down from its place above the mantle. In one corner of the room a fine %^RESET%^stage %^BOLD%^%^BLACK%^has been erected for %^RESET%^%^CYAN%^p%^BOLD%^e%^RESET%^%^CYAN%^rf%^BOLD%^o%^RESET%^%^CYAN%^rm%^BOLD%^a%^RESET%^%^CYAN%^nc%^BOLD%^e%^RESET%^%^CYAN%^s %^BOLD%^%^BLACK%^and live %^RESET%^m%^BOLD%^u%^RESET%^s%^BOLD%^i%^RESET%^c%^BOLD%^%^BLACK%^.%^RESET%^\n");
    set_smell("default","Cigar smoke wafts lazily in the air.");
    set_listen("default","There is the occasional crackle and pop from the fireplace.");
    set_items(([
        ({"wall", "walls"}) : "%^BOLD%^%^BLACK%^Large slabs of %^RESET%^polished %^BOLD%^%^BLACK%^m%^RESET%^a%^BOLD%^r%^BLACK%^bl%^WHITE%^e %^BLACK%^shot through with v%^RESET%^e%^BOLD%^i%^BLACK%^ns of %^WHITE%^wh%^RESET%^i%^BOLD%^te %^BLACK%^comprise these walls.%^RESET%^",
        "rugs" : "%^RESET%^The %^BOLD%^%^BLACK%^eb%^RESET%^o%^BOLD%^%^BLACK%^ny fl%^RESET%^o%^BOLD%^o%^BLACK%^rs %^RESET%^have been covered in several thick %^MAGENTA%^r%^BOLD%^u%^BLACK%^g%^RESET%^%^MAGENTA%^s%^WHITE%^, spread throughout the room. They are %^MAGENTA%^luxurious %^WHITE%^and %^BOLD%^%^MAGENTA%^soft%^RESET%^, though faded in the spots that are close to the %^BOLD%^fireplace%^RESET%^.",
        "fireplace" : "%^RESET%^A truly fantastic and grand focal point to the room, the %^BOLD%^fireplace %^RESET%^dominates the corner opposite the stage. Unlike the rest of the walls, the fireplace has been constructed from %^BOLD%^gl%^RESET%^i%^BOLD%^tt%^RESET%^e%^BOLD%^r%^RESET%^i%^BOLD%^ng wh%^RESET%^i%^BOLD%^t%^RESET%^e %^BOLD%^qu%^RESET%^ar%^BOLD%^tz %^RESET%^and features a mantle of %^BOLD%^%^BLACK%^ebony wood%^RESET%^. A large %^BOLD%^portrait %^RESET%^sits above the %^BOLD%^%^BLACK%^mantle %^RESET%^in a place of honor, seeming to dominate the room from its position. Within a broad %^BOLD%^%^BLACK%^iron cage, %^RESET%^a %^BOLD%^%^RED%^f%^ORANGE%^i%^RESET%^%^RED%^r%^BOLD%^e b%^RESET%^%^ORANGE%^u%^RED%^r%^BOLD%^ns %^RESET%^brightly, an occasional %^BOLD%^%^RED%^e%^RESET%^%^RED%^m%^BOLD%^%^BLACK%^b%^RESET%^%^RED%^e%^BOLD%^r %^RESET%^wafting out into the room.%^RESET%^",
        ({"painting", "portrait"}) : "%^RESET%^This %^BOLD%^%^BLACK%^o%^RESET%^i%^BOLD%^%^BLACK%^l p%^RESET%^a%^BOLD%^i%^BLACK%^nt%^RESET%^i%^BOLD%^%^BLACK%^ng %^RESET%^depicts an %^BOLD%^i%^BLACK%^n%^RESET%^t%^BOLD%^i%^BLACK%^m%^WHITE%^i%^RESET%^dat%^BOLD%^i%^BLACK%^n%^RESET%^g figure of %^BLUE%^pure darkness%^WHITE%^. Clad in elaborate and ancient armor this being stands proudly, features of %^BOLD%^%^BLACK%^pure obsidian %^CYAN%^gl%^RESET%^%^CYAN%^a%^BOLD%^r%^RESET%^%^CYAN%^i%^BOLD%^ng imp%^RESET%^%^CYAN%^e%^BOLD%^r%^RESET%^%^CYAN%^i%^BOLD%^ously %^RESET%^from beneath a jagged %^BOLD%^%^BLACK%^cr%^RESET%^o%^BOLD%^%^BLACK%^wn %^RESET%^of %^BOLD%^%^BLACK%^Adamantine%^RESET%^. Grasped between his %^RED%^cl%^BOLD%^a%^RESET%^%^RED%^w %^WHITE%^like %^BOLD%^%^BLACK%^gauntlets%^RESET%^, point toward the ground, is a %^RED%^d%^BOLD%^%^BLACK%^e%^RESET%^%^RED%^m%^BOLD%^o%^RESET%^%^RED%^n%^BOLD%^i%^RESET%^%^RED%^c gr%^BOLD%^%^BLACK%^e%^RED%^a%^RESET%^%^RED%^t sw%^BOLD%^o%^RESET%^%^RED%^rd%^WHITE%^, a vortex of %^BLUE%^dark energy %^WHITE%^rising up around its %^BOLD%^%^BLACK%^bl%^RESET%^a%^BOLD%^%^BLACK%^de%^RESET%^. Below the portrait a %^BOLD%^%^BLACK%^s%^RESET%^i%^BOLD%^l%^RESET%^v%^BOLD%^%^BLACK%^er pl%^RESET%^a%^BOLD%^%^BLACK%^q%^WHITE%^u%^RESET%^e reads in flowing script: %^BOLD%^%^BLACK%^Lord Shadow%^RESET%^",
        ({"books", "bookshelves"}) : "%^RESET%^A truly impressive collection of %^BOLD%^books %^RESET%^lines the %^BOLD%^%^BLACK%^shelves%^RESET%^, their %^ORANGE%^aged covers %^WHITE%^proclaiming a mix of history and fiction. ",
        ({"table", "ashtray", "chairs"}) : "%^RESET%^These %^BOLD%^%^BLACK%^lounge chairs %^RESET%^have been upholstered in %^BOLD%^%^BLACK%^black leather %^RESET%^and set on %^BOLD%^%^BLACK%^ebony frames%^RESET%^. Every chair is accompanied by a three-legged side %^BOLD%^%^BLACK%^table %^RESET%^large enough to accommodate a small %^BOLD%^%^BLACK%^s%^RESET%^i%^BOLD%^l%^RESET%^v%^BOLD%^%^BLACK%^er a%^RESET%^s%^BOLD%^h%^BLACK%^tr%^RESET%^a%^BOLD%^%^BLACK%^y %^RESET%^and a drink of choice.%^RESET%^",
        "floor" : "%^RESET%^Solid %^BOLD%^%^BLACK%^ebony floorboards %^RESET%^lay beneath your feet in a %^BOLD%^%^BLACK%^h%^RESET%^e%^BOLD%^r%^RESET%^r%^BOLD%^%^BLACK%^i%^RESET%^n%^BOLD%^g%^RESET%^b%^BOLD%^%^BLACK%^o%^RESET%^n%^BOLD%^e %^RESET%^pattern, the %^BOLD%^%^BLACK%^black wood p%^RESET%^o%^BOLD%^%^BLACK%^l%^WHITE%^i%^BLACK%^sh%^RESET%^e%^BOLD%^%^BLACK%^d %^RESET%^to a %^BOLD%^reflective %^BLACK%^sh%^RESET%^e%^BOLD%^e%^BLACK%^n%^RESET%^.",
        "stage" : "%^RESET%^Constructed from %^BOLD%^%^BLACK%^eb%^RESET%^o%^BOLD%^%^BLACK%^ny t%^RESET%^i%^BOLD%^%^BLACK%^mb%^RESET%^e%^BOLD%^%^BLACK%^r %^RESET%^harvested from the %^GREEN%^Th%^BOLD%^a%^RESET%^%^GREEN%^r%^BOLD%^i%^RESET%^%^GREEN%^s F%^BOLD%^o%^RESET%^%^GREEN%^r%^BOLD%^e%^RESET%^%^GREEN%^st%^WHITE%^, this raised %^BOLD%^%^BLACK%^dais %^RESET%^provides an area for %^ORANGE%^musicians %^WHITE%^and %^CYAN%^performers %^WHITE%^to entertain the patrons of the lounge. Thick, crushed velvet curtains of %^MAGENTA%^deep violet %^WHITE%^line the stage and provide a private place for preparations, costume changes, and storage.%^RESET%^",
        "bell" : "%^RESET%^A small %^BOLD%^%^BLACK%^s%^RESET%^i%^BOLD%^l%^RESET%^v%^BOLD%^%^BLACK%^er b%^RESET%^e%^BOLD%^l%^BLACK%^l%^RESET%^ rests on a %^BOLD%^lace doily %^RESET%^atop a small round table near the center of the room. You should be able to ring the %^BOLD%^%^BLACK%^b%^RESET%^e%^BOLD%^l%^BLACK%^l %^RESET%^for service.%^RESET%^",
        ]));
    set_exits(([
        "hall" : ROOMS "hall",
        ]));
}

void reset(){
    ::reset();
    if(!present("dealer")) new(MON "zashan")->move(TO);
}

void init(){
    ::init();
    add_action("read_fun","read");
    add_action("ring_fun","ring");
    add_action("dismiss_fun","dismiss");
}

int ring_fun(string str){
    if((str!="the bell") && (str!="bell"))
        return 0;
    if(present("roomservice")){
        write("Room service is already here!");
        return 1;
    }
    else{
        new(MON"roomservice1.c")->move(TO);
        new(OBJ"serving_cart.c")->move(TO);
    }
    tell_object(TP,"%^BOLD%^%^BLACK%^You give the bell a short %^RESET%^r%^BOLD%^i"+
        "%^RESET%^n%^BOLD%^%^BLACK%^g. A few moments later, a servant enters with a "+
        "serving cart laden with covered dishes. They set a few %^RESET%^menus%^BOLD%^"+
        "%^BLACK%^ out and await your pleasure.%^RESET%^");
    tell_room(ETP,"%^BOLD%^%^BLACK%^"+TP->QCN+" gives the small bell a %^RESET%^r"+
        "%^BOLD%^i%^RESET%^n%^BOLD%^%^BLACK%^g. A few moments later, a servant enters "+
        "pushing a serving cart laden with covered plates and dishes. They set a few "+
        "%^RESET%^menus%^BOLD%^%^BLACK%^ out and await your pleasure.%^RESET%^",TP);
    tell_object(TP,"\n%^RESET%^You can %^BOLD%^dismiss room service %^RESET%^when you "+
        "are finished ordering.");
    return 1;
}

int dismiss_fun(string str){
    object ob, ob2;
    
    if((str!="room service") && (str!="servant"))
        return 0;
    if(!present("roomservice"))
        return 0;
    ob=present("roomservice");
    ob2=present("servingcart");
    tell_room(ETP,"%^RESET%^The servant bows their head in subservience, turning to "+
        "push the cart from the room.");
    ob->move("/d/shadowgate/void.c");
    ob->remove();
    ob2->move("/d/shadowgate/void.c");
    ob2->remove();
    return 1;
}

int read_fun(string str){
    object ob;
    
    if(str!="menu")
        return 0;
    if(!present("roomservice")){
        write("You should summon room service first.");
        return 1;
    }
    
    ob=present("roomservice");
    
    write("\n");
    write("%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~ %^BOLD%^%^BLACK%^The %^RESET%^%^MAGENTA%^V%^BOLD%^io%^RESET%^%^MAGENTA%^l%^BOLD%^e%^RESET%^%^MAGENTA%^t %^BOLD%^%^BLACK%^Restaurant %^RESET%^%^MAGENTA%^& %^BOLD%^%^BLACK%^Bar %^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^WHITE%^");
    write("\n");
    write("\n");
    write("                   %^RESET%^%^MAGENTA%^Appetizers%^RESET%^                   %^RESET%^");
    write("%^BOLD%^%^BLACK%^Pumpkin Cream Soup%^WHITE%^\t\t\t"+(int)ob->get_price("soup")+" gold");
    write("%^BOLD%^%^BLACK%^Tharisian Salad%^WHITE%^\t\t\t\t"+(int)ob->get_price("salad")+" gold");
    write("%^BOLD%^%^BLACK%^Fried Calamari%^WHITE%^\t\t\t\t"+(int)ob->get_price("calamari")+" gold");
    write("\n");
    write("                   %^RESET%^%^MAGENTA%^Main Course%^RESET%^");
    write("%^BOLD%^%^BLACK%^Filet Mignon%^WHITE%^\t\t\t\t"+(int)ob->get_price("filet mignon")+" gold");
    write("%^BOLD%^%^BLACK%^Rosemary Braised Lamb Shank%^WHITE%^\t\t"+(int)ob->get_price("lamb")+" gold");
    write("%^BOLD%^%^BLACK%^Dijon-Crusted Halibut%^WHITE%^\t\t\t"+(int)ob->get_price("halibut")+" gold");
    write("\n");
    write("                   %^RESET%^%^MAGENTA%^Desserts%^WHITE%^");
    write("%^BOLD%^%^BLACK%^Creme Brulee%^WHITE%^\t\t\t\t"+(int)ob->get_price("creme brulee")+" gold");
    write("%^BOLD%^%^BLACK%^Peach Cobbler%^WHITE%^\t\t\t\t"+(int)ob->get_price("cobbler")+" gold");
    write("%^BOLD%^%^BLACK%^Chocolate Cake%^WHITE%^\t\t\t\t"+(int)ob->get_price("cake")+" gold");
    write("\n");
    write("              %^RESET%^%^MAGENTA%^Non-Alcoholic Drinks%^RESET%^");
    write("%^BOLD%^%^BLACK%^Water%^WHITE%^\t\t\t\t\t"+(int)ob->get_price("water")+" gold");
    write("%^BOLD%^%^BLACK%^Lavender Tea%^WHITE%^\t\t\t\t"+(int)ob->get_price("tea")+" gold");
    write("%^BOLD%^%^BLACK%^Lemonade%^WHITE%^\t\t\t\t"+(int)ob->get_price("lemonade")+" gold");
    write("\n");
    write("             %^RESET%^%^MAGENTA%^Alcoholic Beverages%^RESET%^");
    write("%^BOLD%^%^BLACK%^Tequila Twilight%^WHITE%^\t\t\t"+(int)ob->get_price("tequila twilight")+" gold");
    write("%^BOLD%^%^BLACK%^Whiskey Sour%^WHITE%^\t\t\t\t"+(int)ob->get_price("whiskey sour")+" gold");
    write("%^BOLD%^%^BLACK%^Vodka Martini%^WHITE%^\t\t\t\t"+(int)ob->get_price("vodka martini")+" gold");
    write("%^BOLD%^%^BLACK%^Blood Wine%^WHITE%^\t\t\t\t"+(int)ob->get_price("blood wine")+" gold");
    write("%^BOLD%^%^BLACK%^Chardonnay%^WHITE%^\t\t\t\t"+(int)ob->get_price("chardonnay")+" gold");
    write("\n");
    write("             %^RESET%^%^MAGENTA%^Imported Moonshine%^RESET%^");
    write("%^BOLD%^%^BLACK%^Sex in the Woods%^WHITE%^\t\t\t"+(int)ob->get_price("sex in the woods")+" gold");
    write("%^BOLD%^%^BLACK%^Moonshine Float%^WHITE%^\t\t\t\t"+(int)ob->get_price("moonshine float")+" gold");
    write("%^BOLD%^%^BLACK%^Chocolate Moonshine%^WHITE%^\t\t\t"+(int)ob->get_price("chocolate moonshine")+" gold");
    write("\n");
    write("%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^BOLD%^*%^RESET%^%^MAGENTA%^~%^WHITE%^");
    return 1;
}

