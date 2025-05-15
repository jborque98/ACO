# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -fopenmp

# Objetivos individuales
all: calculate_pi hello pointer par_b

calculate_pi: calculate_pi.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

hello: hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

pointer: pointer.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

pointer. par_b: par_b.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
# Limpieza de ejecutables
clean:
	rm -f calculate_pi hello
