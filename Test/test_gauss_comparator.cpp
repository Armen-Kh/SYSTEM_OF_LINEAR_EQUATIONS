#include "file_reader.hpp"
#include "file_writer.hpp"
#include "sle_matrix.hpp"
#include "utility.hpp"

#include <iostream>
#include <cstdlib> //std::abs() or std::fabs()
#include <cstddef>
#include <string>

//comparing the data, if the data difference is greater than epsilon, the result is incorrect
bool Data_Analyze(Result& G, Result& X, float& epsilon); 

void Write_Test_Conclusion (File_Writer& Fw, std::size_t& checked, std::size_t incompatible_results);

int main()
{
	File_Reader Fr_s("../Data/SLE_Gauss_Solutions.txt");
	File_Reader Fr_g("../Data/Golden_Gauss_Method.txt");
	File_Writer Fw("../Data/test_gauss_comparator.txt");
	
	Result X, G;

	float epsilon;
	std::cout << "Enter epsilon for testing: ";
	std::cin >> epsilon;
	Fw.string_writing("epsilon = ");
	Fw.float_writing(epsilon);
	std::size_t checked = 0, incompatible_results = 0;

	while(Read_Result(Fr_g, G)) {
	       if(!Read_Result(Fr_s, X)) {
		       Fw.string_writing("\nThe results is incomplete, golden file contains more data ..\n");
		       break;
	       }

	       if(G.get_number() != X.get_number()) {
		       Fw.string_writing("\nThere is a mismatch of solution's numbers: ");
		       Fw.sizet_writing(G.get_number());
		       Fw.string_writing(" -> ");
		       Fw.sizet_writing(X.get_number());

	       }
	       if(G.get_state() != X.get_state() ||
		  G.get_size() != X.get_size() ||
		  !Data_Analyze(G, X, epsilon)) {
		       Fw.string_writing("\nIncompatible_results: ");
		       Fw.char_writing('#');
		       Fw.sizet_writing(G.get_number());
		       ++incompatible_results;
	       }
	       ++checked;
	}
	
	Write_Test_Conclusion (Fw, checked, incompatible_results);
	std::cout << "\nTest results are presented in \"test_gauss_comparator.txt\" file (folder Data).\n";
	return 0;
}

bool Data_Analyze(Result& G, Result& X, float& epsilon) 
{
	for(std::size_t i = 0; i < G.get_size(); ++i) {
		float diff = std::abs(G(i) - X(i));
		if(diff > epsilon) {
			return false;
		}
	}
	return true;
}	


void Write_Test_Conclusion (File_Writer& Fw, std::size_t& checked, std::size_t incompatible_results)
{
	Fw.string_writing("\n=====================================================================");
	Fw.string_writing("\nChecked solutions: ");
	Fw.sizet_writing(checked);
	Fw.string_writing("\nIncompatible_results: ");
	Fw.sizet_writing(incompatible_results);
	Fw.string_writing(", percentage: ");
	Fw.float_writing((incompatible_results == 0) ? 0 : (100 * float(incompatible_results) / checked));
	Fw.char_writing('%');
	Fw.string_writing("\n=====================================================================");
}






















