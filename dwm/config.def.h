/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 0;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;        /* vert inner gap between windows */
static const unsigned int gappoh    = 0;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "UbuntuMono Nerd Font:style=Regular:size=15" };
static const char dmenufont[]       = "UbuntuMono Nerd Font:style=Regular:size=15";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cherry[]      = "#940d53";
static const char col_darkpurple[]  = "#25124d";
static const char col_black[]       = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 },
	[SchemeSel]  = { col_gray4, col_darkpurple,  col_darkpurple },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance          title          tags mask     isfloating   monitor */
	{ "R_x11",    NULL,             NULL,	         0,            1,           -1 },
	{ NULL,       NULL,             "Nice Window",   0,            1,           -1 },
	{ NULL,       "Godot_Engine",   NULL,	         0,            1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[]=",      tile },      /* first entry is default */
    { "><>",      NULL },      /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[\\]",     dwindle },
    { "|M|",      centeredmaster },
    { "[@]",      spiral },
	{ "===",      bstackhoriz },
    { "HHH",      grid },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, "--config-file", "/home/vic/.config/alacritty/scratchpad_alacritty.toml", NULL };
/* Launching apps */
static const char *browsercmd[]  = { "google-chrome-stable", NULL };
static const char *filescmd[]  = { "thunar", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *emailcmd[]  = { "thunderbird", NULL };
static const char *rstudiocmd[]  = { "rstudio", NULL };
static const char *teamscmd[]  = { "teams-for-linux", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *officecmd[]  = { "onlyoffice-desktopeditors", NULL };
static const char *whatsappcmd[]  = { "gtk-launch", "chrome-hnpfjngllnobngcgfapefoaidbinmjnm-Default.desktop", NULL };
static const char *youtubecmd[]  = { "xdg-open", "https://www.youtube.com/", NULL };
static const char *youtubemusiccmd[]  = { "gtk-launch", "chrome-cinhimbnkkaeohfgghhklpknlkffjgod-Default.desktop", NULL };
static const char *microsoft365cmd[]  = { "gtk-launch", "chrome-onhfoihkhodaeblmangmjjgfpfehnlkm-Default.desktop", NULL };
static const char *tmuxcmd[]  = { "alacritty", "-e", "tmux-sessionizer", NULL };
static const char *zoterocmd[]  = { "zotero", NULL };
static const char *nightycmd[]  = { "gammastep", "-m", "randr", "-P", "-O", "2800", NULL };
static const char *nightlightcmd[]  = { "gammastep", "-m", "randr", "-P", "-O", "4100", NULL };
static const char *nightoffcmd[]  = { "gammastep", "-m", "randr", "-P", "-O", "6500", NULL };
static const char *ridercmd[]  = { "rider", NULL };
static const char *audiocmd[]  = { "pavucontrol", NULL };
static const char *bluemancmd[]  = { "blueman-manager", NULL };
static const char *godotcmd[]  = { "godot", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { Mod4Mask,                     XK_p,      spawn,          {.v = roficmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },

    /* Launching apps */
    { Mod4Mask,                     XK_Return, spawn,          {.v = termcmd } },
	{ Mod4Mask,                     XK_b,      spawn,          {.v = browsercmd } },
	{ Mod4Mask,                     XK_e,      spawn,          {.v = filescmd } },
	{ Mod4Mask,                     XK_l,      spawn,          {.v = lockcmd } },
	{ Mod4Mask,                     XK_m,      spawn,          {.v = emailcmd } },
	{ Mod4Mask,                     XK_r,      spawn,          {.v = rstudiocmd } },
	{ Mod4Mask,                     XK_t,      spawn,          {.v = teamscmd } },
	{ Mod4Mask,                     XK_s,      spawn,          {.v = spotifycmd } },
	{ Mod4Mask,                     XK_o,      spawn,          {.v = officecmd } },
	{ Mod4Mask,                     XK_w,      spawn,          {.v = whatsappcmd } },
	{ Mod4Mask,                     XK_y,      spawn,          {.v = youtubecmd } },
	{ Mod4Mask|ShiftMask,           XK_y,      spawn,          {.v = youtubemusiccmd } },
	{ Mod4Mask,                     XK_3,      spawn,          {.v = microsoft365cmd } },
	{ Mod4Mask,                     XK_f,      spawn,          {.v = tmuxcmd } },
	{ Mod4Mask,                     XK_z,      spawn,          {.v = zoterocmd } },
	{ MODKEY|ShiftMask,             XK_Page_Up, spawn,         {.v = nightycmd } },
	{ MODKEY|ShiftMask,             XK_Page_Down, spawn,       {.v = nightlightcmd } },
	{ MODKEY,                       XK_End,    spawn,          {.v = nightoffcmd } },
	{ Mod4Mask,                     XK_j,      spawn,          {.v = ridercmd } },
	{ Mod4Mask,                     XK_a,      spawn,          {.v = audiocmd } },
	{ Mod4Mask,                     XK_i,      spawn,          {.v = bluemancmd } },
	{ Mod4Mask,                     XK_g,      spawn,          {.v = godotcmd } },


	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = +0.25} },
 	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = -0.25} },
 	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    comboview,      {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_i,      incrgaps,       {.i = +1 } },
    { MODKEY,                       XK_d,      incrgaps,       {.i = -1 } },
    { MODKEY,                       XK_g,      togglegaps,     {0} },
    { Mod4Mask,                     XK_0,      defaultgaps,    {0} },
	{ Mod4Mask,                     XK_1,      setlayout,      {.v = &layouts[3]} },
	{ Mod4Mask,                     XK_2,      setlayout,      {.v = &layouts[4]} },
	{ Mod4Mask,                     XK_4,      setlayout,      {.v = &layouts[5]} },
	{ Mod4Mask,                     XK_5,      setlayout,      {.v = &layouts[6]} },
	{ Mod4Mask,                     XK_6,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

