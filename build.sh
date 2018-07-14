#!/bin/sh

BASIC_TYPE="	stat-driver .
		lstat-driver .
		printf-zeropad
		printf-fieldpad
		printf-leftadj
		printf-pad-string
		printf-field
		snprintf-driver
		atoll-small
		strtoull-driver
		strtoll-driver
		malloc-huge
		ctype
		malloc-unique-pointer
		getline-driver
		atoi
		atol
		atoll
		getenv-driver
		hcreate-driver
		printf-driver
		printf-driver-integers
		strstr-driver
		strstr-effectiveness2
		realloc-filetreewalk include
		popen-driver du include
		puts-driver
		strerror-driver
		pow_test
		getopt -ao arg path path
		getopt -a -o arg path path
		getopt -o arg -a path path
		getopt -a -o arg -- path path
		getopt -a -oarg path path
		getopt -aoarg path path
		strsep-driver
		index
		memmove
		time
		fwrite
		strchr-driver
"

COULD_FAIL="	environ
"




RETVAL="0"



checkifempty()
{
	if [ ! -s "$1" ]
	then    printf "%s\n" "empty test file, something went wrong!!"
		printf "%s\n" "Returning failure for the entire test suite!!"
		RETVAL=1
	fi
}

displaydiff()
{
	grep '^<' "${SUF}/testerr" | tail
	grep '^>' "${SUF}/testerr" | tail
}


cd hlibc-test


SUF="$(pwd)/logs/"
mkdir -p "${SUF}"

cp -r tests-comparative tests-comparative-research
cp -r tests-comparative tests-comparative-control

printf "==========COMPILING TESTS ===================================\n"
(
	cd tests-comparative-research
	CC="$2" make
)
(
	cd tests-comparative-control
	CC="$1" make
)


printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n"

printf "%s" "$BASIC_TYPE" | while read -r i
do	./tests-comparative-research/${i} > "${SUF}/diff2"	# don't quote ./tests/{i} or ./control/{i} 
	./tests-comparative-control/${i} > "${SUF}/diff3"	# so that they can be expanded as arguments
	checkifempty "${SUF}/diff2"
	if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
	then	printf "%s\n" "\`${i}' compared equal to its control method"
	else	printf "%s\n" "##${i} failed to compare equal to its control method"
		echo RETVAL="1" > retval
		displaydiff
	fi
done

#if [ -f retval ]
#then	. retval
#	rm retval
#fi


(
	cd libc-test-fork
	CC=$2 make
	./testsuite
)


exit $RETVAL

