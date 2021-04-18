#include "copier.h"

Copier::Copier()
{
	
}

Copier::~Copier()
{
	
}	
	
std::string Copier::GetSource()
{
	return source;
}

void Copier::SetSource(const std::string& filename)
{
	source = filename;
}

std::string Copier::GetDestination()
{
	return destination;
}

void Copier::SetDestination(const std::string& filename)
{
	destination = filename;
}

bool Copier::CreateCopy()
{
	// try block so it can fail gracefully
	try
	{
		std::lock_guard<std::mutex> lock(copy_lock);
		// instantiate input and output files and a string variable to transfer the data
		std::ifstream inFile{};
		std::ofstream outFile{};
		std::string line{};
		
		// use input file as a resource handle for the opensource file
		inFile.open(source);
		// use output file as a resource handle for the open destination file
		outFile.open(destination);
		
		// while std::getline successfully reads a line from the source file, store it in the variable line
		while(std::getline(inFile, line))
		{
			// write what is in the line variable to the destination file and append an endline character
			outFile << line << "\n";
		}
		
		// close files via resource handles, just to be explicit (sorry, RAII)
		inFile.close();
		outFile.close();
		
		// return true if successfully completed
		return true;
	}
	// catch any exceptions that were thrown
	catch(...)
	{
		// print generic error message to standard error output
		std::cerr << "[-] error: exception thrown during file copy" << std::endl;
	}
	
	// return false, because function execution won't reach this point if it completed successfully
	return false;
}

std::mutex Copier::copy_lock{};
