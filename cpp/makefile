compile:
	@bam
run:
	@./bam/build/debug/arrows
lobbyrun:
	@./lobbyrun
runlog:
	@./bam/build/debug/arrows > log
lobbyrunlog:
	@./lobbyrun > log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
.PHONY: compile run lobbyrun runlog lobbyrunlog getlog
