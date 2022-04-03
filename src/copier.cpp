#include "copier.h"
	
std::mutex Copier::copy_lock{};


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


void Copier::CreateCopy(Copier copier)
{
	reinterpret_cast<CopyApp*>(wxTheApp)->RegisterCopier();
	std::lock_guard<std::mutex> lock(copy_lock);
	
	std::ifstream inFile{};
	std::string line{};
	
	inFile.open(copier.GetSource());
	std::ofstream outFile{};
	std::getline(inFile, line);
	
	if(line.length() > 0)
	{
		outFile.open(copier.GetDestination());
		outFile << line << "\n";
		while(std::getline(inFile, line))
		{
			outFile << line << "\n";
		}
				

	}
	else
	{
		std::string filename = "failed_" + copier.destination;
		outFile.open(filename);
		outFile << "Error: file " << copier.source << " is empty or does not exist." << std::endl;
	}
	
	inFile.close();
	outFile.close();
	reinterpret_cast<CopyApp*>(wxTheApp)->DeregisterCopier();
}
