library ieee;
use ieee.std_logic_signed.all;
use ieee.std_logic_1164.all;
 
entity traffic_lights_top is
	port(
		original_clk : in STD_LOGIC; ----50M hz
		btn : in STD_LOGIC;		--clear button
		led: out STD_LOGIC_VECTOR(3 downto 0) --Green and Red LEDs
		);
end traffic_lights_top;

Architecture behav of traffic_lights_top is


component clkdiv
       port(
		original_clk : in STD_LOGIC;
		clr: in STD_LOGIC;
		after_division_clk: out STD_LOGIC
		);
end component;

component traffic_Controller 
       port(
		after_division_clk : in STD_LOGIC;
		clr : in STD_LOGIC; 
		lights: out STD_LOGIC_VECTOR(3 downto 0)
		);
end component;



signal newclk: STD_LOGIC;
--signal cntr: std_logic_vector(7 downto 0);
begin

	div: clkdiv port map(original_clk, btn, newclk);
	tcl: traffic_Controller port map(newclk, btn, led);
	--cnt: up_counter(newclk, target, out);


end behav;