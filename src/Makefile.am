bin_PROGRAMS = test

test_CXXFLAGS = -std=c++14 ${VULKAN_CFLAGS}
test_LDADD = -lpthread ${VULKAN_LIBS}
test_SOURCES = main.cpp \
		Instance.cpp \
		PhysicalDevice.cpp \
		LogicalDevice.cpp \
		Queue.cpp
