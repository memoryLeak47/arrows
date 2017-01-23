start: compile run
start_release: compile_release run_release
run:
	@./bam/build/debug/arrows | tee log
run_release:
	@./bam/build/release/arrows | tee log
compile:
	@tput reset
	@bam -j `nproc`
compile_release:
	@bam -j `nproc` conf=release
line-counter:
	@wc -l `find -name "*.cpp" -o -name "*.hpp" -o -name "*.list"` | sort -g
valgrind:
	@valgrind --leak-check=full --log-file=valgrind.log ./bam/build/debug/arrows | tee log
getlog:
	@if [ -f log ]; then cat log | less -R; else echo "no log file"; fi
gdb:
	@if [ -f core ]; then gdb ./bam/build/debug/arrows core; else echo no core; fi
perf:
	@sudo perf stat ./bam/build/debug/arrows | tee log
.PHONY: start start_release run run_release compile compile_release line-counter valgrind getlog gdb perf
