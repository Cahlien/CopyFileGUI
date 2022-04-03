#ifndef COPIER_CLASS_H
	#define COPIER_CLASS_H
	
	#include <fstream>
	#include <mutex>

	#include "copyapp.h"
	
	
	class Copier
	{
		public:
			Copier();
			~Copier();
			
			std::string GetSource();
			void SetSource(const std::string&);
			std::string GetDestination();
			void SetDestination(const std::string&);
			
			static void CreateCopy(Copier);

		private:
			std::string source;
			std::string destination;
			
			static std::mutex copy_lock;
	};
#endif
