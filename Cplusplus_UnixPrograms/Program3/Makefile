# Ryan Hosford
# rph160030
# CS3377
CXX=g++
OBJS=program3.o
SRCS=program3.cc

all:program3


clean:
	rm -f $(OBJS) program3

$(OBJS):$(SRCS)
	$(CXX) -c $(SRCS)

program3:$(OBJS)
	$(CXX) -o program3 $(OBJS)
