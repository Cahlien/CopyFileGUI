#include <fstream>
#include <thread>
#include <mutex>
#include <iostream>

class Copier
{
	public:
		Copier();
		~Copier();
		
		std::string GetSource();
		void SetSource(const std::string&);
		std::string GetDestination();
		void SetDestination(const std::string&);

		bool CreateCopy();
	private:
		std::string source;
		std::string destination;
		static std::mutex copy_lock;
};
