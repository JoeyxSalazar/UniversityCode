library ieee;
use ieee.std_logic_signed.all;
use ieee.std_logic_1164.all;

entity Calc8bit is 
port   (Din1 : in std_logic_vector (7 downto 0);
	Din2 : in std_logic_vector (7 downto 0);
       clk: in std_logic;
       load: in std_logic_vector(1 downto 0);
       opcode: in std_logic_vector(3 downto 0);
       result: out std_logic_vector (7 downto 0);
	sign: out std_logic;
       overflow: out std_logic);
end entity;

Architecture Arch8 of Calc8bit is 

       component reg8bit
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
       
	signal Xout : std_logic_vector (7 downto 0);
	signal Yout : std_logic_vector (7 downto 0);

	begin
		R1 : reg8bit port map (Din1, load(0),clk, Xout);
		R2 : reg8bit port map (Din2, load(1), clk, Yout);
		Calc : calcprocessing port map(Xout, Yout, opcode, overflow, sign, result);

end Arch8;
