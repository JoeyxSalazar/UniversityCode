add wave -position end sim:/sequencedetector/*
force -freeze sim:/sequencedetector/clk 0 0, 1 {50 ps} -r 100
force -freeze sim:/sequencedetector/init 1 0
run
run
force -freeze sim:/sequencedetector/init 0 0
force -freeze sim:/sequencedetector/Din 1 0
run
force -freeze sim:/sequencedetector/Din 0 0
run
force -freeze sim:/sequencedetector/Din 1 0
run
run
