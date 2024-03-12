#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Audio.h"
#include "Arduino.h"
#include "ezButton.h"
#include "sdcard.hpp"
#include "vector.hpp"

#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18

#define I2S_DOUT      22 
#define I2S_BCLK      14
#define I2S_LRC       15


Audio audio;
ezButton button_pause(2);
ezButton button_next(4);
ezButton button_volume_up(36);
ezButton button_volume_down(27);
ezButton button_select_up(25);
ezButton button_select_down(12);
ezButton button_select(26);

StringList songs; 
int currentSong = 0;
int volume = 10;
int activeSelection = 0;
bool isPlayingAudio = false;

bool playSong(const char* song) {
  Serial.println("Now Playing: " + songs.get(currentSong));
  return audio.connecttoSD(song);
}

bool playNext() {
    if (songs.get(currentSong + 1) == NULL) {
      currentSong = -1; // Negative one so that when one is added it makes 0
    } 
    audio.stopSong();
    activeSelection++;
    return playSong(("/" + songs.get(++currentSong)).c_str());
}

void printMenu() {
  Serial.println("---------Music Player Menu---------");
  Serial.println("Songs: ");
  for (int i = 0; i < songs.getSize(); i++) {
    Serial.println(songs.get(i));
  }

  Serial.println("Active Selection: " + songs.get(currentSong));
}


void setup(){
  pinMode(SD_CS, OUTPUT);      
  digitalWrite(SD_CS, HIGH);
  Serial.begin(115200);

  Serial.println("Starting program");

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  if(!SD.begin(SD_CS)){
    Serial.println("Card Mount Failed");
    return;
  }

  Serial.println("Card mount successful");

  // Add all the songs to the list
  songs = listAudioFiles("/", songs);
  // All Audio setup
  if (!audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT)) {
    Serial.println("Failed to set pinout");
    return;
  }

  Serial.println("Successfully Set Pinout");

  audio.setVolume(10);

  button_pause.setDebounceTime(50);
  button_next.setDebounceTime(50);
  button_volume_down.setDebounceTime(50);
  button_volume_up.setDebounceTime(50);
  button_select.setDebounceTime(50);
  button_select_up.setDebounceTime(50);
  button_select_down.setDebounceTime(50);

  Serial.println("Playing audio");


  // list all the songs
  printMenu();
}

void loop(){
  button_pause.loop();
  button_next.loop();
  button_volume_up.loop();
  button_volume_down.loop();
  button_select_up.loop();
  button_select_down.loop();
  button_select.loop();
  audio.loop();

  if (audio.isRunning()) {
  } else {
  }

  if (button_pause.isReleased()) {
    audio.pauseResume();
  }
  if (button_next.isReleased()) {
    playNext(); 
  }
  if (button_volume_up.isReleased()) {
    if (volume != 21) audio.setVolume(++volume);
  }
  if (button_volume_down.isReleased()) {
    if (volume != 0) audio.setVolume(--volume);
  }

  // Navigation
  if (button_select_up.isReleased()) {
    if (activeSelection == 0) activeSelection = songs.getSize();
    else activeSelection--;

    Serial.println("Active Selection: " + songs.get(activeSelection));
  } 
  if (button_select_down.isReleased()) {
    if (activeSelection == songs.getSize()) activeSelection = 0;
    else activeSelection++;

    Serial.println("Active Selection: " + songs.get(activeSelection));
  }
  if (button_select.isReleased()) {
    currentSong = activeSelection;
    audio.stopSong();
    playSong(("/" + songs.get(activeSelection)).c_str());
    isPlayingAudio = true;
  }

  if (isPlayingAudio && !audio.isRunning()) {
    playNext();
  }
}

// optional
// void audio_info(const char *info){
//     Serial.print("info        "); Serial.println(info);
// }
// void audio_id3data(const char *info){  //id3 metadata
//     Serial.print("id3data     ");Serial.println(info);
// }
// void audio_eof_mp3(const char *info){  //end of file
//     Serial.print("eof_mp3     ");Serial.println(info);
// }
// void audio_showstation(const char *info){
//     Serial.print("station     ");Serial.println(info);
// }
// void audio_showstreaminfo(const char *info){
//     Serial.print("streaminfo  ");Serial.println(info);
// }
// void audio_showstreamtitle(const char *info){
//     Serial.print("streamtitle ");Serial.println(info);
// }
// void audio_bitrate(const char *info){
//     Serial.print("bitrate     ");Serial.println(info);
// }
// void audio_commercial(const char *info){  //duration in sec
//     Serial.print("commercial  ");Serial.println(info);
// }
// void audio_icyurl(const char *info){  //homepage
//     Serial.print("icyurl      ");Serial.println(info);
// }
// void audio_lasthost(const char *info){  //stream URL played
//     Serial.print("lasthost    ");Serial.println(info);
// }
// void audio_eof_speech(const char *info){
//     Serial.print("eof_speech  ");Serial.println(info);
// }