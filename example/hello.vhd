library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity AndGate is
    Port (
        A : in  STD_LOGIC;
        B : in  STD_LOGIC;

        Z : out STD_LOGIC
    );

end AndGate;

architecture Behavioral of AndGate is
begin
    Z <= A and B;
end Behavioral;
