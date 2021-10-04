`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:45:16 09/13/2021 
// Design Name: 
// Module Name:    fulladder 
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



module fulladder(A, B, Cin, Sum, Cout);
	input A, B, Cin;
	output Sum, Cout;
	wire G, H, J;
	halfadder H1(.A(A),.B(B),.Sum(G),.Cout(H));
	halfadder H2(.A(Cin),.B(G),.Sum(Sum),.Cout(J));
	or(Cout, H, J);
endmodule

