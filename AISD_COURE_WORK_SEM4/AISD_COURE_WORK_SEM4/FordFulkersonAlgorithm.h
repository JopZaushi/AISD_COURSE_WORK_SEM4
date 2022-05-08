#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
using namespace std;

char* read_file() {
	const int buff = 512;
	char* start_text = new char[buff];
	//input from file
	std::ifstream filein("Чтение.txt"); 	// open file for reading
	filein.unsetf(ios::skipws);
	if (!filein.is_open()) //if file not found
		std::cout << "Ошибка открытия файла!";
	while (!filein.eof()) {
		filein.getline(start_text, buff, '.'); //until end of file
	}
	filein.close();

	return start_text;
}

String string_peaks(char* start_text) {
	//select all paths
	int number = 0;
	int check = 0;
	char space = ' ';
	String all_way;
	String only_peaks;
	while (start_text[number] != '.') {
		if (check == 2) break;
		while (start_text[number] != ';') {
			if (check == 1) {
				check++;
				break;
			}
			all_way = all_way + start_text[number];
			number++;
			if (start_text[number] == ';') {
				all_way = all_way + space;
				number++;
			}
			if (start_text[number] == 'N' && start_text[number + 1] == '/' && start_text[number + 2] == 'A') {
				while (start_text[number] != ';') {
					number++;
				}
				number++;
			}
			if (start_text[number] >= 48 && start_text[number] <= 57) {
				while (start_text[number] != '\n') {
					if (start_text[number] == '\0') {
						check++;
						break;
					}
					number++;
				}
				number++;
			}
		}
	}

	//definition of vertices in a single instance
	number = 0;
	while (number != all_way.length) {
		if (only_peaks.length == 0) {
			while (all_way[number] != space) {
				only_peaks = only_peaks + all_way[number];
				number++;
			}
			only_peaks = only_peaks + space;
			number++;
		}
		else {
			String vertex_from_list;
			//take a vertex from the whole list
			while (all_way[number] != space) {
				vertex_from_list = vertex_from_list + all_way[number];
				number++;
			}
			//compare it with the main
			for (int i = 0; i < only_peaks.length; i++) {
				String vertex_for_comparison;
				while (only_peaks[i] != space) {
					vertex_for_comparison = vertex_for_comparison + only_peaks[i];
					i++;
				}
				if (vertex_for_comparison == vertex_from_list) {
					number++;
					break;
				}
				if (i + 1 == only_peaks.length) {
					only_peaks = only_peaks + vertex_from_list;
					only_peaks = only_peaks + space;
					number++;
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
					while (vertex_from_list.empty()) {
						vertex_from_list.pop_last_simv();
					}
					break;
				}
				else {
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
				}
			}
		}

	}
	return only_peaks;
}

int dimension(String only_peaks) {
	int number = 0, matrix_dimension = 0;
	char space = ' ';
	while (number != only_peaks.length) {
		if (only_peaks[number] == space) matrix_dimension++;
		number++;
	}
	return matrix_dimension;
}


int** initial_matrix(char* start_text, String only_peaks) {
	int matrix_dimension = dimension(only_peaks);
	//matrix creation
	int** matrix = new int* [matrix_dimension];
	for (int i = 0; i < matrix_dimension; i++) {
		matrix[i] = new int[matrix_dimension];
	}
	//matrix initialization
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			matrix[i][j] = 0;
		}
	}

	//matrix filling
	int number = 0;
	while (start_text[number] != '\0') {
		String departure_point;
		String place_of_arrival;
		int vertex1 = 0, vertex2 = 0;
		int weight = 0;
		//read the vertex from the first line
		while (start_text[number] != ' ') {
			departure_point = departure_point + start_text[number];
			number++;
		}
		number++;
		while (start_text[number] != ' ') {
			place_of_arrival = place_of_arrival + start_text[number];
			number++;
		}
		number++;

		//from 1 vertex to 2
		while (start_text[number] != '\n') {
			weight += start_text[number] - '0';
			if (start_text[number + 1] == '\0') {
				number++;
				break;
			}
			if (start_text[number + 1] == '\n') {
				number++;
				break;
			}
			else {
				weight *= 10;
				number++;
			}
		}

		//filling cells
		if (start_text[number] == '\n' || start_text[number] == '\0') {
			// work with 1 vertex
			for (int i = 0; i < only_peaks.length; i++) {
				String vertex_for_comparison;
				while (only_peaks[i] != ' ') {
					vertex_for_comparison = vertex_for_comparison + only_peaks[i];
					i++;
				}
				vertex1++;
				if (vertex_for_comparison == departure_point) {
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
					break;
				}
				else {
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
				}
			}
			// work with 2 vertex
			for (int i = 0; i < only_peaks.length; i++) {
				String vertex_for_comparison;
				while (only_peaks[i] != ' ') {
					vertex_for_comparison = vertex_for_comparison + only_peaks[i];
					i++;
				}
				vertex2++;
				if (vertex_for_comparison == place_of_arrival) {
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
					break;
				}
				else {
					while (vertex_for_comparison.empty()) {
						vertex_for_comparison.pop_last_simv();
					}
				}
			}
			matrix[vertex1 - 1][vertex2 - 1] = weight;
			if (start_text[number] == '\0') {
				break;
			}
			else number++;
		}

	}

	return matrix;
}

void print_matrix(int** matrix) {
	int matrix_dimension = dimension(string_peaks(read_file()));
	//output matrix
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

int min_number(int* array) {
	int min_elem = INT_MAX;
	int matrix_dimension = dimension(string_peaks(read_file()));
	for (int i = 0; i < matrix_dimension; i++) {
		if (array[i] < min_elem && array[i] > 0) min_elem = array[i];
	}
	return min_elem;
}

int Ford_Fulkerson_Algorithm(int** matrix_way, String only_peaks) {
	int matrix_dimension = dimension(string_peaks(read_file()));
	//matrix creation
	int maximum_flow = 0;
	int** matrix_flow = new int* [matrix_dimension];
	for (int i = 0; i < matrix_dimension; i++) {
		matrix_flow[i] = new int[matrix_dimension];
	}
	//matrix initialization
	for (int i = 0; i < matrix_dimension; i++) {
		for (int j = 0; j < matrix_dimension; j++) {
			matrix_flow[i][j] = 0;
		}
	}
	bool check = false;
	while (check != true) {
		bool check3 = false;
		int* way = new int[matrix_dimension];
		int index = 0;
		int index1 = -1, index2 = -1;
		for (int i = 0; i < matrix_dimension; i++) {
			for (int j = 0; j < matrix_dimension; j++) {
				if (matrix_way[i][matrix_dimension - 1] != 0) {
					way[index] = matrix_way[i][matrix_dimension - 1];
					index1 = i; index2 = matrix_dimension - 1;
					i = matrix_dimension - 1;
					j = matrix_dimension - 1;
					index++;
					check3 = true;
				}
				else {
					if (matrix_way[i][j] != 0 && j != 0) {
						if (i == index2 && j == index1) {
							continue;
						}
						else {
							way[index] = matrix_way[i][j];
							index1 = i; index2 = j;
							i = j;
							j = 0;
							index++;
						}
					}
				}
			}
			if (i == matrix_dimension - 1) {
				int min_elem = min_number(way);
				maximum_flow += min_elem;
				index1 = -1; index2 = -2;
				for (int i = 0; i < matrix_dimension; i++) {
					for (int j = 0; j < matrix_dimension; j++) {
						if (matrix_way[i][matrix_dimension - 1] != 0) {
							matrix_way[i][matrix_dimension - 1] -= min_elem;
							matrix_flow[matrix_dimension - 1][i] += min_elem;
							index1 = i; index2 = matrix_dimension - 1;
							i = matrix_dimension - 1;
							j = matrix_dimension - 1;
							index++;
						}
						else {
							if (matrix_way[i][j] != 0 && j != 0) {
								if (i == index2 && j == index1) {
									continue;
								}
								else {
									matrix_way[i][j] -= min_elem;
									matrix_flow[j][i] += min_elem;
									index1 = i; index2 = j;
									i = j;
									j = 0;
								}
							}
						}
					}
				}
				for (int i = 0; i < matrix_dimension; i++) {
					for (int j = 0; j < matrix_dimension; j++) {
						matrix_way[i][j] += matrix_flow[i][j];
						matrix_flow[i][j] = 0;
					}
				}

				delete[]way;
				int check2 = 0;
				for (int t = 0; t < matrix_dimension; t++) {
					if (matrix_way[t][matrix_dimension - 1] == 0) check2++;
				}
				if (check2 == matrix_dimension) check = true;
				if (check3 == false) check = true;

				break;
			}
		}
	}
	cout << "End Matrix" << endl;
	print_matrix(matrix_way);
	return maximum_flow;
}