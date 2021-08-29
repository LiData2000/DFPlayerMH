/*
 *	name:		DFPlayer_Mudah
 *	version:	1.0
 *	Author:		lidata2000
 *	Date:		29-08-2021
 *	Description: mp3 library for DFPlayer MP3-TF-16P specially ic mh2024k-16ss
 *		   note: mp3 file must put into 01 folder in your tf card and namefile sould be "001.mp3" etc
 */
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DFPlayer_Mudah.h"

extern uint8_t send_buf[8] = {
 0x7E, 0xFF, 06, 00, 00, 00, 00, 0xEF};
extern uint8_t recv_buf[8];

static void(*send_func)() = NULL;
static HardwareSerial * _hardware_serial = NULL;
static SoftwareSerial * _software_serial = NULL;
static boolean is_reply = false;


void mp3_set_reply (boolean state) {
	is_reply = state;
	send_buf[4] = is_reply;
}

void h_send_func() {
	for (int i=0; i<8; i++) {
		_hardware_serial->write (send_buf[i]);
	}
}

//
void s_send_func() {
	for (int i=0; i<8; i++) {
		_software_serial->write (send_buf[i]);
	}
}

//
//void mp3_set_serial (HardwareSerial *theSerial) {
void mp3_set_serial (HardwareSerial &theSerial) {
	_hardware_serial = &theSerial;
	send_func = h_send_func;
}

//
void mp3_set_serial (SoftwareSerial &theSerial) {
	_software_serial = &theSerial;
	send_func = s_send_func;
}

//
void mp3_send_cmd (uint8_t cmd, uint16_t arg) {
	send_buf[3] = cmd;
	send_buf[5] = (int8_t)(arg >> 8);//datah
	send_buf[6] = (int8_t)(arg); //datal
	send_func();
}

void mp3_send_cmd (uint8_t cmd) {
	send_buf[3] = cmd;
	send_func ();
}

void inisial(){
    mp3_send_cmd(CMD_SEL_DEV,DEV_TF);    
    mp3_send_cmd(CMD_PLAY_W_VOL,0X0F01);
} 

void atur_suara(int besar){
    mp3_send_cmd(CMD_SET_VOLUME,besar);
    delay(20);
}

void mainkan(int urutan){
    mp3_send_cmd(CMD_PLAY_W_INDEX,urutan);
    delay(20);
}

void lanjut(){
    mp3_send_cmd(CMD_NEXT_SONG);
    delay(20);
}

void mundur(){
    mp3_send_cmd(CMD_PREV_SONG);
    delay(20);
}
