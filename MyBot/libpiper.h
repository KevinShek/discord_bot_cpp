//#pragma once
//#ifndef LIBPIPER_HPP
//#define LIBPIPER_HPP
//
//#include <string>
//#include <vector>
//#include "../../../dependices/piper-master/src/cpp/piper.hpp"
//
//class LibPiper {
//public:
//    LibPiper(const std::string& modelPath,
//        const std::string& configPath,
//        const std::string& espeakPath,
//        bool useCuda = false);
//
//    ~LibPiper();
//
//    // Synthesizes audio from text into raw 16-bit PCM samples
//    bool synthesizeToPCM(const std::string& text, std::vector<int16_t>& outPcm);
//
//    // Synthesizes audio from text and writes it to a WAV file
//    bool synthesizeToWav(const std::string& text, const std::string& wavPath);
//
//private:
//    std::unique_ptr<piper::PiperConfig> config_;
//    piper::Voice voice_;
//    std::optional<piper::SpeakerId> speakerId_;
//};
//
//#endif // LIBPIPER_HPP
