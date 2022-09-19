/**
Author: Hunter Schemidt
Date: 09/16/2022

Defind Class Agent (Person)
*/

class Person {
	private:
		
	public: 
		char prevStatus = 'P';
		char status = 'P'; // normal 'P', infected 'I', recoverd 'R'
		
		Person(char s) {
			status = s;
			prevStatus = s;
		}
		~Person() = default;
		Person(const Person&) = default;
		Person& operator=(const Person&) = default;
		
};
