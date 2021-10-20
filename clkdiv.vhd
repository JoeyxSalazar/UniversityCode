Library IEEE;
Use IEEE.STD_LOGIC_1164.all;
Use IEEE.STD_LOGIC_unsigned.all;

entity clkdiv is 
	port(
		original_clk : in STD_LOGIC;
		clr: in STD_LOGIC;
		after_division_clk : out STD_LOGIC
		);
end clkdiv;

architecture behav of clkdiv is 
	signal divider : std_logic_vector( 22 downto 0 );
	
begin
	process(original_clk, clr)
	begin
		if clr = '0' then 
			divider <= "00000000000000000000000";
		elsif rising_edge(original_clk) then 
			divider <= divider + '1';
		end if;
	end process;
	after_division_clk <= divider(22); --input frequency / 8,333,333.33 produces 6Hz clock

end behav;

