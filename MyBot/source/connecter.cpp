#include "connecter.h"
#include <dpp/dpp.h>
//#include <fstream>
//#include <iostream>
//

void ConnectionToBot::joiner(const dpp::slashcommand_t& event)
{
	/* Get the guild */
	dpp::guild* g = dpp::find_guild(event.command.guild_id);

	/* Get the voice channel that the bot is currently in from this server (will return nullptr if we're not in a voice channel!) */
	auto current_vc = event.from()->get_voice(event.command.guild_id);

	bool join_vc = true;

	/* Are we in a voice channel? If so, let's see if we're in the right channel. */
	if (current_vc) {
		/* Find the channel id that the user is currently in */
		auto users_vc = g->voice_members.find(event.command.get_issuing_user().id);

		if (users_vc != g->voice_members.end() && current_vc->channel_id == users_vc->second.channel_id) {
			join_vc = false;

		}
		else {
			/* We are on a different voice channel. We should leave it, then join the new one
			 * by falling through to the join_vc branch below. */
			event.from()->disconnect_voice(event.command.guild_id);

			join_vc = true;
		}
	}

	/* If we need to join a vc at all, join it here if join_vc == true */
	if (join_vc) {
		/* Attempt to connect to a voice channel, returns false if we fail to connect. */
		/* The user issuing the command is not on any voice channel, we can't do anything */
		if (!g->connect_member_voice(event.command.get_issuing_user().id)) {
			event.reply("You don't seem to be in a voice channel!");
			return;
		}

		 /* Tell the user we joined their channel. */
		event.reply("Joined your channel!");
		return;
	}
	else {
		event.reply("Don't need to join your channel as i'm already there with you!");
		return;
	}
}

void ConnectionToBot::leaver(const dpp::slashcommand_t& event)
{
	/* Get the voice channel that the bot is currently in from this server (will return nullptr if we're not in a voice channel!) */
	auto current_vc = event.from()->get_voice(event.command.guild_id);

	if (current_vc != NULL)
	{
		event.from()->disconnect_voice(event.command.guild_id);
		event.reply("Left your channel!");
		return;
	}
	event.reply("Nope.");
}