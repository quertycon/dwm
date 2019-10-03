/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int gappx     = 16;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_purp[]	    = "#780692";
static const char col_gray5[]       = "#282828";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray5 },
	[SchemeSel]  = { col_gray4, col_purp,  col_purp  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, 0xd0, OPAQUE },
	[SchemeSel]  = { OPAQUE, 0xd0, OPAQUE },
};

/* tagging */
static const char *tags[] = { "1", "ꔮ", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "discord",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Vivaldi-stable",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Spotify",  NULL,       NULL,	      1 << 5,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ Mod1Mask,                     	KEY,      view,           {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask,           	KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,             	KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask|ShiftMask, 	KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *startupcmd[] = { "./scripts/startupscript.sh", NULL };

/* programs */
static const char *vscodecmd[]  = { "code", "-r", NULL };
static const char *browsercmd[] = { "vivaldi", NULL };
static const char *spotifycmd[] = { "spotfiy", NULL };
static const char *rangercmd[] = { "ranger", NULL };
static const char *discordcmd[] = { "discord", NULL };
static const char *telegramcmd[] = { "telegram-desktop", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 15  } },
	// CHANGED KEYBINDS
	{ Mod1Mask,		        XK_t,	   spawn,          {.v = termcmd } },
	{ Mod1Mask,                     XK_w,      killclient,     {0} },
	{ Mod1Mask,                     XK_s,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,		XK_p,      spawn,          {.v = startupcmd } },
	{ Mod1Mask,                     XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask,                     XK_l,      setmfact,       {.f = +0.05} },
//	{ Mod1Mask,                     XK_g,      setmfact,       {.f = 0.5} },
	{ Mod1Mask,                     XK_j,      focusstack,     {.i = +1 } },
	{ Mod1Mask,                     XK_k,      focusstack,     {.i = -1 } },
	{ Mod1Mask,                     XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },

	// Quickdial programs
	{ Mod1Mask,           			XK_c,      spawn,          {.v = vscodecmd } },
	{ Mod1Mask,           			XK_b,      spawn,          {.v = browsercmd } },
	{ Mod1Mask,           			XK_m,      spawn,          {.v = spotifycmd } },
	{ Mod1Mask,           			XK_f,      spawn,          {.v = rangercmd } },
	{ Mod1Mask,           			XK_d,      spawn,          {.v = discordcmd } },
	{ Mod1Mask,           			XK_i,      spawn,          {.v = telegramcmd } },
	// LOL WATSDIT
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
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
