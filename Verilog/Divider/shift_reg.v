`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:19:36 10/16/2021 
// Design Name: 
// Module Name:    shift_reg 
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
module shift_reg(input [nBit-1:0] In,
					  input clk,
					  input load,
					  input clr,
					  input sl,
					  input sr,
					  input shiftIn,
					  output reg [nBit-1:0] out);

	parameter nBit = 16;
	
	always@(negedge clk)
	begin
		if(clr)
			out <= 1'b0;
		else
		begin
			if(load)
				out <= In;
			else if (sl)
				out <= {out[nBit-2:0], shiftIn};
			else if (sr)
				out <= {shiftIn, out[nBit-1:1]};
			else
				out <= out;
		end
	end	
endmodule
