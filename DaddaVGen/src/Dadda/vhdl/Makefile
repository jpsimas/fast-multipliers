default:
	ghdl -a half_adder.vhd
	ghdl -a full_adder.vhd
	ghdl -a Mult_Dadda32.vhd
	ghdl -a mbe_ppg.vhd
	ghdl -a tb.vhd
	ghdl -a tb_ppg.vhd
	ghdl -e tb
	./tb --vcd=out.vcd
	ghdl -e tb_ppg
	./tb_ppg --vcd=out_ppg.vcd
clean:
	rm -rf *.o
	rm -rf work-obj93.cf
