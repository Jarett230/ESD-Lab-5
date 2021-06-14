library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


ENTITY lab_5_top is
  port (
    CLOCK_50 	: in std_logic;
	 KEY			: in std_logic_vector(3 downto 0);
	 SW			: in std_logic_vector(7 downto 0);
    HEX0  		: out std_logic_vector(6 downto 0);
    HEX1  		: out std_logic_vector(6 downto 0);
    HEX2  		: out std_logic_vector(6 downto 0);
    HEX3  		: out std_logic_vector(6 downto 0);
    HEX4  		: out std_logic_vector(6 downto 0);
    HEX5  		: out std_logic_vector(6 downto 0);
    wave  		: out std_logic
	 );
end entity lab_5_top;

architecture lab_5_top_arch of lab_5_top is
  
component nios_system
    port (
    clk_clk : in std_logic;
    hex0_export : out std_logic_vector(6 downto 0);
    hex1_export : out std_logic_vector(6 downto 0);
    hex2_export : out std_logic_vector(6 downto 0);
    hex3_export : out std_logic_vector(6 downto 0);
    hex4_export : out std_logic_vector(6 downto 0);
    hex5_export : out std_logic_vector(6 downto 0);
    pushbuttons_export : in std_logic_vector(3 downto 0);
    reset_reset_n : in std_logic;
    switches_export : in std_logic_vector(7 downto 0);
    wave_outwave : out std_logic
  );
end component;

   

begin

  nios_system_inst : component nios_system
    port map (
		clk_clk            => CLOCK_50,
		hex0_export			 => HEX0,
		hex1_export			 => HEX1,
		hex2_export			 => HEX2,
		hex3_export			 => HEX3,
		hex4_export			 => HEX4,
		hex5_export			 => HEX5,
		pushbuttons_export => KEY,
		reset_reset_n		 => '1',
		switches_export    => SW,
		wave_outwave    => wave
    );


end architecture lab_5_top_arch;