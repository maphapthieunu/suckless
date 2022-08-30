/* 
See LICENSE file for copyright and license details.
On Arch Linux, install nerd-fonts-jetbrains-mono from AUR for the font.
*/

/* appearance */
static const unsigned int borderpx		= 2;
static const unsigned int snap			= 0;
static const unsigned int showsystray		= 1;
static const unsigned int systraypinning	= 0;
static const unsigned int systrayonleft		= 1;
static const unsigned int systrayspacing	= 4;
static const unsigned int gappx			= 10;
static const int systraypinningfailfirst	= 1;
static const int showbar			= 1;
static const int topbar				= 1;
static int vp					= 10;
static int sp					= 10;
static const char *fonts[]			= { "JetBrainsMono Nerd Font:size=10" };
static const int horizpadbar			= 2;
static const int vertpadbar			= 8;
static const char *colors[][3]			= {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#e0d4d0", "#0c0c0c", "#c0594b" },
	[SchemeSel]  = { "#fffaf5", "#0c0c0c", "#ff6650" },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg      border */
	[SchemeNorm] = { OPAQUE, OPAQUE, OPAQUE },
	[SchemeSel]  = { OPAQUE, OPAQUE, OPAQUE },
};

/* tagging */
static const char *tags[] = { "ﲾ", "", "ﭮ", "", "", "", "" };

static const unsigned int ulinepad	= 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

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
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *rofidrun[]		= { "rofi", "-show", "drun", NULL };
static const char *rofirun[]		= { "rofi", "-show", "run", NULL };
static const char *termcmd[]		= { "kitty", NULL };
static const char *fm[]			= { "nemo", NULL };
static const char *upvol[]		= { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol[]		= { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[]		= { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brightnessup[]	= { "xbacklight", "-inc", "2", NULL };
static const char *brightnessdown[]	= { "xbacklight", "-dec", "2", NULL };
static const char *settings[]		= { "xfce4-settings-manager", NULL };
static const char *powermenu[]		= { "rofi", "-show", "p", "-modi", "p:~/.local/bin/pm", NULL };
static const char *emoji[]		= { "ibus", "emoji", NULL };
static Key keys[] = {
	/* modifier                     	key				function	argument */
	{ MODKEY,				XK_s,				spawn,          {.v = rofidrun } },
	{ MODKEY,				XK_r,				spawn,          {.v = rofirun } },
	{ MODKEY,				XK_Return,			spawn,          {.v = termcmd } },
	{ MODKEY,				XK_e,				spawn,		{.v = fm } },
	{ MODKEY,				XK_i,				spawn,		{.v = settings } },
	{ MODKEY,				XK_semicolon,			spawn,		{.v = emoji } },
	{ MODKEY,				XK_period,			spawn,		{.v = emoji } },
	{ MODKEY,                       	XK_b,				togglebar,      {0} },
	{ Mod1Mask,				XK_Tab,				focusstack,     {.i = +1 } },
	{ Mod1Mask|ShiftMask,			XK_Tab,				focusstack,     {.i = -1 } },
	{ MODKEY,                       	XK_k,				incnmaster,     {.i = +1 } },
	{ MODKEY,                       	XK_j,				incnmaster,     {.i = -1 } },
	{ MODKEY,                       	XK_h,				setmfact,       {.f = -0.05} },
	{ MODKEY,                       	XK_l,				setmfact,       {.f = +0.05} },
	{ MODKEY,                       	XK_g,				zoom,           {0} },
	{ MODKEY,                       	XK_Tab,				view,           {0} },
	{ Mod1Mask,				XK_F4,				killclient,     {0} },
	{ MODKEY,                       	XK_t,				setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       	XK_f,				setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,                     	XK_m,				setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       	XK_space,			setlayout,      {0} },
	{ MODKEY|ShiftMask,             	XK_space,			togglefloating, {0} },
	{ MODKEY,                       	XK_comma,			focusmon,       {.i = -1 } },
	{ MODKEY,                       	XK_slash,			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             	XK_comma,			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             	XK_slash,			tagmon,         {.i = +1 } },
	TAGKEYS(                        	XK_1,                      			0)
	TAGKEYS(                        	XK_2,                      			1)
	TAGKEYS(                        	XK_3,                      			2)
	TAGKEYS(                        	XK_4,                      			3)
	TAGKEYS(                        	XK_5,                      			4)
	TAGKEYS(                        	XK_6,                      			5)
	TAGKEYS(                        	XK_7,                      			6)
	TAGKEYS(                        	XK_8,                      			7)
	TAGKEYS(                        	XK_9,                      			8)
	{ MODKEY|ShiftMask,             	XK_e,				quit,		{0} },
	{ 0,					XF86XK_AudioLowerVolume,	spawn,		{.v = downvol } },
	{ 0,					XF86XK_AudioRaiseVolume,	spawn,		{.v = upvol } },
	{ 0,					XF86XK_AudioMute,		spawn,		{.v = mutevol } },
	{ 0,					XF86XK_MonBrightnessUp,		spawn,		{.v = brightnessup } },
	{ 0,					XF86XK_MonBrightnessDown,	spawn,		{.v = brightnessdown } },
	{ ControlMask|Mod1Mask,			XK_Delete,			spawn,		{.v = powermenu } },
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            	{0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      	{0} },
	{ ClkStatusText,        0,              Button2,        spawn,          	{.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      	{0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, 	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    	{0} },
	{ ClkTagBar,            0,              Button1,        view,           	{0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     	{0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            	{0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      	{0} },
};
