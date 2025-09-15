//#include "libpiper.h"
//#include <fstream>
//#include <iostream>
//
////LibPiper::LibPiper(const std::string& modelPath,
////    const std::string& configPath,
////    const std::string& espeakPath,
////    bool useCuda) {
////    config_ = std::make_unique<piper::PiperConfig>();
////    config_->useESpeak = true;
////    config_->eSpeakDataPath = espeakPath;
////
////    piper::initialize(*config_);
////    piper::loadVoice(*config_, modelPath, configPath, voice_, speakerId_, useCuda);
////}
////
////LibPiper::~LibPiper() {
////    piper::terminate(*config_);
////}
//
//bool LibPiper::synthesizeToPCM(const std::string& text, std::vector<int16_t>& outPcm) {
//    piper::SynthesisResult result;
//    try {
//        piper::textToAudio(*config_, voice_, text, outPcm, result, []() {});
//        return true;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error during synthesis: " << e.what() << std::endl;
//        return false;
//    }
//}
//
//bool LibPiper::synthesizeToWav(const std::string& text, const std::string& wavPath) {
//    std::vector<int16_t> audioBuffer;
//    if (!synthesizeToPCM(text, audioBuffer))
//        return false;
//
//    std::ofstream outFile(wavPath, std::ios::binary);
//    if (!outFile)
//        return false;
//
//    uint32_t dataSize = audioBuffer.size() * sizeof(int16_t);
//    uint32_t sampleRate = voice_.synthesisConfig.sampleRate;
//    uint16_t channels = voice_.synthesisConfig.channels;
//    uint16_t bitsPerSample = voice_.synthesisConfig.sampleWidth * 8;
//
//    outFile.write("RIFF", 4);
//    uint32_t chunkSize = 36 + dataSize;
//    outFile.write(reinterpret_cast<const char*>(&chunkSize), 4);
//    outFile.write("WAVE", 4);
//
//    outFile.write("fmt ", 4);
//    uint32_t subChunk1Size = 16;
//    uint16_t audioFormat = 1;
//    outFile.write(reinterpret_cast<const char*>(&subChunk1Size), 4);
//    outFile.write(reinterpret_cast<const char*>(&audioFormat), 2);
//    outFile.write(reinterpret_cast<const char*>(&channels), 2);
//    outFile.write(reinterpret_cast<const char*>(&sampleRate), 4);
//    uint32_t byteRate = sampleRate * channels * bitsPerSample / 8;
//    outFile.write(reinterpret_cast<const char*>(&byteRate), 4);
//    uint16_t blockAlign = channels * bitsPerSample / 8;
//    outFile.write(reinterpret_cast<const char*>(&blockAlign), 2);
//    outFile.write(reinterpret_cast<const char*>(&bitsPerSample), 2);
//
//    outFile.write("data", 4);
//    outFile.write(reinterpret_cast<const char*>(&dataSize), 4);
//    outFile.write(reinterpret_cast<const char*>(audioBuffer.data()), dataSize);
//
//    return true;
//}
