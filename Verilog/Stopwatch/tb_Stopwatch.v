`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:38:59 09/29/2021
// Design Name:   full_counter
// Module Name:   C:/Users/Karna Nagalla/Desktop/ECE/ECE414/Lab3/Stopwatch/tb_Stopwatch.v
// Project Name:  Stopwatch
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: full_counter
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Stopwatch;

	// Inputs
	reg clk_base;
	reg reset;
	reg stop;

	// Outputs
	wire [3:0] num4;
	wire [3:0] num3;
	wire [3:0] num2;
	wire [3:0] num1;

	// Instantiate the Unit Under Test (UUT)
	full_counter uut (
		.clk_base(clk_base), 
		.reset(reset), 
		.stop(stop), 
		.num4(num4), 
		.num3(num3), 
		.num2(num2), 
		.num1(num1)
	);
	
	integer i;
	integer k;
	integer j;

	initial begin
		// Initialize Inputs
		clk_base = 0;
		reset = 0;
		stop = 0;

		// Wait 100 ns for global reset to finish
		#10;
        
		// Add stimulus here
		clk_base = 0;
		reset = 1;
		stop = 0;
		#10;
		
		clk_base = 0;
		reset = 0;
		stop = 0;
		#10;
		
		for(i = 0; i < 31'd500000000; i = i + 1)
			#1 clk_base = ~clk_base;
			
		clk_base = 0;
		reset = 0;
		stop = 1;
		#100;
		
		
		for(k = 0; k < 31'd25; k = k + 1)
			#1 clk_base = ~clk_base;
			
		clk_base = 0;
		reset = 1;
		stop = 0;
		#100;
		
		for(j = 0; j < 31'd25; j = j + 1)
			#1 clk_base = ~clk_base;

	end
      
endmodule

