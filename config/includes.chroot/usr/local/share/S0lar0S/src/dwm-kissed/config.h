/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = { "Hack:size=10" };
static const char dmenufont[]       = "Hack:size=10";
static const char normbordercolor[] = "#090909";
static const char normbgcolor[]     = "#090909";
static const char normfgcolor[]     = "#828282";
static const char selbordercolor[]  = "#1E90FF";
static const char selbgcolor[]      = "#090909";
static const char selfgcolor[]      = "#1E90FF";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const double shade           = 0.6;      /* opacity of unfocussed clients */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */

#define NUMCOLORS 8
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border   foreground background        description                  statuscode
  { "#090909", "#828282", "#111111" },  /* normal   (grey on dark)       \x01 */
  { "#1E90FF", "#1E90FF", "#090909" },  /* selected (blue on dark)       \x02 */
  { "#1E90FF", "#090909", "#1E90FF" },  /* urgent   (selected inverted)  \x03 */
  { "#090909", "#00D210", "#090909" },  /* green                         \x04 */
  { "#090909", "#CCD200", "#090909" },  /* yellow                        \x05 */
  { "#090909", "#D25E00", "#090909" },  /* orange on black               \x06 */
  { "#090909", "#D20023", "#090909" },  /* red                           \x07 */
  { "#090909", "#ffffff", "#090909" },  /* nobug... */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "eml", "web", "irc", "vim", "vid", "gfx", "dev", "ftp", "p2p" };

static const Rule rules[] = {
	/* class              instance    title       tags mask  iscenterd  ifloating monitor */
	//{ "Thunderbird",      NULL,       NULL,       1 << 0,    0,         0,        -1 },
	//{ "Firefox",          NULL,       NULL,       1 << 1,    0,         0,        -1 },
	//{ "Gajim",            NULL,       NULL,       1 << 2,    0,         0,        -1 },
	//{ "Geany",            NULL,       NULL,       1 << 3,    0,         0,        -1 },
	//{ "Oggconvert",       NULL,       NULL,       1 << 4,    1,         1,        -1 },
	//{ "Handbrake-gtk",    NULL,       NULL,       1 << 4,    1,         1,        -1 },
	//{ "Avidemux",         NULL,       NULL,       1 << 4,    1,         1,        -1 },
	//{ "Gimp",             NULL,       NULL,       1 << 5,    0,         0,        -1 },
	//{ "Inkscape",         NULL,       NULL,       1 << 5,    0,         0,        -1 },
	//{ "Filezilla",        NULL,       NULL,       1 << 7,    0,         0,        -1 },
	//{ "Transmission-gtk", NULL,       NULL,       1 << 8,    0,         1,        -1 },
	{ NULL,               "scratchpad", NULL,     0,         1,         1,        -1 },
	{ NULL,               NULL,       "sound",    0,         1,         1,        -1 },
	{ NULL,               NULL,       "player",   0,         1,         1,        -1 },
	{ "XTerm",            NULL,       NULL,       0,         1,         1,        -1 },
	{ "feh",              NULL,       NULL,       0,         1,         1,        -1 },
	{ "XCalc",            NULL,       NULL,       0,         1,         1,        -1 },
	{ "Rox",              NULL,       NULL,       0,         1,         1,        -1 },
	//{ "Tor Browser",      NULL,       NULL,       0,         1,         1,        -1 },
	{ "Lxappearance",     NULL,       NULL,       0,         1,         1,        -1 },
	{ "mpv",              NULL,       NULL,       0,         1,         1,        -1 },
	{ "mplayer2",         NULL,       NULL,       0,         1,         1,        -1 },
	{ "Sxiv",             NULL,       NULL,       0,         1,         1,        -1 },
	{ "Cyclope",          NULL,       NULL,       0,         1,         1,        -1 },
	//{ "Surf",             NULL,       NULL,       0,         1,         1,        -1 },
	//{ "tabbed",           NULL,       NULL,       0,         1,         1,        -1 },
	{ "Tk",               NULL,       NULL,       0,         1,         1,        -1 },
	{ "trayer",           "panel",    NULL,       1 << 0,    0,         1,        -1 },
	{ NULL,               NULL,       "Library",  0,         1,         1,        -1 },
	{ "File-roller",      NULL,       NULL,       0,         1,         1,        -1 },
	{ "Redshift-config",  NULL,       NULL,       0,         1,         1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[0]",      monocle }, /* first entry is default */
	{ "[|]",       tile },    /* classic tiling */
	{ "[ ]",       NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask    // Alt as main modifier
#define MODKEY2 Mod4Mask   // Super as second modifier
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *tkmenucmd[] = { "tkmenu", NULL };
static const char *termcmd[]   = { "st", NULL };
static const char *xtermcmd[]  = { "xterm", "-geometry", "150x25", NULL };
static const char *scratcmd[]  = { "scratchpad", NULL };
static const char *watchcmd[]  = { "st", "-t", "infos system", "-e", "glances", NULL };
static const char *rangercmd[] = { "st", "-e", "ranger", NULL };
static const char *zikcmd[]    = { "st", "-t", "player", "-e", "mocp", NULL };
static const char *soundcmd[]  = { "st", "-t", "sound", "-e", "alsamixer", NULL };
static const char *filecmd[]   = { "pcmanfm", NULL };
static const char *webcmd[]    = { "surf", "file:///usr/local/share/kiss0s/help/kisstart.html", NULL };
static const char *torwebcmd[] = { "anonweb", NULL };
static const char *vimcmd[]    = { "st", "-t", "editor", "-e", "vim", NULL };
static const char *irccmd[]    = { "st", "-t", "irc", "-e", "weechat", NULL };
static const char *wallcmd[]   = { "dmenu_wall", NULL };

#include "push.c"
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_p,         spawn,          {.v = dmenucmd } },
	{ MODKEY2,                      XK_p,         spawn,          {.v = tkmenucmd } },
	{ MODKEY|ControlMask,           XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY2,                      XK_Return,    spawn,          {.v = scratcmd } },
	{ MODKEY2|ShiftMask,            XK_Return,    spawn,          {.v = xtermcmd } },
	{ MODKEY,                       XK_r,         spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_z,         spawn,          {.v = zikcmd } },
	{ MODKEY,                       XK_v,         spawn,          {.v = soundcmd } },
	{ MODKEY|ShiftMask,             XK_r,         spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_w,         spawn,          {.v = webcmd } },
	{ MODKEY2,                      XK_w,         spawn,          {.v = torwebcmd } },
	{ MODKEY,                       XK_e,         spawn,          {.v = vimcmd } },
	{ MODKEY,                       XK_x,         spawn,          {.v = irccmd } },
	{ MODKEY|ControlMask,           XK_w,         spawn,          {.v = wallcmd } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
    { MODKEY|ControlMask,           XK_j,         pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,         pushup,         {0} },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,     setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} },
	{ MODKEY,                       XK_agrave,    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_Left,      shiftview,      {.i = -1 } },
    { MODKEY|ControlMask,           XK_Right,     shiftview,      {.i = +1 } },
	TAGKEYS(                        XK_ampersand,                 0)
	TAGKEYS(                        XK_eacute,                    1)
	TAGKEYS(                        XK_quotedbl,                  2)
	TAGKEYS(                        XK_apostrophe,                3)
	TAGKEYS(                        XK_parenleft,                 4)
	TAGKEYS(                        XK_minus,                     5)
	TAGKEYS(                        XK_egrave,                    6)
	TAGKEYS(                        XK_underscore,                7)
	TAGKEYS(                        XK_ccedilla,                  8)
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = watchcmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = tkmenucmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

