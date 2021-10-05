`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:05:42 09/29/2021 
// Design Name: 
// Module Name:    place 
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
module place(input clk_base,
				 input reset,
				 input stop,
				 input [nBit-1:0] limit,
				 input [3:0] placestop,
				 output clk_next,
				 output [3:0] num
				 );
				 
	parameter nBit = 18;
	wire clk_count;

	get_clk #(nBit) div(.clk_base(clk_base), .reset(reset), .stop(stop), .limit(limit), .clk_out(clk_count)); 
	counter increment (.clk(clk_count), .reset(reset), .count(placestop), .num(num));
	
	assign clk_next = clk_count;

endmodule
