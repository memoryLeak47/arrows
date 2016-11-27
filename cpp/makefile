start: compile run
run:
	@./bam/build/debug/arrows | tee log
valgrind:
	@valgrind --leak-check=full --log-file=valgrind.log ./bam/build/debug/arrows | tee log
getlog:
	@if [ -f log ]; then cat log | less -R; else echo "no log file"; fi
gdb:
	@if [ -f core ]; then gdb ./bam/build/debug/arrows core; else echo no core; fi
line-counter:
	@wc -l `find -name "*.cpp" -o -name "*.hpp" -o -name "*.list"` | sort -g
compile:
	@bam -j `nproc`
perf:
	@sudo perf stat ./bam/build/debug/arrows | tee log
.PHONY: run getlog gdb line-counter compile start
