#include "copier.h"
	
// static mutex initialization; will replace with a more elegant solution eventually
std::mutex Copier::copy_lock{};

// default constructor
Copier::Copier()
{
	currentException = nullptr;
	status = false;
}

// destructor
Copier::~Copier()
{
	
}	
	
// get source filename
std::string Copier::GetSource()
{
	return source;
}

// set source filename
void Copier::SetSource(const std::string& filename)
{
	source = filename;
}

// get destination filename
std::string Copier::GetDestination()
{
	return destination;
}

// set destination filename
void Copier::SetDestination(const std::string& filename)
{
	destination = filename;
}

bool Copier::isFinished()
{
	return status;
}

std::exception_ptr Copier::GetException()
{
	return currentException;
}

// the function that this whole app exists to call
bool Copier::CreateCopy()
{
	// try block so it can fail gracefully
	try
	{
		// instantiate a lock_guard with the static mutex to avoid data races; heavy-handed solution
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
		status = true;
	}
	catch(std::exception& e)
	{
		currentException = std::current_exception();
	}
	// return false, because function execution won't reach this point if it completed successfully
	return status;
}
