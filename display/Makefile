CXX=g++
CXXFLAGS=-std=c++11 `pkg-config --cflags --libs opencv4`

display_solved: diplay_solved.c
	$(CXX) $(CXXFLAGS) -o display_solved diplay_solved.c