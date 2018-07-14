#include <stdio.h>
#include <stdlib.h>
#include <search.h>

static char *data[] = { "alpha", "bravo", "charlie", "delta",
	 "echo", "foxtrot", "golf", "hotel", "india", "juliet",
	 "kilo", "lima", "mike", "november", "oscar", "papa",
	 "quebec", "romeo", "sierra", "tango", "uniform",
	 "victor", "whisky", "x-ray", "yankee", "zulu"
};

int main(void)
{
	ENTRY e, *ep;
	long i;

	hcreate(30);

	for (i = 0; i < 24; i++) {
		e.key = data[i];
		/* data is just an integer, instead of a
		   pointer to something */
		e.data = (void*)i;
		ep = hsearch(e, ENTER);
		/* there should be no failures */
		if (ep == NULL) {
			fprintf(stderr, "entry failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 22; i < 26; i++) {
		/* print two entries from the table, and
		   show that two are not in the table */
		e.key = data[i];
		ep = hsearch(e, FIND);
		printf("%s -> %s:%ld\n", e.key,
			   ep ? ep->key : "NULL", ep ? (long)(ep->data) : 0);
	}
	hdestroy();
	exit(EXIT_SUCCESS);
}

