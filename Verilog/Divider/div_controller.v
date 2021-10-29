`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:13:24 10/17/2021 
// Design Name: 
// Module Name:    div_controller 
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
module div_controller(sub_cout, counter, reset, clk,
							 AB_load_QR_clr, A_sl,
							 R_load_Q_shiftIn, R_sl,
							 Q_sl);
							 
	parameter nBit = 16;
	parameter s0=3'b000, s1=3'b001, s2=3'b010, s3=3'b011, s4=3'b100, s5=3'b101;
							 
	input sub_cout, reset, clk;
	input [3:0] counter;
	
	output reg AB_load_QR_clr, A_sl;
	output reg R_load_Q_shiftIn, R_sl;
	output reg Q_sl;
	 
	reg [2:0] state;

	always@(posedge clk or posedge reset)
	begin
		if(reset)
			state <= s0;
		else
		begin
			case(state)
				s0: state <= s1;
				s1:
				begin
					if(sub_cout)
						state <= s3;
					else
						state <= s2;
				end
	
				s2:
				begin
					if(counter == nBit-1)
						state <= s5;
					else
						state <= s4;
				end
				
				s3:
				begin
					if(counter == nBit-1)
						state <= s5;
					else
						state <= s4;
				end
				
				s4: state <= s1;
				s5: state <= s5;
				default: state <= s0;
			endcase
		end
	end
	
	always@(state)
	begin
		case(state)
			s0: 
			begin
				AB_load_QR_clr <= 1'b1;
				A_sl <= 1'b0;
				R_load_Q_shiftIn <= 1'b0;
				R_sl <= 1'b0;
				Q_sl <= 1'b0;
			end
			
			s1: 
			begin
				AB_load_QR_clr <= 1'b0;
				A_sl <= 1'b0;
				R_sl <= 1'b1;
			end
			
			s2: 
			begin
				R_load_Q_shiftIn <= 1'b0;
				R_sl <= 1'b0;
				Q_sl <= 1'b1;
			end
			
			s3:
			begin
				R_load_Q_shiftIn <= 1'b1;
				R_sl <= 1'b0;
				Q_sl <= 1'b1;
			end
			
			s4: 
			begin
				A_sl <= 1'b1;
				R_load_Q_shiftIn <= 1'b0;
				R_sl <= 1'b0;
				Q_sl <= 1'b0;
			end
			
			s5: 
			begin
				R_load_Q_shiftIn <= 1'b0;
				Q_sl <= 1'b0;
			end
		endcase
	end
endmodule
