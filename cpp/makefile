.PHONY: start
start: compile run

.PHONY: start_release
start_release: compile_release run_release

.PHONY: run
run:
	@./arrows | tee log

.PHONY: run_release
run_release:
	@./arrows | tee log

.PHONY: compile
compile:
	@tput reset
	@./compile.sh debug

.PHONY: compile_release
compile_release:
	@tput reset
	@./compile.sh release

.PHONY: line-counter
line-counter:
	@wc -l `find -name "*.cpp" -o -name "*.hpp" -o -name "*.list"` | sort -g

.PHONY: valgrind
valgrind:
	@valgrind --leak-check=full --log-file=valgrind.log ./arrows | tee log

.PHONY: getlog
getlog:
	@if [ -f log ]; then cat log | less -R; else echo "no log file"; fi

.PHONY: gdb
gdb:
	@if [ -f core ]; then gdb ./arrows core; else echo running with no core; echo; gdb ./arrows; fi

.PHONY: perf
perf:
	@sudo perf stat ./arrows | tee log
