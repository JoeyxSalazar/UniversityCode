`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:12:22 09/28/2013 
// Design Name: 
// Module Name:    sev_seg_with_clk_top 
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
module sev_seg_with_clk_top(
    input [7:0] num_1,
    input [7:0] num_2,
    input clk_main,
	 input reset,
    output [7:0] sev_seg_leds,
    output [3:0] led_disable,
    output [3:0] led_enable
    );
	 
	 // Register and Wire Definitions
	 wire clk_slw ;
	 wire [7:0] num_3;
	 wire [7:0] num_4;
	 reg [14:0] clk_div ;
	 
	 div_toplevel #(8) div(.A(num_1),
								  .B(num_2),
								  .reset(reset),
								  .clk(clk_slw),
								  .R_out(num_4),
								  .Q_out(num_3)
								  );
					  
	 
	 // Instantiate the 7-segment display driver module
	 sev_seg_with_clk display_driver(
      .num_1(num_3[7:4]),							// input number one
      .num_2(num_3[3:0]),							// input number two
		.num_3(num_4[7:4]),
		.num_4(num_4[3:0]),
	   .clk(clk_div[14]),					// we need a clock to switch between multiple digits (see below for clock generation)
	   .reset(reset),							// reset signal
	   .sev_seg_leds(sev_seg_leds),		// controls the eight individual LEDs in all sev_seg digits
	   .led_disable(led_disable),			// connected to disable the 6 displays that will not be used 
	   .led_enable(led_enable) 			// connected to drive the 2 displays that will be used
	   );
		
	//---------------- CLOCK GENERATION FOR MULTIPLE 7-SEGMENT DISPLAYS ------------------
	
	// Instantiation of the clock generator from IP Core Generator
	ip_clk_div clk_5M(				// generated core to obtain a slower clk of 5MHz from onboard 100 MHz oscillator.
		.CLK_IN1(clk_main),      	// we assign the external 100 MHz clock to clk_main
		.CLK_OUT1(clk_slw));    	// we assign the generated 5 MHz clock to clk_slw

	
	// Further dividing the clock - 5MHz to approximately 150 Hz
	// We increment clk_div by 1 at every rising edge of clk_slw
	// clk_slw is a 15-bit register, so it can take 2^15 possible values
	// We will use the MSB of clk_slw (clk_slw[14]) as our display switching clock
	// MSB will be low in the first half, and high in the second half of 2^15 counts
	// So, MSB will complete one cycle at every 2^15 cycles of clk_slw
	always @ (posedge clk_slw)	
	begin
		if (reset)
			clk_div <= 15'd0 ;
		else 								
			clk_div <= clk_div + 15'd1 ;	
	end

endmodule
