
clean:
	rm -rf tests-comparative-research
	rm -rf tests-comparative-control
	rm -rf logs
	make -C libc-test-fork clean
	rm retval
	
