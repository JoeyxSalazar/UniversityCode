`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:11:43 09/28/2013 
// Design Name: 
// Module Name:    sev_seg 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sev_seg_decoder(
    input  [3:0] num_in,					// number to display in binary form
    output reg [7:0] sev_seg_leds		// controls the eight individual LEDs in the 7-segment display 
    );

	 // lights up the proper LEDs for each digit (remember that the LEDs are active low)
	 always @(num_in)	 begin
		 case (num_in)			
			4'h0 		:	 sev_seg_leds[7:0] = 8'b10000001 ;
			4'h1 		:	 sev_seg_leds[7:0] = 8'b11110011 ;
			4'h2	 	:	 sev_seg_leds[7:0] = 8'b01001001 ;
			4'h3 		:	 sev_seg_leds[7:0] = 8'b01100001 ;
			4'h4 		:	 sev_seg_leds[7:0] = 8'b00110011;
			4'h5 		:	 sev_seg_leds[7:0] = 8'b00100101 ;
			4'h6 		:	 sev_seg_leds[7:0] = 8'b00000101 ;
			4'h7 		:	 sev_seg_leds[7:0] = 8'b11110001 ;
			4'h8 		:	 sev_seg_leds[7:0] = 8'b00000001 ;
			4'h9 		:	 sev_seg_leds[7:0] = 8'b00100001 ;
			4'hA 		:	 sev_seg_leds[7:0] = 8'b00010001 ;
			4'hB 		:	 sev_seg_leds[7:0] = 8'b00000111 ;
			4'hC 		:	 sev_seg_leds[7:0] = 8'b10001101 ;
			4'hD 		:	 sev_seg_leds[7:0] = 8'b01000011 ;
			4'hE 		:	 sev_seg_leds[7:0] = 8'b00001101 ;
			4'hF 		:	 sev_seg_leds[7:0] = 8'b00011101 ;	
		   default 	: 	 sev_seg_leds[7:0] = 8'b01111111 ;
		 endcase
	 end 
	 
endmodule
