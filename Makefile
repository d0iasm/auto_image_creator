analysis: analysis.cpp
	g++ -o analysis.out analysis.cpp `mecab-config --cflags` `mecab-config --libs`

processing: processing.cpp
	g++ -std=c++11 -o processing.out processing.cpp -I/usr/local/include/opencv2 -I/usr/local/include/opencv -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui `pkg-config --cflags --libs opencv`


