run:
	@./bam/build/debug/arrows | tee log
lobbyrun:
	@./lobbyrun | tee log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
.PHONY: run lobbyrun getlog
