program_NAME := BadassHeroes

program_CXX_SRCS := $(wildcard *.cpp)
program_CXX_OBJS  := ${program_CXX_SRCS:.cpp=.o}

program_INCLUDE_DIRS :=

program_LIBRARIES := GL glfw SDL SDL_image

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))

LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))

LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

$(program_NAME): $(program_CXX_OBJS)
	$(LINK.cc) $(program_CXX_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_CXX_OBJS)