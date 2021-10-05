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
    input [3:0] num_in,					// number to display in binary form
    output reg [7:1] sev_seg_leds		// controls the eight individual LEDs in the 7-segment display 
    );

	 // lights up the proper LEDs for each digit (remember that the LEDs are active low)
	always @(*)	begin
		case (num_in)			
			4'h0 		:	 sev_seg_leds[7:1] = 7'b1000000;
			4'h1 		:	 sev_seg_leds[7:1] = 7'b1111001;
			4'h2	 	:	 sev_seg_leds[7:1] = 7'b0100100;
			4'h3 		:	 sev_seg_leds[7:1] = 7'b0110000;
			4'h4 		:	 sev_seg_leds[7:1] = 7'b0011001;
			4'h5 		:	 sev_seg_leds[7:1] = 7'b0010010;
			4'h6 		:	 sev_seg_leds[7:1] = 7'b0000010;
			4'h7 		:	 sev_seg_leds[7:1] = 7'b1111000;
			4'h8 		:	 sev_seg_leds[7:1] = 7'b0000000;
			4'h9 		:	 sev_seg_leds[7:1] = 7'b0010000;
			default 	: 	 sev_seg_leds[7:1] = 7'b0111111;
		endcase
	end
endmodule
