// Chernobog (5/20/22)
// Player Housing Item Storage

#include <std.h>
inherit BAG;

string filename, long_description;

void create(){
    ::create();
    set_name("storage");
    set_id(({"storage"}));
    set_short("storage");
    set_long((: this_object(), "long_desc" :));
    set_max_internal_encumbrance(500);
    set_weight(1000000);
    set_value(0);
    set_property("no animate",1);
    long_description = "This is a large box meant to contain a miscellaneous collection of items.";
}

void setup_wardrobe(string location){
    filename = "/d/save/storage/"+location;
    "/daemon/yuck_d"->load_inventory(this_object(), filename);
}

int remove(){
    save_wardrobe();
    all_inventory(this_object())->remove();
    ::remove();
}

void save_wardrobe(){
    object storage = this_object();
    
    if(!objectp(storage)) return;
    if(!objectp(environment(storage))) return;

    mkdir("/d/save/storage");
    mkdir(filename);
    "/daemon/yuck_d"->save_inventory(storage, filename);
}

void long_desc_set(string str){
    long_description = str;
    return;
}

string long_desc(){
    return long_description;
}

string query_long(string str){
    string desc, tmp, * true_inv;
    object* inv;
    mapping myInv;
    int j, i;

    desc = long_desc();
    inv = all_inventory(TO);
    if (!sizeof(inv)) return desc;
    myInv = ([]);
    for(i = 0; i < sizeof(inv); i++){
        if(inv[i]->is_disease()) continue;
        tmp = inv[i]->query_short();
        if(member_array(tmp, keys(myInv)) != -1) myInv[tmp]["quantity"]++;
        else myInv += ([tmp:(["quantity" : 1, "short" : tmp]), ]);
        continue;
    }

    if(!sizeof(keys(myInv))) return desc;
    if(stringp(desc)) desc += arrange_string("It contains:", 50) + "Amount\n";
    else desc = "  It contains: \n";
    true_inv = sort_array(keys(myInv), (: strcmp("/daemon/filters_d.c"->filter_colors($1),"/daemon/filters_d.c"->filter_colors($2)) :));
    for(i = 0; i < sizeof(true_inv); i++){
        j = 55 - strlen("/daemon/filters_d.c"->filter_colors(myInv[true_inv[i]]["short"]));
        desc += myInv[true_inv[i]]["short"] + arrange_string(" ", j) + myInv[true_inv[i]]["quantity"] + "\n";
    }

    return desc;
}

