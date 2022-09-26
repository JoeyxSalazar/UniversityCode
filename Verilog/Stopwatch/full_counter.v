`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:22:27 09/29/2021 
// Design Name: 
// Module Name:    full_counter 
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
module full_counter(input clk_base,
						  input reset,
						  input stop,
						  output [3:0] num4,
						  output [3:0] num3,
						  output [3:0] num2,
						  output [3:0] num1
    );
	 
	 wire [3:0] clk_out;
	 
	 wire [17:0] tenth_sec_limit = 18'd250000;
	 wire [3:0] sec_limit = 3'b100;
	 wire [2:0] minute_limit = 2'b10;

	 wire [3:0] ten_stop = 4'b1001;
	 wire [3:0] six_stop = 4'b0101;
	 
	 place #(18) block4(.clk_base(clk_base), .reset(reset), .stop(stop), .limit(tenth_sec_limit), .placestop(ten_stop), .clk_next(clk_out[0]), .num(num4));
	 place #(4) block3(.clk_base(clk_out[0]), .reset(reset), .stop(stop), .limit(sec_limit), .placestop(ten_stop), .clk_next(clk_out[1]), .num(num3));
	 place #(4) block2(.clk_base(clk_out[1]), .reset(reset), .stop(stop), .limit(sec_limit), .placestop(six_stop), .clk_next(clk_out[2]), .num(num2));
	 place #(3) block1(.clk_base(clk_out[2]), .reset(reset), .stop(stop), .limit(minute_limit), .placestop(ten_stop), .clk_next(clk_out[3]), .num(num1));

endmodule
