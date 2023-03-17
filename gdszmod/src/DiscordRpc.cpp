#include "DiscordRpc.h"

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("1078005101244973066", &Handle, 1, NULL);
}

void Discord::Update()
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = "Recreation by user666";
	discordPresence.largeImageKey = "sz_icon";
	Discord_UpdatePresence(&discordPresence);
}