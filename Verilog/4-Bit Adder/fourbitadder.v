`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:05:13 09/13/2021 
// Design Name: 
// Module Name:    fourbitadder 
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
module fourbitadder(
    A,
    B,
    E,
    NewSum,
    Cout
    );
	 
	 input[3:0] A;
	 input[3:0] B;
	 
	 input E;
	 output reg[3:0] NewSum;
	 wire [3:0] Sum;
	 wire[3:0] hold;
	 output Cout;
	 
	 wire c0, c1, c2, c3;
	 reg[3:0] dummy;
	 reg[3:0] Bnew;
	 
	 
	 
always @(*) 
begin
	 if(E) 		 //If Subtracting, two's complement
	 begin
		assign Bnew = ~B;
		assign dummy = 4'b1111;
	 end
	 else
	 begin
		assign Bnew = B;
		assign dummy = 4'b0000;
		end
end

wire v;	
assign Cout = (c3^E); //Carry = c3 for addition, Carry = not(c3) for subtraction.
assign v = (c3^c2);	// If the two most significant carry output bits differ, then we have an overflow.

	 fulladder f1(.A(A[0]),.B(Bnew[0]),.Cin(E),.Cout(c0),.Sum(Sum[0])); // LSB 
	 fulladder f2(.A(A[1]),.B(Bnew[1]),.Cin(c0),.Cout(c1),.Sum(Sum[1]));
	 fulladder f3(.A(A[2]),.B(Bnew[2]),.Cin(c1),.Cout(c2),.Sum(Sum[2]));
	 fulladder f4(.A(A[3]),.B(Bnew[3]),.Cin(c2),.Cout(c3),.Sum(Sum[3])); //MSB

//If subtraction, the answer is still in two's complement, so we must convert back

	
	assign hold = (Sum^dummy) + 1'b1; //twos comp
	always @(*)
		case(E)
			1'b1: assign NewSum = hold;
		default: assign NewSum = Sum;
		endcase
			
endmodule
