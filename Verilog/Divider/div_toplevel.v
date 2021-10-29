`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:28:24 10/17/2021 
// Design Name: 
// Module Name:    div_toplevel 
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
module div_toplevel(input [nBit-1:0] A,
						  input [nBit-1:0] B,
						  input reset,
						  input clk,
						  output [nBit-1:0] R_out,
						  output [nBit-1:0] Q_out);
						  
	parameter nBit = 16;
	
	wire [nBit-1:0] transfer_R, transfer_Q;
	
	wire AB_load_QR_clr, A_sl;
	wire R_load_Q_shiftIn, R_sl;
	wire Q_sl;
	
	wire transfer_sub_cout;
	wire [3:0] transfer_count;

	div_controller #(nBit) control(.sub_cout(transfer_sub_cout),
											 .counter(transfer_count),
											 .reset(reset),
											 .clk(clk),
											 .AB_load_QR_clr(AB_load_QR_clr), .A_sl(A_sl),
											 .R_load_Q_shiftIn(R_load_Q_shiftIn), .R_sl(R_sl),
											 .Q_sl(Q_sl));
											 
	div_datapath #(nBit) datapath(.A(A),
											.B(B),
											.clk(clk),
											.reset(reset),
											.AB_load_QR_clr(AB_load_QR_clr), .A_sl(A_sl),
											.R_load_Q_shiftIn(R_load_Q_shiftIn), .R_sl(R_sl),
											.Q_sl(Q_sl),
											.shift_count(transfer_count),
											.sub_cout(transfer_sub_cout),
											.final_R(transfer_R),
											.final_Q(transfer_Q));
	
	assign R_out = transfer_R;
	assign Q_out = transfer_Q;
	
endmodule
