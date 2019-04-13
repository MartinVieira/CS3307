/**
 * @file doxygen.config
 * @authoer Jisoo Lee
 * @date Nov 28th, 2017
 * @brief Contains methods that deals with database.
 *
 * Creates direcotories and text files that contains information about user profiles, bridges, lights, groups and schedule
 */
#ifndef DBO_H_
#define DBO_H_
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "user.h"

using namespace Wt;
using namespace std;

/**
 * @brief Class that create DatabaseObject object
 *
 * All methods that deals with database of the project. Such as user profiles, bridges, lights, groups and schedules.
 */
class DatabaseObject {

	public:

        /**
         * @brief basic constructor for a DatabaseObject object
         *
         * This constructor initializes a DatabaseObject object with no parameteres and returns empty DatabaseObject object
         * that can handle various methods that deals with databases.
         * @parameters none
         * @returns empty DatabaseObject object
         */
		DatabaseObject() {

		};

        /**
         * @brief a function that creates account
         *
         * Function that creates a directory based off username. Inside that, create a file profile which will contain
         * user profile, and empty directory "bridges".
         * @parameters firstName: string value with user's first name.
         *             lastName: string value with user's last name.
         *             userName: string value with user's username, which will be the name of directory created through dbo.h
         *             password: string value with user's password.
         *             secQues: string value with user's security question.
         *             secAns: string value with user's security answer.
         * @returns none
         */
		void createAccount(string firstName, string lastName, string userName, string password, string secQues, string secAns) {
			ofstream file;
            // Create directories and files
            string userDirectory = "mkdir database/" + userName;
            system(userDirectory.c_str());
            string bridgeDirectory = "mkdir database/" + userName + "/bridges";
            system(bridgeDirectory.c_str());
            string filename = "database/" + userName + "/profile.txt";
            
            // Write profile.txt with user infomration.
            file.open(filename.c_str()); // open file to write
            file << password << "\n";
            file << firstName << "\n";
            file << lastName << "\n";
            file << "empty" << "\n";
            file << "empty" << "\n";
            file << "empty" << "\n";
            file << secQues << "\n";
            file << secAns << "\n";
            file.close(); // close file
		};

        /**
         * @brief a function that checks if username already exists
         *
         * Function that finds the profile.txt of the directory with userName, returns true if file opens, else it returns false.
         * This indicates if the username is already in use or not.
         * @parameteres userName: string value which contains user's username
         * @returns bool value with indication if username is already in use or not.
         */
		bool findUser(string userName) {
			string filename = "database/" + userName + "/profile.txt";
        	ifstream file(filename.c_str()); // open file to read
        	if(file.is_open()) {
        		file.close(); //close file
        		return true;
        	}
        	else return false;
		};

        /**
         * @brief a function that checks if the password user inputed to log in matches the password associated
         *         with user account.
         * Function that accesses into the profile.txt inside directory of userName, it checks the password associated with taht
         * file to see if the password of user input matches with password inside profile.txt.
         * @parameteres    userName: string value which contains user's username.
         *                    password: string value of input password which will be compared to password associated with account.
         * @returns bool value with indication if password matches or not.
         */
		bool checkPW(string userName, string password) {
			ifstream file;
			string filename = "database/" + userName + "/profile.txt";
            file.open(filename.c_str()); // open file to read
			string line;
			string result;

			if (!file) {

			}
			else {
				if (getline(file, line)) result = line; // gets first line
				file.close(); // close file
			}

			if (result.compare(password) == 0) return true;
			else return false;
		};

        /**
         * @brief a function that gets the security question associated with user account.
         * Function that accesses into the profile.txt inside directory of userName, and gets the security question associated with it.
         * @parameteres userName: string value which contains user's username.
         * @returns string value with the user account's security question.
         */
		string getSecQues(string userName) {
			ifstream file;
			string filename = "database/" + userName + "/profile.txt";
			file.open(filename.c_str()); //open file to read
			string secQues;

			for (int i = 0; i < 7; i++) {
				getline(file, secQues);
			}

            file.close(); // close file
            
			return secQues;

		};

        /**
         * @brief a function that gets the security answer associated with user account.
         * Function that accesses into the profile.txt inside directory of userName, and gets the security answer associated with it.
         * @parameters userName: string value which contains user's username.
         * @returns string value with the user account's security answer.
         */
		string getSecAns(string userName) {
			ifstream file;
			string filename = "database/" + userName + "/profile.txt";
			file.open(filename.c_str()); // open file to read
			string secAns;

			for (int i = 0; i < 8; i++) {
				getline(file, secAns);
			}

            file.close(); // close file
            
			return secAns;

		};

        /**
         * @brief a function that resets the password associated with user account.
         * Function that accesses into the profile.txt inside directory of userName, and changed the password associated with it with
         * input password.
         * @parameters userName: string value which contains user's username.
         *             password: string value of input password which will replace the user account's associated password.
         * @returns none
         */
		void resetPassword(string userName, string newPassword) {

			string filename = "database/" + userName + "/profile.txt";
			ifstream in(filename.c_str()); // open in to read
	
            // Read in every line and store to varialbe from profile.txt
			string line, password, firstName, lastName, address, city, province, secQues, secAns;
			if (getline(in, line)) password = line;
			if (getline(in, line)) firstName = line;
			if (getline(in, line)) lastName = line;
			if (getline(in, line)) address = line;
			if (getline(in, line)) city = line;
			if (getline(in, line)) province = line;
			if (getline(in, line)) secQues = line;
			if (getline(in, line)) secAns = line;
	
			in.close();

			ofstream out(filename.c_str());
	
			out << newPassword << "\n" << firstName << "\n" << lastName << "\n" << address << "\n"
			<< city << "\n" << province << "\n" << secQues << "\n" << secAns;
	
			out.close(); // close in

		};

        /**
         * @brief a a function that resets the user account profile.
         * Function that accesses into the profile.txt inside directory of userName, and change the profile associated with it with new
         * input values.
         * @parameters userName: string value which contains user's username.
         *             newFirstName: string value which will replace first name of user profile.
         *             newLastName: string value which will replace last name of user profile.
         *             newAddress: string value which will replace address of user profile.
         *             newCity: string value which will replace city of user profile.
         *             newProvince: string value which will replace province of user profile.
         * @returns none
         */
		void resetProfile(string userName, string newFirstName, string newLastName, string newAddress, string newCity, string newProvince) {

			string filename = "database/" + userName + "/profile.txt";
			ifstream in(filename.c_str()); // open in to read
	
            // Read in every line and store to varialbe from profile.txt
			string line, password, firstName, lastName, address, city, province, secQues, secAns;

			if (getline(in, line)) password = line;
			if (getline(in, line)) firstName = line;
			if (getline(in, line)) lastName = line;
			if (getline(in, line)) address = line;
			if (getline(in, line)) city = line;
			if (getline(in, line)) province = line;
			if (getline(in, line)) secQues = line;
			if (getline(in, line)) secAns = line;
	
            // close in
			in.close();

			ofstream out(filename.c_str()); // open out to write
	
            // Write the file with profile values.
			out << password << "\n" << newFirstName << "\n" << newLastName << "\n" << newAddress << "\n"
			<< newCity << "\n" << newProvince << "\n" << secQues << "\n" << secAns;
	
			out.close(); // close out

		};

        /**
         * @brief a function that access into user account in database to create user object
         * Function that accesses into the profile.txt inside directory of userName, and create a user object off of
         * those information.
         * @parameters userName: string value which contains user's username.
         * @returns user object with user account's information associated with it.
         */
		User login(string userName) {
			string filename = "database/" + userName + "/profile.txt";
            // Reads each line of the file
			string info[8];
        	int count = 0;
        	ifstream file(filename.c_str()); // open file to read
        	if(file.is_open()) {
        		for (std::string line; getline(file, line);) {
        			info[count] = line;
        			count++;
        		}
        		file.close();
        	}

            // Declare user to return
        	User user(info[1], info[2], userName, info[0], info[3], info[4], info[5], info[6], info[7]);
			return user;
		};
    
        /**
         * @brief a function that creates a new bridge file inside a bridges direcotry
         * Function that access into bridges directory inside directory of userName, and create a new text file with name
         * of bridgeName which contains information about the bridge.
         * @parameters userName: string value which contains user's username.
         *                bridgeName: string value which contains bridge name.
         *                location: string value which contains location of where bridges are associated with inside house.
         *             ipAddress: string value which contains ip address associated with bridge.
         *                portNum: integer value which contains port number of the bridge.
         *                bridgeUN: string value which contains username associated with bridge
         */
        void addBridge(string userName, string bridgeName, string location, string ipAddress, int portNum, string bridgeUN) {
            
            string filename = "database/" + userName + "/" + bridgeName + ".txt";
            //Write the file with bridge information
            ofstream file; // open file to write
            file.open(filename.c_str());
            file << location << "\n";
            file << ipAddress << "\n";
            file << portNum << "\n";
            file << bridgeUN << "\n";
            file.close(); // close file
            
        };

        /**
         * @brief deconstructor for DatabaseObject
         * Function that deletes the Database Object
         */
		~DatabaseObject() {
		};

};

#endif //DBO_H_
