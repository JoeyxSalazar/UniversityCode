Library IEEE;
Use ieee.std_logic_1164.all;

Entity reg8bit is
       Port(Inp : in std_logic_vector(7 downto 0);
              Load, Clk : in std_logic;
              Outp : out std_logic_vector(7 downto 0));
       end reg8bit;
              
Architecture behav of reg8bit is
       Signal storage: std_logic_vector(7 downto 0);
              begin
                    process(Inp, Load, Clk)
                    begin
                           if (Clk'event and Clk = '1' and Load = '1') then
                                  storage <= Inp;
                           elsif (Clk'event and Clk = '0') then
                                  Outp <= storage;
                           end if;
                    end process;
              end;



