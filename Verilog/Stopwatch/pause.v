`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:06:16 09/28/2021 
// Design Name: 
// Module Name:    pause 
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
module pause(input clk_base,
				 input reset,
				 input stop, 
				 input [nBit-1:0] limit,
				 output reg clk_out
				 );
	
	parameter nBit = 18;
	
	reg [nBit-1:0] clk_counter;
	
	always@(posedge clk_base, posedge reset)
	begin
		if(reset)
		begin
			clk_counter <= 1'b0;
			clk_out <= 1'b1;
		end
		else
		begin
			if(stop)
				begin
					if(clk_counter == limit)
					begin
						clk_counter <= 1'b0;
						clk_out <= ~clk_out;
					end
					else
					begin
						clk_counter <= clk_counter + 1'b1;
						clk_out <= clk_out;
					end
				end
			else
				clk_counter <= clk_counter;
		end
	end

endmodule

