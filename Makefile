
clean:
	-rm -rf tests-comparative-research
	-rm -rf tests-comparative-control
	-rm -rf hbox-research
	-rm -rf hbox-control
	-rm -rf arbitraire
	-rm -rf logs
	-rm -rf bc*
	-make -C libc-test-fork clean
	-make -C tests-emperical clean
	-rm retval
	
