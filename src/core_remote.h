/*
Copyright (c) 2014 Tobias Schramm

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


Init packet:
	[0]						Type indicator (0 for transmission start)
	[1..5]					Address
	[6..8]					Response challenge
	[9..10]					Number of packets
	[11]					Operation
	[12..13]				Field index
	
	Operation = 0 => read
	Operation = 1 => write
	
Connection ACK packet
	[0]						Type indicator (100 for connection ACK packet)
	[1..3]					Challenge
	[4..6]					Response challenge
	
Connection NAK packet
	[0]						Type indicator (101 for connection NAK packet)
	[1..3]					Challenge
	[4..6]					Response challenge
	
Data packet
	[0]						Type indicator (1 for data packet)
	[1..3]					Challenge
	[4..6]					Response challenge
	[7]						Packet length
	[8..31]					Data
*/

#ifndef __OHC_CORE_REMOTE_H__
#define __OHC_CORE_REMOTE_H__
	
	//Typedef
	typedef struct
	{
		uint8_t*	my_challenge;
		uint8_t*	remote_challenge;
		uint16_t	packet_counter;
		uint16_t	length;
	}
	ohc_core_remote_connection_t;

	//Exit codes
	#define CORE_REMOTE_ERROR_ADDR_TOO_SHORT	100
	#define CORE_REMOTE_ERROR_ADDR_TOO_LONG		101
	#define CORE_REMOTE_ERROR_PAYLOAD_TOO_LONG	102
	
	#define CORE_REMOTE_PACKET_OVERHEAD			8
	#define CORE_REMOTE_CHALLENGE_LENGTH		3
		
	#if WIRELESS_PACK_LEN <= CORE_REMOTE_PACKET_OVERHEAD
		#error "NRF24L01 packet too short to store any data"
	#endif
	
	extern uint8_t core_remote_init(uint8_t* addr, uint8_t addr_len);
	extern uint8_t core_remote_write_field(uint8_t* addr, uint8_t addr_len, uint16_t id, uint8_t* data, uint16_t offset, uint16_t length);
	extern uint8_t core_remote_main(void);
	
	#include "core_remote.c"
#endif