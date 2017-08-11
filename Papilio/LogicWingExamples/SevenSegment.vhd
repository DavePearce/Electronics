library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity SevenSegment is
port(
 CLK: in STD_LOGIC;  
 Seg7_AN: out STD_LOGIC_VECTOR(0 to 1);
 Seg7: out STD_LOGIC_VECTOR(0 to 6));
end SevenSegment;

architecture Behavioral of SevenSegment is
signal ticks: unsigned(31 downto 0) := to_unsigned(0,32);
signal tick: std_logic := '0';
signal counter: unsigned(2 downto 0) := "000";
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
	-- Increment counter upon tick
   process(tick)
   begin      
		if rising_edge(tick) then
			counter <= counter + 1;
		end if;
	end process;
   Seg7_AN <= "00";
	process
	begin
		case to_integer(counter) is
			when 0 => Seg7 <= "0000001";
			when 1 => Seg7 <= "1001111";
			when 2 => Seg7 <= "0010010";
			when 3 => Seg7 <= "0000110";
			when 4 => Seg7 <= "1001100";
			when 5 => Seg7 <= "0100100";
			when 6 => Seg7 <= "0100000";
			when 7 => Seg7 <= "0001111";
			when 8 => Seg7 <= "0000000";
			when others => Seg7 <= "1111111";
		end case;
	end process;
end Behavioral;

