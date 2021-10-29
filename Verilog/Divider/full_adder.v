`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:53:04 10/16/2021 
// Design Name: 
// Module Name:    full_adder 
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
module full_adder(A, B, Cin, Cout, Sum);

	input A, B, Cin;
	output Cout, Sum;
	
	wire S;
	wire [1:0] carry;

	half_adder HA_1(.A(A), .B(B), .Cout(carry[0]), .Sum(S));
	half_adder HA_2(.A(S), .B(Cin), .Cout(carry[1]), .Sum(Sum));
	
	assign Cout = carry[0]|carry[1];
	
endmodule
