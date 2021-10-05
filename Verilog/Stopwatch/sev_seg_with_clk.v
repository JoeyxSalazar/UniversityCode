`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:01:50 09/28/2013 
// Design Name: 
// Module Name:    sev_seg_with_clk 
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
module sev_seg_with_clk(
    input [3:0] num_1,					// input number one
    input [3:0] num_2,					// input number two
	 input [3:0] num_3,
	 input [3:0] num_4,
	 input clk,								// we need a clk to switch between multiple digits
	 input reset,							// reset signal 
	 output [7:1] sev_seg_leds,		// controls the 8 individual LEDs in all sev_seg digits
	 output [3:0]led_disable,			// connected to disable the 6 displays that will not be used 
	 output reg [3:0]led_enable		// connected to drive the 2 displays that will be used
    );
	  
	 reg [3:0] out_bus;
	 reg [2:0] sel;
	 
	 assign led_disable = 4'b1111;		// disable other 5 digits
	 
	 // We will toggle the register "sel" at every rising clock edge
	 // This register will be used to switch the display between two displays
	 // led_enable[1] controls the leftmost display, led_enable[0] controls the one next to it, led_enable[2]
	 // The displays are activated when the corresponding enable bit goes to LOW
	 
	 always @ (posedge clk or posedge reset)		// Whenever the clock or the reset signal goes high, this block will be activated
	 begin
		if (reset)								// If reset is high
		begin
			sel <= 3'b000;		 				// sel signal is brought to 0
			led_enable <= 4'b1111;				// both displays are turned off
		end
		else										// If reset button is not pressed
		begin
			sel[2] <= sel[1] & sel[0];
			sel[1] <= sel[1]^sel[0];
			sel[0] <= ~sel[0];

			case(sel)
				3'b001: 
				begin
					led_enable <= 4'b0111;
					out_bus <= num_1;
				end
				3'b010:
				begin
					led_enable <= 4'b1011;
					out_bus <= num_2;
				end
				3'b011:
				begin
					led_enable <= 4'b1101;
					out_bus <= num_3;
				end
				3'b100:
				begin
					led_enable <= 4'b1110;
					out_bus <= num_4;
				end
				default : led_enable <= 4'bxxxx;
			endcase
		end
	 end	

	 
	 // If sel = 0, num_2 is sent to the decoder input; otherwise it is num_1 
	 sev_seg_decoder decoder1(.num_in(out_bus), 
									  .sev_seg_leds(sev_seg_leds));
	 // So, num_2 controls the leftmost display, and num_1 controls the one next to it
	 // For convenience, we assigned num_2 to the four leftmost switches and num_1 to the four rightmost switches
	 
endmodule
