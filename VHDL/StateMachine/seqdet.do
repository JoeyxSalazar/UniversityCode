add wave -position end sim:/fsm/*
force -freeze sim:/fsm/clk 0 0, 1 {50 ps} -r 100
force -freeze sim:/fsm/init 1 0
run
run
force -freeze sim:/fsm/init 0 0
force -freeze sim:/fsm/Din 1 0
run
force -freeze sim:/fsm/Din 0 0
run
force -freeze sim:/fsm/Din 1 0
run
run