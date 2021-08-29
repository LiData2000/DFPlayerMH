/*
 *	Copyright:	LiData2000
 *	name:		DFPlayer_Mudah test code
 *	Author:		LiData2000 source = lisper <lisper.li@dfrobot.com>
 *	Date:		28-08-2021
 *	Description:	mp3 library for DFPlayer mini board ic MH2024K-16SS
 *
 *	this code is test on arduino uno
 *	you can try input:
 *	mainkan
 *	mainkan(3)//play 01/003.mp3 
 *	lanjut		//play next
 *	mundur		//paly previous
 *	atur_suara(20) //set volume to 20 (0~30)
 */
 
#include <SoftwareSerial.h>
#include <DFPlayer_Mudah.h>

SoftwareSerial MySerial(10,11);

void setup () {
  Serial.begin (9600);
  MySerial.begin(9600);
  mp3_set_serial(MySerial); 
  inisial();
  atur_suara(1);
}

void loop () {        
  mainkan(3);
  delay (1000);
}
