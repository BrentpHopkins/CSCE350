all: Hopkins_Brent_QuickSort.cpp Hopkins_Brent_InputFileGenerator.cpp
	g++ Hopkins_Brent_QuickSort.cpp -o Hopkins_Brent_QuickSort
	g++ Hopkins_Brent_InputFileGenerator.cpp -o Hopkins_Brent_InputFileGenerator

generate_files: Hopkins_Brent_InputFileGenerator
	./Hopkins_Brent_InputFileGenerator

process_files: Hopkins_Brent_QuickSort
	./Hopkins_Brent_QuickSort
clean:
	rm ../data/*.txt

