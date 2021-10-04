
library ieee;
use ieee.std_logic_signed.all;
use ieee.std_logic_1164.all;
 
entity calcprocessing is
       port(X,Y : in std_logic_vector(7 downto 0);
       opcode: in std_logic_vector(3 downto 0);
       overflow: out std_logic;
       sign: out std_logic;
       Result: out std_logic_vector (7 downto 0));
end calcprocessing;
 
Architecture behav of calcprocessing is
begin
       calcprocessing:process(X,Y,opcode)
	
       begin
              if(opcode = "0000") then
                    Result <= Y;
              elsif(opcode = "0001") then
                    Result <= Y + 1;
              elsif(opcode = "0011") then
                    Result <= X + Y;
              elsif(opcode = "0100") then
                    Result <= not Y;
              elsif(opcode = "0101") then
                    Result <= (Y);
                    sign <= '1';
              elsif(opcode = "1000") then
		    if ( X > Y) then 
	            Result <= ((not(Y+((not X)+1)))+1);
                    sign <= '1';
		    else 
                    Result <= Y - X;
                    end if;
              elsif(opcode = "1001") then
                        if ( Y = "00000000") then 
	            	Result <= Y+1;
			sign <= '1';
			else
			Result <= Y-1;
                    	end if;
              elsif(opcode = "1011") then
                    Result <= not X;
              elsif(opcode = "1100") then
                    Result <= X and Y;
              elsif(opcode = "1101") then
                    Result <= X or Y;
              elsif(opcode = "1110") then 
                    Result <= X xor Y;
              end if;
          
              if(Result = "11111111") then
                    overflow <= '1';

              end if;
             
       end process;
end behav;

