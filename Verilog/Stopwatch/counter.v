`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:12:24 09/28/2021 
// Design Name: 
// Module Name:    counter 
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
module counter(input clk,
					input reset,
					input [3:0] count,
					output [3:0] num
					);

	reg [3:0] counter;
	
	always@(posedge clk, posedge reset)
	begin
		if(reset)
			counter <= 4'b0000;
		else if(counter == count)
			counter <= 4'b0000;
		else
			counter <= counter + 4'b0001;
	end
	
	assign num = counter;

endmodule
