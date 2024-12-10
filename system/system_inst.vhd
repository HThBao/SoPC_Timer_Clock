	component system is
		port (
			clk_clk                         : in  std_logic                    := 'X';             -- clk
			hex0_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			hex1_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			hex2_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			hex3_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			hex4_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			hex5_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			reset_reset_n                   : in  std_logic                    := 'X';             -- reset_n
			sw_external_connection_export   : in  std_logic_vector(2 downto 0) := (others => 'X')  -- export
		);
	end component system;

	u0 : component system
		port map (
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			hex0_external_connection_export => CONNECTED_TO_hex0_external_connection_export, -- hex0_external_connection.export
			hex1_external_connection_export => CONNECTED_TO_hex1_external_connection_export, -- hex1_external_connection.export
			hex2_external_connection_export => CONNECTED_TO_hex2_external_connection_export, -- hex2_external_connection.export
			hex3_external_connection_export => CONNECTED_TO_hex3_external_connection_export, -- hex3_external_connection.export
			hex4_external_connection_export => CONNECTED_TO_hex4_external_connection_export, -- hex4_external_connection.export
			hex5_external_connection_export => CONNECTED_TO_hex5_external_connection_export, -- hex5_external_connection.export
			reset_reset_n                   => CONNECTED_TO_reset_reset_n,                   --                    reset.reset_n
			sw_external_connection_export   => CONNECTED_TO_sw_external_connection_export    --   sw_external_connection.export
		);

