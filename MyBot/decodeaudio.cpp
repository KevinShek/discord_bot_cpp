#include <fstream>
#include <iostream>
#include <vector>
#include <mpg123.h>
#include <dpp/dpp.h>
#include "decodeaudio.h"

bool DecodeAudio::check_file(const std::string& mp3_path)
{
	std::ifstream testfile(mp3_path);
	if (!testfile.is_open()) {
		std::cout << "C++ cannot open file at: " << mp3_path << "\n";
		return false;
	}
	else {
		std::cout << "C++ can open the file successfully.\n";
		return true;
	}
}

bool DecodeAudio::decode_mp3_to_pcm(const std::string& mp3_path, std::vector<uint8_t>& pcmdata) {

	if (check_file(mp3_path) == false)
	{
		return false;
	}

	if (mpg123_init() != MPG123_OK) {
		std::cout << "mpg123_init failed\n";
		return false;
	}

	int err = 0;
	mpg123_handle* mh = mpg123_new(NULL, &err);
	if (!mh) {
		std::cout << "mpg123_new failed: " << mpg123_plain_strerror(err) << "\n";
		mpg123_exit();
		return false;
	}

	// Set supported format
	mpg123_format_none(mh);
	mpg123_format(mh, 48000, MPG123_MONO, MPG123_ENC_SIGNED_16);
	mpg123_format(mh, 48000, MPG123_STEREO, MPG123_ENC_SIGNED_16);

	if (mpg123_open(mh, mp3_path.c_str()) != MPG123_OK) {
		std::cout << "mpg123_open failed: " << mpg123_strerror(mh) << "\n";
		mpg123_delete(mh);
		mpg123_exit();
		return false;
	}

	if (mpg123_open(mh, mp3_path.c_str()) != MPG123_OK) {
		std::cout << "Failed to open MP3: " << mpg123_strerror(mh) << "\n";
		std::cout << "Path used: " << mp3_path << "\n";
		return false;
	}

	long rate;
	int channels, encoding;
	mpg123_getformat(mh, &rate, &channels, &encoding);
	std::cout << "Opened MP3 with rate: " << rate << ", channels: " << channels << "\n";

	size_t buffer_size = mpg123_outblock(mh);
	std::vector<unsigned char> buffer(buffer_size);

	size_t done;
	pcmdata.clear();

	int result;
	while ((result = mpg123_read(mh, buffer.data(), buffer_size, &done)) == MPG123_OK) {
		pcmdata.insert(pcmdata.end(), buffer.begin(), buffer.begin() + done);
	}

	if (pcmdata.empty()) {
		std::cout << "Decoded 0 bytes\n";
	}

	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();

	std::cout << "Decoded " << pcmdata.size() << " bytes\n";

	return !pcmdata.empty();
}

void DecodeAudio::audio_to_discord(const dpp::slashcommand_t& event, std::vector<uint8_t>& pcmdata, std::string message)
{
	dpp::voiceconn* v = event.from()->get_voice(event.command.guild_id);
	if (v && v->voiceclient) {
		v->voiceclient->send_audio_raw((uint16_t*)pcmdata.data(), pcmdata.size());
		event.edit_response(message);
	}
	else {
		/*event.edit_response("Voice connection not ready.");*/
		event.edit_response("Voice connection not ready.");
	}
}