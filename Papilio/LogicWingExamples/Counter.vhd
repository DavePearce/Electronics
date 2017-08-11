library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Counter is
port(
 CLK: in STD_LOGIC; 
 SWITCH: in STD_LOGIC_VECTOR(7 downto 0);
 LED: out STD_LOGIC_VECTOR(0 to 7));
end Counter;

architecture Behavioral of Counter is
signal ticks: unsigned(31 downto 0) := to_unsigned(0,32);
signal tick: std_logic := '0';
signal counter: unsigned(7 downto 0) := "00000000";
begin
   -- Down sample the clk
	process(CLK)
	begin	   
		if rising_edge(CLK) then
			if ticks = to_unsigned(10000000,ticks'length)
			then
				ticks <= to_unsigned(0,ticks'length);
				tick <= '1';
			else
				tick <= '0';
				ticks <= ticks + 1;			
			end if;
		end if;
	end process;
   -- Increment counter upon switch activation
	process(tick)
	begin	   
		if rising_edge(tick) then			
			counter <= counter + 1;
		end if;
	end process;
	-- Output state of counter to LED
	LED <= std_logic_vector(counter);
	--
end Behavioral;

