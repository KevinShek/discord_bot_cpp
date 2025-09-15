#pragma once
#include <iostream>
#include <vector>

class DecodeAudio {

public:
	DecodeAudio() {
	}
	bool decode_mp3_to_pcm(const std::string& mp3_path, std::vector<uint8_t>& pcmdata);
	bool check_file(const std::string& mp3_path);
	void audio_to_discord(const dpp::slashcommand_t& event, std::vector<uint8_t>& pcmdata, std::string message);
};