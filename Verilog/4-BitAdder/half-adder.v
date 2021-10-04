`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:29:55 09/13/2021 
// Design Name: 
// Module Name:    halfadder 
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
module halfadder(A, B, Sum, Cout);
    input A;
    input B;
    output Cout;
    output Sum;//*******************************************Does order matter below?*****************************
	 assign Sum = A^B; //Gets sum of the two bit addition
	 assign Cout = A&B;   //Figures out the carry out
endmodule


