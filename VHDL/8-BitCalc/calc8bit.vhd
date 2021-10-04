library ieee;
use ieee.std_logic_signed.all;
use ieee.std_logic_1164.all;

entity calculator8bit is 
port   (Din1 : in std_logic_vector (7 downto 0);
	Din2 : in std_logic_vector (7 downto 0);
       clk: in std_logic;
       load: in std_logic_vector(1 downto 0);
       opcode: in std_logic_vector(3 downto 0);
       result: out std_logic_vector (7 downto 0);
	sign: out std_logic;
       overflow: out std_logic);
end entity;

Architecture Arch8 of calculator8bit is 

       component register8
       port (Inp: in std_logic_vector(7 downto 0);
              Clk, Load: in std_logic;
              Outp: out std_logic_vector(7 downto 0));
       end component;

       component calcprocessing
       port (X,Y: in std_logic_vector (7 downto 0);
              opcode: in std_logic_vector(3 downto 0);
              overflow: out std_logic;
		sign: out std_logic;
              Result: out std_logic_vector (7 downto 0));
       end component;
		 
		 
			component Display is
			port(
			Input: in std_logic_vector(3 downto 0); --input from calc
			segmentSeven : out std_logic_vector(6 downto 0)); --7 bit output end Display_Ckt;
			end component;
			
			component DisplaySign is
			port( Input: in bit; --input from sign
			segmentSeven : out std_logic_vector(6 downto 0)); --7 bit output end Display_Ckt;
			end component;
       
	signal Xout : std_logic_vector (7 downto 0);
	signal Yout : std_logic_vector (7 downto 0);
	signal DisL : std_logic_vector (6 downto 0);
	signal DisR : std_logic_vector (6 downto 0);
	signal DiSign: std_logic_vector (6 downto 0);

	begin
		R1 : register8 port map (Din1, load(0),clk, Xout);
		R2 : register8 port map (Din2, load(1), clk, Yout);
		Calc : calcprocessing port map(Xout, Yout, opcode, overflow, sign, result);
		ledL: Display port map (Result(7 downto 4), DisL);
		ledR: Display port map (Result(3 downto 0), DisR);
		sign: DisplaySign port map (sign, DiSign);
		

end Arch8;
