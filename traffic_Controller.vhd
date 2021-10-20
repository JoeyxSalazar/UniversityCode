library ieee;
use ieee.std_logic_signed.all;
use ieee.std_logic_1164.all;
 
entity traffic_Controller is
       port(
		after_division_clk : in STD_LOGIC;
		clr : in STD_LOGIC; 
		lights: out STD_LOGIC_VECTOR(3 downto 0)
		);
end traffic_Controller;
 
Architecture behav of traffic_Controller is

type state_type is (s0,s1,s2,s3,s4, s5);
signal present_state: state_type;
signal count : integer range 0 to 30;
constant sec5 : integer:=30; --30 counts -> 180
constant sec : integer:=6; --6 counts -> 36

begin
	toplev: process(after_division_clk, clr)
	Begin
		If clr = '0' then
			present_state<=s0;
			count <= 0;
		elsif after_division_clk'event and after_division_clk = '1' then
			Case present_state is
				When s0=>
					--N/S is green
					--E/W is red
					if count < sec5 then
						present_state <= s0;
						count <= count + 1;
						
					else
						present_state <= s1;
						count <= 0;
					end if;

				When s1=>
					--N/S is yellow
					--E/W red
					if count < sec then
						present_state <= s1;
						count <= count + 1;
						
					else
						present_state <= s2;
						count <= 0;
					end if;

				When s2=>
					-- N/S is red
					--E/W is red
					if count < sec then
						present_state <= s2;
						count <= count + 1;
						
					else
						present_state <= s3;
						count <= 0;
					end if;
				When s3=>
					--N/S is red
					--E/W is green
					if count < sec5 then
						present_state <= s3;
						count <= count + 1;
						
					else
						present_state <= s4;
						count <= 0;
					end if;
				When s4=>
					--N/S is red
					--E/W is yellow
					if count < sec then
						present_state <= s4;
						count <= count + 1;
						
					else
						present_state <= s5;
						count <= 0;
					end if;
				When s5=>
					--N/S is red
					--E/W is red
					if count < sec then
						present_state <= s5;
						count <= count + 1;
		
					else
						present_state <= s0;
						count <= 0;
					end if;
				When others=>
					Null;
				end case;
		end if;
	End process;


	light: process(present_state)
	begin
		Case present_state is
			When s0 =>
				--N/S is green
				--E/W is red
				lights <= "1001";
			When s1 =>
				--N/S is yellow
				--E/W red
				lights <= "1101";
			When s2 =>
				-- N/S is red
				--E/W is red
				lights <= "0101";
			When s3 =>
				--N/S is red
				--E/W is green
				lights <= "0110";
			When s4 =>
				--N/S is red
				--E/W is yellow
				lights <= "0111";
			When s5 =>
				--N/S is red
				--E/W is red
				lights <= "0101";
			When others =>
				lights <= "1111";
		end case;
	end process;
			

	
				



end behav;
