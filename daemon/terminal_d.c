//      /obj/daemon/terminal_d.c
//      from the Nightmare Mudlib
//      Contains all the terminal information used to initialize
//      a player's terminal settings
//      created by Pinkfish@Discworld
//      rewritten for the Nightmare Mudlib by Descartes of Borg 930903

#define ANSI(p) sprintf("%c["+(p)+"m", 27)
#define ESC(p) sprintf("%c"+(p), 27)

static mapping term_info;

void create() {
    term_info = ([ "unknown":
                   ([ "RESET": "", "BOLD": "","ULINE": "", "FLASH":"", "BLACK":"", "RED":"", "BLUE":"", "CYAN":"", "MAGENTA":"", "ORANGE":"", "YELLOW":"", "GREEN":"", "WHITE":"", "BLACK":"", "B_RED":"", "B_ORANGE":"", "B_YELLOW":"", "B_BLACK":"", "B_CYAN":"","B_WHITE":"", "B_GREEN":"","B_BLUE":"", "B_MAGENTA":"", "STATUS":"", "WINDOW":"", "INITTERM": "","ENDTERM":""]),
                   "ansi":
                   ([ "RESET":ANSI("0;37;40"), "BOLD":ANSI(1), "ULINE":ANSI(4), "FLASH":ANSI(5), "BLACK":ANSI(30),"RED":ANSI(31), "GREEN":ANSI(32), "ORANGE":ANSI(33), "YELLOW":ANSI(1)+ANSI(33), "BLUE": ANSI(34), "CYAN":ANSI(36), "MAGENTA":ANSI(35), "BLACK":ANSI(30), "WHITE": ANSI(37), "B_RED":ANSI(41), "B_GREEN":ANSI(42), "B_ORANGE":ANSI(43), "B_YELLOW":ANSI(1)+ANSI(43), "B_BLUE":ANSI(44), "B_CYAN":ANSI(46), "B_BLACK":ANSI(40), "B_WHITE": ANSI(47), "B_MAGENTA":ANSI(45), "STATUS":"", "WINDOW":"", "INITTERM":"", "ENDTERM":"" ]),
                   "ansi-noblack":
                   ([ "RESET":ANSI("0;37;40"), "BOLD":ANSI(1), "ULINE":ANSI(4), "FLASH":ANSI(5), "BLACK":ANSI(34),"RED":ANSI(31), "GREEN":ANSI(32), "ORANGE":ANSI(33), "YELLOW":ANSI(1)+ANSI(33), "BLUE": ANSI(34), "CYAN":ANSI(36), "MAGENTA":ANSI(35), "BLACK":ANSI(34), "WHITE": ANSI(37), "B_RED":ANSI(41), "B_GREEN":ANSI(42), "B_ORANGE":ANSI(43), "B_YELLOW":ANSI(1)+ANSI(43), "B_BLUE":ANSI(44), "B_CYAN":ANSI(46), "B_BLACK":"", "B_WHITE": ANSI(47), "B_MAGENTA":ANSI(45), "STATUS":"", "WINDOW":"", "INITTERM":"", "ENDTERM":"" ]),                   
                   "ansi-nocolors":
                   ([ "RESET":ANSI(0), "BOLD":ANSI(1), "ULINE":ANSI(4), "FLASH":ANSI(5), "BLACK":"", "RED":"", "GREEN":"", "ORANGE":"", "YELLOW":ANSI(1), "BLUE":"" , "CYAN":"", "MAGENTA":"", "BLACK":"", "WHITE":ANSI(0) , "B_RED":"", "B_GREEN":"", "B_ORANGE":"", "B_YELLOW":"", "B_BLUE":"", "B_CYAN":"", "B_BLACK":"", "B_WHITE": "", "B_MAGENTA":"", "STATUS":"", "WINDOW":"", "INITTERM":"", "ENDTERM":"" ]),
                   "ansi-nobgcolors":
                   ([ "RESET":ANSI("0;37;40"), "BOLD":ANSI(1), "ULINE":ANSI(4), "FLASH":ANSI(5), "BLACK":ANSI(30), "RED":ANSI(31), "GREEN":ANSI(32), "ORANGE":ANSI(33), "YELLOW":ANSI(1)+ANSI(33), "BLUE": ANSI(34), "CYAN":ANSI(36), "MAGENTA":ANSI(35), "BLACK":ANSI(30), "WHITE": ANSI(37), "B_RED":"", "B_GREEN":"", "B_ORANGE":"", "B_YELLOW":"", "B_BLUE":"", "B_CYAN":"", "B_BLACK":"", "B_WHITE": "", "B_MAGENTA":"", "STATUS":"", "WINDOW":"", "INITTERM":"", "ENDTERM":"" ]),                   
                   "debug":
                   ([ "STATUS":"", "WINDOW":"", "INITTERM": "","ENDTERM":"" ]),
                     ]);
}

mapping query_term_info(string type) {
    return (term_info[type] ? term_info[type] : term_info["unknown"]);
}

string *query_terms() { return keys(term_info); }

int query_term_support(string str) {
    return (term_info[str] ? 1 : 0);
}

