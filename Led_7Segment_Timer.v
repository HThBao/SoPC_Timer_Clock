module Led_7Segment_Timer
(
input 	  	 CLOCK_50,
input  [0:0] KEY,
input  [2:0] SW,
output [7:0] HEX0,
output [7:0] HEX1,
output [7:0] HEX2,
output [7:0] HEX3,
output [7:0] HEX4,
output [7:0] HEX5
);
system nios_system(
.clk_clk											(CLOCK_50),
.reset_reset_n									(KEY[0]),
.hex0_external_connection_export			({8'd0,HEX0}),
.hex1_external_connection_export			({8'd0,HEX1}),
.hex2_external_connection_export			({8'd0,HEX2}),
.hex3_external_connection_export			({8'd0,HEX3}),
.hex4_external_connection_export			({8'd0,HEX4}),
.hex5_external_connection_export			({8'd0,HEX5}),
.sw_external_connection_export			({3'd0,SW})
);
endmodule
