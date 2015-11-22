module iic_iogen(inout scl, sda, input scl_padoen_oe, sda_padoen_oe, sdao, sclo, output scl_pad_i, sda_pad_i);
	assign scl = scl_padoen_oe ? 1'bz : sclo;
	assign sda = sda_padoen_oe ? 1'bz : sdao;
	assign scl_pad_i = scl;
	assign sda_pad_i = sda;
endmodule