`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:13:02 10/16/2021 
// Design Name: 
// Module Name:    div_datapath 
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
module div_datapath(A, B, clk, reset,
						  AB_load_QR_clr, A_sl,
						  R_load_Q_shiftIn, R_sl,
						  Q_sl,
						  shift_count, sub_cout,
						  final_R, final_Q);
	
	parameter nBit = 16;
	
	input [nBit-1:0] A, B;
	
	input clk, reset;
	input AB_load_QR_clr, A_sl;
	input R_load_Q_shiftIn, R_sl;
	input Q_sl;
	
	output reg [nBit-1:0] final_R, final_Q;
	
	output [3:0] shift_count;
	output sub_cout;
	
	wire [nBit-1:0] outA, outB, outR, outQ, sub;
	wire [3:0] counter;
	wire [nBit-1:0] null;
	assign null = 0;
	
	counter ls_count(.increment(A_sl),
						  .clk(clk),
						  .clr(reset),
						  .count(counter));

	shift_reg #(nBit) reg_A(.In(A),
									.clk(clk),
									.load(AB_load_QR_clr), .clr(1'b0), .sl(A_sl), .sr(1'b0), .shiftIn(1'b0),
									.out(outA));
								  
	shift_reg #(nBit) reg_B(.In(B),
									.clk(clk),
									.load(AB_load_QR_clr), .clr(1'b0), .sl(1'b0), .sr(1'b0), .shiftIn(1'b0),
									.out(outB));
								  
	shift_reg #(nBit) reg_R(.In(sub),
									.clk(clk),
									.load(R_load_Q_shiftIn), .clr(AB_load_QR_clr), .sl(R_sl), .sr(1'b0), .shiftIn(outA[nBit-1]),
									.out(outR));
								  
	subtractor #(nBit) subtract(.R(outR),
										 .B(outB),
										 .out(sub),
										 .cout(sub_cout));
								  
	shift_reg #(nBit) reg_Q(.In(null),
									.clk(clk),
									.load(1'b0), .clr(AB_load_QR_clr), .sl(Q_sl), .sr(1'b0), .shiftIn(R_load_Q_shiftIn),
									.out(outQ));
	
	assign shift_count = counter;
	
	always@(posedge clk)
	begin
		if(counter == nBit-1)
		begin
			final_R <= outR;
			final_Q <= outQ;
		end
		else
		begin
			final_R <= 1'b0;
			final_Q <= 1'b0;
		end
	end

endmodule
