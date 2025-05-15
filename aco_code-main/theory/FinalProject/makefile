# Makefile

CXX      := g++
CXXFLAGS := -std=c++17 -O3 -fopenmp
TARGET   := solar_system

SRCS := \
    main.cpp \
    SolarSystem.cpp \
    Euler.cpp \
    EulerCromer.cpp \
    LeapFrog.cpp \
    RK4.cpp \
    MultiRateLeapFrog.cpp \
    MultiRateRK4.cpp \
    Yoshida.cpp

OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla implícita para .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
