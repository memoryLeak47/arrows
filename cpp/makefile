compile:
	@bam
no_compile_run:
	@./bam/build/debug/arrows | tee log
no_compile_lobbyrun:
	@./lobbyrun | tee log
run: compile
	@./bam/build/debug/arrows | tee log
lobbyrun: compile
	@./lobbyrun | tee log
getlog:
	@if [ -f log ]; then cat log; else echo "no log file"; fi
.PHONY: compile run lobbyrun getlog no_compile_run no_compile_lobbyrun
