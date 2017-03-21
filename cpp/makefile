.PHONY: start
start: build run

.PHONY: start_release
start_release: build_release run_release

.PHONY: run
run:
	@./arrows | tee program.log

.PHONY: run_release
run_release:
	@./arrows | tee program.log

.PHONY: build
build:
	@tput reset
	@script -q -c "./compile.sh compile debug" build.log

.PHONY: build_release
build_release:
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

.PHONY: create_prec
create_prec:
	@./compile.sh unlock debug
	@cp -r build/debug/buf prec
	@./compile.sh lock debug

.PHONY: create_prec_release
create_prec_release:
	@./compile.sh unlock release
	@cp -r build/release/buf prec
	@./compile.sh lock release
