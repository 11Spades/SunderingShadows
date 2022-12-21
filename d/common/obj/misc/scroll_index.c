// modified scroll satchels, originally by Lujke

#include <std.h>
#include <move.h>

inherit "/std/bag_logic";

string order;

void create(){
    set_name("scroll index");
    set_id(({ "scroll index", "case", "scroll case", "leather case", "leather case with copper adornments" }));
    set_short("%^RESET%^%^CRST%^%^C136%^le%^C100%^a%^C136%^the%^C100%^r %^C136%^ca%^C100%^s%^C136%^e %^C058%^with %^C208%^c%^C214%^o%^C220%^pp%^C214%^e%^C208%^r ad%^C214%^or%^C220%^nm%^C214%^en%^C208%^ts%^CRST%^");
    set_weight(6);
    set_long((: this_object(), "long_desc" :));
    
    set_lore("%^RESET%^%^CYAN%^Designed as yet another tool for a prepared rogue, these cases hold a few scrolls within leather tubes to be kept within easy reach for an emergency. They are an odd marriage of engineering and magic, spring-loaded to save on time while possessing a few protective enchantments to keep the scrolls pristine.%^RESET%^");
    set_property("lore difficulty", 15);
    set_value(1000);
    set_cointype("gold");
    
    set_max_internal_encumbrance(15);
}

void init(){
    ::init();
    add_action("index_cast", "index");
    add_action("read_case", "read");
    add_action("order_scrolls", "order");
    
    call_out("check_scroll_index_count",1);
}

string long_desc(){
    return "%^RESET%^%^CRST%^%^C058%^At a glance, this is a series of %^C136%^har%^C100%^d%^C136%^en%^C100%^e%^C136%^d lea%^C100%^t%^C136%^he%^C100%^r %^C136%^t%^C100%^u%^C136%^be%^C100%^s %^RESET%^%^C058%^covered with odd %^C208%^c%^C214%^o%^C220%^pp%^C214%^e%^C208%^r ad%^C214%^or%^C220%^nm%^C214%^en%^C208%^ts%^RESET%^%^C058%^. Small %^C144%^buttons %^C058%^at the top of each tube can be pressed, popping the spring-loaded cap and launching the contents out with alacrity. Small %^C100%^writing %^C058%^can be seen on the side of the case.%^CRST%^\n";
}

string query_long(string str){
    string desc, tmp, * true_inv;
    object* inv, scrollcase;
    mapping myInv;
    int j, i;
    scrollcase = this_object();

    desc = long_desc() + "\n";
    inv = all_inventory(scrollcase);
    if(!sizeof(inv)) return desc;
    
    myInv = ([]);
    for(i = 0; i < sizeof(inv); i++){
        if(inv[i]->is_disease()) continue;
        tmp = inv[i]->query_short();
        if(member_array(tmp, keys(myInv)) != -1) myInv[tmp]["quantity"]++;
        else myInv += ([tmp:(["quantity" : 1, "short" : tmp]), ]);
        continue;
    }

    if(!sizeof(keys(myInv))) return desc;
    if(stringp(desc)) desc += arrange_string("%^RESET%^%^CRST%^It contains:", 50) + "Amount\n";
    else desc = "  It contains: \n";
    true_inv = sort_array(keys(myInv), (: strcmp("/daemon/filters_d.c"->filter_colors($1),"/daemon/filters_d.c"->filter_colors($2)) :));
    for(i = 0; i < sizeof(true_inv); i++){
        j = 55 - strlen("/daemon/filters_d.c"->filter_colors(myInv[true_inv[i]]["short"]));
        desc += myInv[true_inv[i]]["short"] + arrange_string(" ", j) + myInv[true_inv[i]]["quantity"] + "\n";
    }

    return desc;
}

int order_scrolls(string str){
    object player, room;
    player = this_player();
    room = environment(player);
    
    if(str == "scrolls by level"){
        tell_object(player, "%^RESET%^%^CRST%^%^C058%^You quickly sort the scrolls into cases according to their spell level.%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ quickly shuffles the contents of their case.%^CRST%^", player);
        order_contents_alphabetically();
        order_contents_by_spell_level();
        return 1;
    }
    if(str == "scrolls alphabetically"){
        tell_object(player, "%^RESET%^%^CRST%^%^C058%^You quickly sort the scrolls into cases according to alphabetical order.%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ quickly shuffles the contents of their case.%^CRST%^", player);
        order_contents_alphabetically();
        return 1;
    }
    return notify_fail("Do you want to 'order scrolls by level' or 'order scrolls alphabetically'?");
}

int item_allowed(object item){
    string *ids = ({}), stuff = ({ "scroll", "paper", "parchment" });
    int i;

    ids = item->query_id();
    for(i=0;i<sizeof(ids);i++) if(member_array(ids[i],stuff) != -1) return 1;

    write("%^RESET%^%^CRST%^%^C196%^You can only put scrolls, paper, and parchment in this.%^CRST%^");
    return 0;
}

int read_case(string str){
    if(!objectp(this_object())||!objectp(environment(this_object()))) return 0;
    if(str!="case") return 0;
    
    tell_object(this_player(),"%^RESET%^%^CRST%^%^BOLD%^%^RED%^To use the index, press the button to the side of the proper case.\n%^BOLD%^%^YELLOW%^<index 'spell name' on 'target name'>\n\n%^BOLD%^%^RED%^To sort your scrolls conveniently:\n%^BOLD%^%^YELLOW%^<order scrolls by level>\n%^BOLD%^%^YELLOW%^<order scrolls alphabetically>\n%^RESET%^");
    return 1;
}

int index_cast(string str){
    string spellname, targetname, *input;
    object *ob, scrollcase, player, room;
    
    scrollcase = this_object();
    player = this_player();
    room = environment(player);
    
    if(!objectp(scrollcase) || !objectp(environment(scrollcase)) || !objectp(player)) return 0;
    if(environment(scrollcase) != player){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^You have to be holding the scroll index to use it properly.%^CRST%^");
        return 1;
    }
    if(!str || strlen(str) < 3){
        tell_object(player, "%^RESET%^%^CRST%^%^C059%^Try 'index <spell name>' or index <spell name> on <target name>'.%^CRST%^");
        return 1;
    }
    
    input = explode(str, " on ");
    spellname = input[0];
    if(sizeof(input) > 1) targetname = implode(input[1..], " on ");
    
    if(!present(spellname, scrollcase)){
        tell_object(player, "%^RESET%^%^CRST%^%^C196%^There is no scroll with the spell "+spellname+" in the scroll index. Or at least, if there is your indexing has gone horribly wrong!%^CRST%^");
        tell_room(room, "%^RESET%^%^CRST%^%^C196%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C196%^ searches for a scroll in their scroll index, but doesn't seem to find what they're is looking for.%^CRST%^", ETO);
        return 1;
    }
    tell_object(player, "%^RESET%^%^CRST%^%^C058%^You tap lightly at a %^C100%^button %^C058%^along the case, ejecting a %^C144%^scroll %^C058%^into your awaiting hand!%^CRST%^");
    tell_room(room, "%^RESET%^%^CRST%^%^C058%^"+player->query_cap_name()+"%^RESET%^%^CRST%^%^C058%^ taps at their case and a %^C144%^scroll %^C058%^springs into their palm!%^CRST%^", player);
    
    player->force_me("get "+spellname+" from scroll index");
    if(targetname && sizeof(input) > 1) player->force_me("use "+spellname+" on "+targetname);
    else TP->force_me("use scroll");
    
    return 1;
}

void order_contents_alphabetically(){
    object item, next_item, * result, * contents, scrollcase;
    int i, j, count;
    string spellname, next_spellname;
    result = ({});
    scrollcase = this_object();
    contents = all_inventory(scrollcase);
    count = sizeof(contents);
    
    if(count < 1) return;
    next_item = 0;
    j = 0;
    while(sizeof(contents) > 0 && j < 50){
        j++;
        contents = all_inventory(scrollcase);
        count = sizeof(contents);
        next_item = 0;
        for(i = count - 1; i >= 0; i--){
            if(sizeof(result) > 0 && member_array(contents[i], result) != -1) continue;
            if(!objectp(next_item)){
                next_item = contents[i];
                next_spellname = next_item->query_spell_name();
            }
            if(contents[i]->query_spell_name() > next_spellname){
                next_item = contents[i];
                next_spellname = next_item->query_spell_name();
            }
        }
        result += ({ next_item });
        if(objectp(next_item)) next_item->move(environment(scrollcase));
    }
    for(i = 0; i < sizeof(result); i++){
        item = result[i];
        item->move(scrollcase);
    }
}

void order_contents_by_spell_level(){
    object item, next_item, * result, * contents, scrollcase;
    int i, j, count, spell_level, next_spell_level;
    result = ({});
    scrollcase = this_object();
    contents = all_inventory(scrollcase);
    count = sizeof(contents);
    
    if(count < 1) return;
    next_item = 0;
    j = 0;
    while(sizeof(contents) > 0 && j < 50){
        j++;
        contents = all_inventory(scrollcase);
        count = sizeof(contents);
        next_item = 0;
        for(i = count - 1; i >= 0; i--){
            if(sizeof(result) > 0 && member_array(contents[i], result) != -1) continue;
            if(!objectp(next_item)){
                next_item = contents[i];
                next_spell_level = next_item->query_spell_level();
            }
            if(contents[i]->query_spell_level() > next_spell_level){
                next_item = contents[i];
                next_spell_level = next_item->query_spell_level();
            }
        }
        result += ({ next_item });
        if(objectp(next_item)) next_item->move(environment(scrollcase));
    }
    for(i = 0; i < sizeof(result); i++){
        item = result[i];
        item->move(scrollcase);
    }
}

void check_scroll_index_count(){
    object player = this_player();
    if(player && collapse_array(all_inventory(player)->is_scroll_index()) > 1){
        tell_object(player, "%^RESET%^%^CRST%^%^B_RED%^%^BOLD%^%^YELLOW%^You have too many scroll index containers, the limit is one. Lower the amount held as soon as roleplay permits.%^RESET%^");
        call_out("check_scroll_index_count", 30);
        return;
    }
    remove_call_out("check_scroll_index_count");
}

int is_scroll_index(){
    return 1;
}

int isMagic(){ return 2; }

