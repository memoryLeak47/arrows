start: compile run
run:
	@./bam/build/debug/arrows | tee log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
gdb:
	@if [ -f core ]; then gdb ./bam/build/debug/arrows core; else echo no core; fi
line-counter:
	@line-counter *pp
compile:
	@bam -j `nproc`
.PHONY: run getlog gdb line-counter compile start
