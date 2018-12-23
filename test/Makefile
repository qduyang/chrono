SOURCES = main.cpp test_timer.cpp
CC = g++

CXXFLAGS = -O3 -Wall -std=c++17 -DBOOST_ASIO_HAS_STD_CHRONO -Wunused-variable -Wno-overloaded-virtual -fdata-sections -ffunction-sections

TEST 		= test_chrono
TEST_G 	= $(TEST)-g
NDEBUG 	= -DNDEBUG
DEBUG		= -g -O0

BUILDDIR = ../build/chrono

INCLUDES = -I. -I.. -I../include -I/usr/local/include -I/usr/include

BOOST_LIB_PATH = /usr/lib64
# STATIC_LIBS = $(BOOST_LIB_PATH)/libboost_date_time.a $(BOOST_LIB_PATH)/libboost_system.a
LIBS = -L$(BOOST_LIB_PATH) -lboost_date_time -lboost_system -lpthread

DEBUG_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%-g.o,$(SOURCES))
DEBUG_DEPS = $(patsubst %.cpp,$(BUILDDIR)/%-g.d,$(SOURCES))

-include $(DEPS)
-include $(DEBUG_DEPS)

debug: $(TEST_G)

$(TEST_G): $(DEBUG_OBJS)
	$(CC) $(CCTYPE) $(CXXFLAGS) $(LDFLAGS) $(DEBUG_OBJS) $(LIBS) $(DEBUG) -o$(TEST_G) $(STATIC_LIBS)

$(BUILDDIR)/%-g.o:%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CXXFLAGS) $(INCLUDES) $(DEBUG) -MD -MF $(BUILDDIR)/$*-g.d -c $< -o $@

clean:
	-rm -rf *.o *.d *~ $(TEST_G) $(BUILDDIR)

