CC= gcc
CCFLAGS= -Wall -Wextra -std=c17 -g

SRC_DIR= src
PLANNERSRC= $(SRC_DIR)/calender.c
PLANNEROBJ = $(PLANNERSRC:.c=.o)

TEST_DIR= tests
TESTSRC = $(TEST_DIR)/utests
TESTOBJ = $(TESTSRC:.c=.o)

TESTTARGET= utests

test: $(TESTTARGET)

$(TESTTARGET): $(TESTOBJ) $(PLANNEROBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<


clean:
	rm $(PLANNEROBJ) $(TESTOBJ)