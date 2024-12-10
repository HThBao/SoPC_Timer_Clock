
module system (
	clk_clk,
	hex0_external_connection_export,
	hex1_external_connection_export,
	hex2_external_connection_export,
	hex3_external_connection_export,
	hex4_external_connection_export,
	hex5_external_connection_export,
	reset_reset_n,
	sw_external_connection_export);	

	input		clk_clk;
	output	[7:0]	hex0_external_connection_export;
	output	[7:0]	hex1_external_connection_export;
	output	[7:0]	hex2_external_connection_export;
	output	[7:0]	hex3_external_connection_export;
	output	[7:0]	hex4_external_connection_export;
	output	[7:0]	hex5_external_connection_export;
	input		reset_reset_n;
	input	[2:0]	sw_external_connection_export;
endmodule
