.PHONY: start
start: compile run

.PHONY: start_release
start_release: compile_release run_release

.PHONY: run
run:
	@./arrows | tee program.log

.PHONY: run_release
run_release:
	@./arrows | tee program.log

.PHONY: compile
compile:
	@tput reset
	@script -q -c "./compile.sh compile debug" build.log

.PHONY: compile_release
compile_release:
	@tput reset
	@script -q -c "./compile.sh compile release" build.log

.PHONY: line-counter
line-counter:
	@wc -l `find -name "*.cpp" -o -name "*.hpp" -o -name "*.list"` | sort -g

.PHONY: valgrind
valgrind:
	@valgrind --leak-check=full --log-file=valgrind.log ./arrows | tee log

.PHONY: program_log
program_log:
	@if [ -f program.log ]; then less -R program.log ; else echo "no log file"; fi

.PHONY: build_log
build_log:
	@if [ -f build.log ]; then less -R build.log; else echo "no build.log"; fi

.PHONY: gdb
gdb:
	@./compile.sh unlock debug
	@./compile.sh unlock release
	@if [ -f core ]; then gdb ./arrows core; else echo running with no core; echo; gdb ./arrows; fi
	@./compile.sh lock debug
	@./compile.sh lock release

.PHONY: perf
perf:
	@sudo perf stat ./arrows | tee log
