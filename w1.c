#include "w1.h"

#define W1_PORT PORTD
#define W1_BIT  PD3

#define OW_GET_IN()   (iopBit(W1_PORT, W1_BIT))
//#define OW_OUT_LOW()  ( W1_PORT &= (~(1 << W1_BIT)) )
#define OW_OUT_LOW()  (iopLow(W1_PORT, bv(W1_BIT)))
//#define OW_OUT_HIGH() ( W1_PORT |= (1 << W1_BIT) )
#define OW_DIR_IN()   (iopInput(W1_PORT, bv(W1_BIT)))
#define OW_DIR_OUT()  (iopOutput(W1_PORT, bv(W1_BIT))

uint8_t w1Reset(void)
{
  uint8_t err;
  iopOutputLow(W1_PORT, bv(W1_BIT));
  _delay_us(480);      
  
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){    
    // set Pin as input - wait for clients to pull low
    OW_DIR_IN(); // input
    //    OW_OUT_HIGH(); // pullup    
    _delay_us(66);
    err = OW_GET_IN();
  }
  
  // after a delay the clients should release the line
  // and input-pin gets back to high due to pull-up-resistor
  _delay_us(480 - 66);
  if( OW_GET_IN() == 0 ){		// short circuit
    err = 1;
  }
  return err;
}

extern uint8_t w1rw( uint8_t data )
{
	for(uint8_t i = 8; i > 0; i--){
	  _delay_us(15); // ����������� ��������	    
	  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){      
      iopOutputLow(W1_PORT, bv(W1_BIT));
      
  	  _delay_us(5);  // ����������� ����� ��� �������� 1
      
      if( data & 1 ){
    	  OW_DIR_IN();  // w1 high, ���� �������� 1
  	  }
      
      data >>= 1; // ���������� "�������" ������
  	  _delay_us(5);
      if( OW_GET_IN() ){ // ������ ���
    	  data |= 0x80;
  	  }
	  }
	  _delay_us(60 - 12); // ����� �����
    //  OW_OUT_HIGH();
	  OW_DIR_IN();  // w1 high
  }    
	return data;
}


//uint8_t ow_rom_search( uint8_t diff, uint8_t *id )
//{
	//uint8_t i, j, next_diff;
	//uint8_t b;
	//
	//if( ow_reset() ) return OW_PRESENCE_ERR;	// error, no device found
	//
	//ow_byte_wr( OW_SEARCH_ROM );			// ROM search command
	//next_diff = OW_LAST_DEVICE;			// unchanged on last device
	//
	//i = OW_ROMCODE_SIZE * 8;					// 8 bytes
	//
	//do {
		//j = 8;					// 8 bits
		//do {
			//b = ow_bit_io( 1 );			// read bit
			//if( ow_bit_io( 1 ) ) {			// read complement bit
				//if( b )					// 11
				//return OW_DATA_ERR;			// data error
			//}
			//else {
				//if( !b ) {				// 00 = 2 devices
					//if( diff > i || ((*id & 1) && diff != i) ) {
					//b = 1;				// now 1
					//next_diff = i;			// next pass 0
					//}
				//}
			//}
			//ow_bit_io( b );     			// write bit
			//*id >>= 1;
			//if( b ) *id |= 0x80;			// store bit
			//
			//i--;
			//
		//} while( --j );
		//
		//id++;					// next byte
	//
	//} while( i );
	//
	//return next_diff;				// to continue search
//}
//

//void w1Command( uint8_t command, uint8_t *id )
//{
	//uint8_t i;
//
	//w1Reset();
//
	//if( id ) {
		//ow_byte_wr( OW_MATCH_ROM );			// to a single device
		//i = OW_ROMCODE_SIZE;
		//do {
			//ow_byte_wr( *id );
			//id++;
		//} while( --i );
	//} 
	//else {
		//ow_byte_wr( OW_SKIP_ROM );			// to all devices
	//}
	//
	//ow_byte_wr( command );
//}

/*
  ��������� �������� ���������� ����� crc ����������� ���� ��� ����� b.
  ���������� ���������� �������� ����������� �����  
  */
extern uint8_t w1CRCUpdate(uint8_t crc, uint8_t b) {
  //  return pgm_read_byte(&onewire_crc_table[crc ^ b]);
  for (uint8_t p = 8; p; p--) {
    crc = ((crc ^ b) & 1) ? (crc >> 1) ^ 0b10001100 : (crc >> 1);
    b >>= 1;
  }
  return crc;
}

//const uint8_t PROGMEM onewire_crc_table[] = {
  //0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
  //0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
  //0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
  //0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
  //0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
  //0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
  //0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
  //0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
  //0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
  //0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
  //0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
  //0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
  //0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
  //0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
  //0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
  //0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35
//};
//
//// ��������� �������� ���������� ����� crc ����������� ���� ��� ����� b.
//// ���������� ���������� �������� ����������� �����
//inline uint8_t onewire_crc_update(uint8_t crc, uint8_t b) {
  //return pgm_read_byte(&onewire_crc_table[crc ^ b]);
//}