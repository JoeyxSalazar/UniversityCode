Library IEEE;
Use IEEE.STD_LOGIC_1164.all;

Entity fsm is
	Port( clk: in STD_LOGIC;
		init: in STD_LOGIC;
		Din: in STD_LOGIC;
		Dout: out STD_LOGIC);
end fsm;

Architecture fsm of fsm is
type state_type is (s0,s1,s2,s3,s4);
signal next_state, present_state: state_type;
begin
	Sreg: process(clk, init)
	Begin
		If init = '1' then
			present_state<=s0;
		Elsif clk'event and clk = '1' then
			present_state <= next_state;
		end if;
	End process;

	C1: process(present_state,din)
	Begin
		Case present_state is
			When s0 =>
				If din = '1' then
					next_state <= s1;
				Else
					next_state <= s0;
				end if;
			When s1 =>
				If din = '1' then
					next_state <= s1;
				else
					next_state <= s2;
				end if;
			When s2 =>
				If din = '0' then
					next_state <= s0;
				else
					next_state <= s3;
				end if;
			When s3 => 
				If Din = '1' then
					next_state <= s4;
				else
					next_state <=s2;
				end if;
			When s4 =>
				next_state <= s0;
			When others =>
				Null;
			end case;
	End process;

	C2: process(present_state)
	Begin
		If present_state = s4 then
			Dout <= '1';
		Else
			Dout<='0';
		end if;
	end process;
end fsm;
