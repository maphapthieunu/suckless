/* 
See LICENSE file for copyright and license details.
Based on config.def.h lol
yay -S nerd-fonts-jetbrains-mono for font
*/

/* appearance */
static const unsigned int borderpx		= 0;
static const unsigned int snap			= 0;
static const unsigned int showsystray		= 1;
static const unsigned int systraypinning	= 0;
static const unsigned int systrayonleft		= 1;
static const unsigned int systrayspacing	= 4;
static const unsigned int gappx			= 10;
static const int systraypinningfailfirst	= 1;
static const int showbar			= 1;
static const int topbar				= 1;
static const char *fonts[]			= { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]			= { "JetBrainsMono Nerd Font:size=10" };
static const int horizpadbar			= 2;
static const int vertpadbar			= 8;
static const char *colors[][3]			= {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#f8f8f2", "#1e1f29", "#1e1f29" },
	[SchemeSel]  = { "#725397", "#1e1f29", "#1e1f29" },
};

/* tagging */
static const char *tags[] = { "ﲾ", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]			= "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]		= { "rofi", "-show", "drun", "-font", "'JetBrainsMono Nerd Font'", NULL };
static const char *termcmd[]		= { "kitty", NULL };
static const char *fm[]			= { "thunar", NULL };
static const char *upvol[]		= { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol[]		= { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[]		= { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brightnessup[]	= { "xbacklight", "-inc", "2", NULL };
static const char *brightnessdown[]	= { "xbacklight", "-dec", "2", NULL };
static Key keys[] = {
	/* modifier                     key				function	argument */
	{ MODKEY,			XK_s,				spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_Return,			spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,				togglebar,      {0} },
	{ Mod1Mask,			XK_Tab,				focusstack,     {.i = +1 } },
	{ Mod1Mask|ShiftMask,		XK_Tab,				focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,				incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_j,				incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,				setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,				setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_g,				zoom,           {0} },
	{ MODKEY,                       XK_Tab,				view,           {0} },
	{ Mod1Mask,			XK_F4,				killclient,     {0} },
	{ MODKEY,                       XK_t,				setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,				setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,				setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,			setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,			togglefloating, {0} },
	{ MODKEY,                       XK_0,				view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,				tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,			tagmon,         {.i = +1 } },
	{ MODKEY,			XK_e,				spawn,		{.v = fm } },
	TAGKEYS(                        XK_1,                      			0)
	TAGKEYS(                        XK_2,                      			1)
	TAGKEYS(                        XK_3,                      			2)
	TAGKEYS(                        XK_4,                      			3)
	TAGKEYS(                        XK_5,                      			4)
	TAGKEYS(                        XK_6,                      			5)
	TAGKEYS(                        XK_7,                      			6)
	TAGKEYS(                        XK_8,                      			7)
	TAGKEYS(                        XK_9,                      			8)
	{ MODKEY|ShiftMask,             XK_e,				quit,		{0} },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,		{.v = downvol} },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,		{.v = upvol} },
	{ 0,				XF86XK_AudioMute,		spawn,		{.v = mutevol} },
	{ 0,				XF86XK_MonBrightnessUp,		spawn,		{.v = brightnessup} },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,		{.v = brightnessdown} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

