run:
	@./bam/build/debug/arrows | tee log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
gdb:
	@gdb ./bam/build/debug/arrows core
.PHONY: run getlog gdb
