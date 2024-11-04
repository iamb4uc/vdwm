/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 20;   /* gaps between windows */
static const unsigned int snap = 20;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 0;            /* 0 means bottom bar */
/* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as
 * bar height */
static const int user_bh = 0;
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=11:antialias=true"};
static const char dmenufont[] =
    "JetBrainsMono Nerd Font:size=15:antialias=true";
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t",     scratchpadname,
                                      "-g", "120x34", NULL};
/* 1 means swallow floating windows by default */
static const int swallowfloating = 1;
static const char col_gray1[] = "#282828";
static const char col_gray2[] = "#282828";
static const char col_gray3[] = "#ebdbb2";
static const char col_gray4[] = "#282828";
static const char col_cyan[] = "#ebdbb2";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
    [SchemeStatus] = {col_cyan, col_gray1, "#282828"},
    [SchemeTagsSel] = {col_gray4, col_cyan, "#282828"},
    [SchemeTagsNorm] = {col_gray3, col_gray1, "#282828"},
    [SchemeInfoSel] = {col_gray4, col_cyan, "#282828"},
    [SchemeInfoNorm] = {col_gray3, col_gray1, "#282828"},
};

/* tagging */
static const char *tags[] = {"I",  "II",  "III",  "IV", "V",
                             "VI", "VII", "VIII", "IX"};

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class             instance              title                      tags
       mask     isfloating   isterminal  noswallow  monitor */
    {"Gimp", NULL, NULL, 0, 0, 0, 0, -1},
    {"Firefox", NULL, NULL, 0, 0, 0, -1, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
    {"st-256color", "st-256color", "pulsemixer", 0, 1, 0, 0, -1},
    /*{"st-256color", "st-256color", "ncmpcpp", 0, 1, 0, 0, -1},*/
    {"st-256color", "st-256color", "peaclock", 0, 1, 0, 0, -1},
    {NULL, NULL, "Picture in picture", 0, 1, 0, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[T]", tile}, /* first entry is default */
    {"[F]", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {"[S]", spiral},
    {"[D]", dwindle},
    {"[CM]", centeredmaster},
    {"[CMf]", centeredfloatingmaster},
};

/*======= APPLICATIONS USED =======
 * Browser:              firefox
 * Notes:                obsidian
 * Ide:                  neovim
 * Music:                ncmpcpp + mpd
 * Terminal:             st
 * Application Launcher: dmenu
 * Network:              NetworkManager
 * Utility:              htop, pulsemixer, xbacklight
 * File Browser:         lf
 * Pdf Reader:           zathura
 * Mail:                 thunderbird
 * Password Manager:     keepassxc
 * Lock Screen:          slock
 */

/* TUI Application */
static const char *nvim[] = {"st", "-e", "nvim", NULL};
static const char *tmuxnew[] = {"st", "-e", "tmux", NULL};
static const char *tmuxattach[] = {"st", "-e", "tmux", "a", NULL};
static const char *fb[] = {"st", "-e", "lfub", NULL};
static const char *mixer[] = {"st", "-e", "pulsemixer", NULL};
static const char *htop[] = {"st", "-e", "htop", NULL};
static const char *music[] = {"st", "-e", "ncmpcpp", NULL};
static const char *netman[] = {"st", "-e", "nmtui", NULL};
static const char *netkill[] = {"nmcli", "r", "wifi", "off", NULL};
static const char *netrecover[] = {"nmcli", "r", "wifi", "on", NULL};
static const char *chkdsk[] = {"st", "-e", "ncdu", NULL};
static const char *exitses[] = {"sysact", NULL};

/* Music */
static const char *mpctoggle[] = {"mpc", "toggle", NULL};
static const char *mpcshuffle[] = {"mpc", "shuffle", NULL};
static const char *mpcnegvol[] = {"pamixer", "-d", "2", NULL};
static const char *mpcposvol[] = {"pamixer", "-i", "2", NULL};
static const char *mpcprev[] = {"mpc", "prev", NULL};
static const char *mpcnext[] = {"mpc", "next", NULL};

/* Display Brightness*/
static const char *brightup[] = {"xbacklight", "+2", NULL};
static const char *brightdn[] = {"xbacklight", "-2", NULL};
static const char *brightupsomemore[] = {"xbacklight", "+10", NULL};
static const char *brightdnsomemore[] = {"xbacklight", "-10", NULL};

/* Other Application */
static const char *web[] = {"firefox", NULL};
static const char *pass[] = {"keepassxc", NULL};
static const char *pdf[] = {"zathura", NULL};
static const char *ss[] = {"flameshot", "gui", NULL};
static const char *mail[] = {"thunderbird", NULL};
static const char *notes[] = {"obsidian", NULL};
static const char *slp[] = {"slock", "loginctl", "suspend", "-i", NULL};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *dmenucmd[] = {"dmenu_run", NULL};
static const char *termcmd[] = {"st", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */

    /*                       TERMINAL APPLICATIONS                      */
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = music}},
    {MODKEY | ShiftMask, XK_h, spawn, {.v = htop}},
    {MODKEY | ShiftMask, XK_v, spawn, {.v = nvim}},
    {MODKEY | ShiftMask, XK_t, spawn, {.v = tmuxnew}},
    {MODKEY | ShiftMask, XK_a, spawn, {.v = tmuxattach}},
    {MODKEY | ShiftMask, XK_f, spawn, {.v = fb}},
    {MODKEY | ShiftMask, XK_F4, spawn, {.v = mixer}},
    {MODKEY, XK_n, spawn, {.v = netman}},
    {MODKEY, XK_F8, spawn, {.v = netkill}},
    {MODKEY | ShiftMask, XK_F8, spawn, {.v = netrecover}},
    {MODKEY | ShiftMask, XK_F7, spawn, {.v = chkdsk}},
    {MODKEY | ShiftMask, XK_s, spawn, {.v = ss}},
    {MODKEY | ShiftMask, XK_p, togglescratch, {.v = scratchpadcmd}},

    /*                       NCMPCPP   CONTROLS                         */
    {MODKEY, XK_F2, spawn, {.v = mpcnegvol}},
    {MODKEY | ShiftMask, XK_F2, spawn, {.v = mpcprev}},
    {MODKEY, XK_F1, spawn, {.v = mpctoggle}},
    {MODKEY | ShiftMask, XK_F1, spawn, {.v = mpcshuffle}},
    {MODKEY, XK_F3, spawn, {.v = mpcposvol}},
    {MODKEY | ShiftMask, XK_F3, spawn, {.v = mpcnext}},

    /*                       BIGHTNESS CONTROLS                         */
    {MODKEY, XK_F5, spawn, {.v = brightdn}},
    {MODKEY, XK_F6, spawn, {.v = brightup}},
    {MODKEY | ShiftMask, XK_F5, spawn, {.v = brightdnsomemore}},
    {MODKEY | ShiftMask, XK_F6, spawn, {.v = brightupsomemore}},

    /*                       GUI      APPLICATIONS                      */
    {MODKEY | ShiftMask, XK_w, spawn, {.v = web}},
    {MODKEY | ShiftMask, XK_r, spawn, {.v = pdf}},
    {MODKEY | ShiftMask, XK_k, spawn, {.v = pass}},
    {MODKEY | ShiftMask, XK_F12, spawn, {.v = mail}},
    {MODKEY | ShiftMask, XK_n, spawn, {.v = notes}},

    /*                       dmenu    APPLICATIONS                      */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_q, spawn, {.v = exitses}},
    {MODKEY, XK_F11, spawn, {.v = slp}},

    /*                              DWM SETTINGS                        */
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_o, incnmaster, {.i = +1}},
    {MODKEY, XK_p, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_y, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_u, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_i, setlayout, {.v = &layouts[5]}},
    {MODKEY | ShiftMask, XK_i, setlayout, {.v = &layouts[6]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -2}},
    {MODKEY, XK_equal, setgaps, {.i = +2}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    {MODKEY | ShiftMask, XK_x, quit, {0}},
    {MODKEY | ControlMask | ShiftMask, XK_q, quit, {1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
