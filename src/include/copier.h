#ifndef _COPIER_CLASS_H_ 
	#define _COPIER_CLASS_H_ 1
	
	#include <exception>
	#include <fstream>					// needed for ifstream and ofstream
	#include <mutex>						// needed for the mutex and lock_guard

	// class responsible for copying the file
	class Copier
	{
		// public section of class
		public:
			// constructors and destructors
			Copier();
			~Copier();
			
			// getters and setters for private variables
			std::string GetSource();
			void SetSource(const std::string&);
			std::string GetDestination();
			void SetDestination(const std::string&);
			bool isFinished();
			
			std::exception_ptr GetException();
			
			// function that does the copying
			bool CreateCopy();

		// private section of class
		private:
			// private variables for source and destination filenames
			std::string source;
			std::string destination;
			
			// private variable for status
			bool status;

			// private variable for the exception pointer
			std::exception_ptr currentException;
			
			// private static mutex
			static std::mutex copy_lock;
	};
#endif
