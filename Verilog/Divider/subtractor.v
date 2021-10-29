`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:56:18 10/16/2021 
// Design Name: 
// Module Name:    subtractor 
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
module subtractor(input [nBit-1:0] R,
						input [nBit-1:0] B,
						output [nBit-1:0] out,
						output cout);
						
	parameter nBit = 16;
	
	wire [nBit-1:0] B_comp;
	wire [nBit-1:0] c;
	
	assign B_comp = ~B + 1'b1;
	
	genvar i;
	
	generate
		for(i=0; i <= nBit-1; i=i+1)
		begin: generate_subtractor
			if(i==0)
				half_adder HA(R[0], B_comp[0], c[0], out[0]);
			else
				full_adder FA(R[i], B_comp[i], c[i-1], c[i], out[i]);
		end
		
		assign cout = c[nBit-1];
		
	endgenerate
endmodule
