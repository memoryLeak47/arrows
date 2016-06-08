compile:
	@bam
run:
	@./bam/build/debug/arrows | tee log
lobbyrun:
	@./lobbyrun | tee log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
.PHONY: compile run lobbyrun runlog lobbyrunlog getlog
