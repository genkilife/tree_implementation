include makefile.inc

all: bin/test_binaryTree_02 bin/test_binaryTree_03 bin/test_avlTree_02 bin/test_avlTree_03 bin/test_bplusTree_02 bin/test_bplusTree_03

run:
	./bin/test_binaryTree_02
	./bin/test_binaryTree_03
	./bin/test_avlTree_02
	./bin/test_avlTree_03
	./bin/test_bplusTree_02
	./bin/test_bplusTree_03

# c file dependencies
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# test object files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp $(INCLUDEROOT)/$(wildcard *.h)
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# binary dependencies
$(BINDIR)/%: $(OBJDIR)/%.o $(OBJECTS)
	@$(CXX) $(OBJECTS) $< $(LFLAGS) -o $@
	@echo "Link "$<"!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*
	@$(rm) $(BINDIR)/*
	@echo "Cleanup complete!"
