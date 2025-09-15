#include <dpp/dpp.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include "joinleave.h"
#include "decodeaudio.h"
#include "Connection.h"
#include <cstdlib>

int main() {

	std::vector<uint8_t> pcmdata;
	JoinLeaveBot ToBot;
	DecodeAudio DecodeSound;
	EnvLoader DiscordServer;

	// Grab Token
	std::string path = R"(D:\projects\coding_for_fun\.env)";
	DiscordServer.load_env_file(path);
	std::string token = DiscordServer.get_env_var("BOT_TOKEN");
	if (token.empty()) {
		std::cerr << "BOT_TOKEN not set or empty in .env\n";
		return 1;
	}

	/* Setup the bot */
	//dpp::cluster bot(BOT_TOKEN);
	dpp::cluster bot(token);

	bot.on_log(dpp::utility::cout_logger());

	/* The event is fired when someone issues your commands */
	bot.on_slashcommand([&bot, &pcmdata, &ToBot, &DecodeSound](const dpp::slashcommand_t& event) {

		/* Check which command they ran */
		if (event.command.get_command_name() == "join") {
			ToBot.joiner(event);
		}
		else if (event.command.get_command_name() == "leave") {
			ToBot.leaver(event);
		}
		else if (event.command.get_command_name() == "talker") {
			// join voice channel if not already in the voice channel
			ToBot.joiner(event);

			std::string UserMessage = std::get<std::string>(event.get_parameter("message"));


			event.reply(UserMessage);
		}
		else if (event.command.get_command_name() == "pain") {
			// join voice channel if not already in the voice channel
			ToBot.joiner(event);
			// this is important as discord typically waits for 3 seconds to hear response from the bot otherwise discord forces the bot to close
			event.thinking();
			const std::string music_path = R"(D:\projects\coding_for_fun\windows-bot-template-main\windows-bot-template-main\sounds\pain_peko.mp3)";
			bool AudioArrived = DecodeSound.decode_mp3_to_pcm(music_path, pcmdata);
			DecodeSound.audio_to_discord(event, pcmdata, "pain peko");
		}
		else if (event.command.get_command_name() == "painpeko") {
			// join voice channel if not already in the voice channel
			ToBot.joiner(event);
			// this is important as discord typically waits for 3 seconds to hear response from the bot otherwise discord forces the bot to close
			event.thinking();
			const std::string music_path = R"(D:\projects\coding_for_fun\windows-bot-template-main\windows-bot-template-main\sounds\pain_peko_full.mp3)";
			bool AudioArrived = DecodeSound.decode_mp3_to_pcm(music_path, pcmdata);
			DecodeSound.audio_to_discord(event, pcmdata, "Pain Peko!");
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			/* Create a new command. */
			bot.global_command_create(dpp::slashcommand("join", "Joins your voice channel.", bot.me.id));
			bot.global_command_create(dpp::slashcommand("leave", "leave your voice channel.", bot.me.id));
			bot.global_command_create(dpp::slashcommand("pain", "pain peko short form.", bot.me.id));
			bot.global_command_create(dpp::slashcommand("painpeko", "pain peko full form.", bot.me.id));
			bot.global_command_create(dpp::slashcommand("talker", "Reads your message.", bot.me.id)
				.add_option(dpp::command_option(dpp::co_string, "message", "Message to echo", true)));
		}
	});

	/* Start bot */
	bot.start(dpp::st_wait);
	
	return 0;
}
