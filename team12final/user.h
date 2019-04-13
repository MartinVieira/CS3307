/**
  * @file doxygen.config
  * @authoer Jisoo Lee
  * @date Nov 28th, 2017
  * @brief Contains methods that deals with user informations
  *
  * Class which contains contructors and methods for user information.
  *
  */

#ifndef USER_H_
#define USER_H_
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

/**
  * @brief Class that creates User object
  *
  * All methods such as getter and setter of the user informations.
  */
class User {
        // private variables
        // secQues == security question, secAns == security answer
        string firstName, lastName, userName, password, address, city, province, secQues, secAns;

    public:

        /**
          * @brief basic constructor for a User object
          *
          * This constructor intitializes a User object with no parameters and returns empty User object that can handle
          * various methods dealing with user information.
          * @parameters none
          * @returns empty User object
          */
        User() {
            firstName = "";
            lastName = "";
            userName = "";
            password = "";
            address = "";
            city = "";
            province = "";        // change variable to ipAddress
            secQues = "";
            secAns = "";
        };

        /**
         * @brief constructor for a User object that has parameters
         *
         * This constructor intitializes a User object with parameters and returns User object with user information
         * that can handle various methods.
         * @parameters firstName: string value containing first name of user
         *             lastName: string value containing last name of user
         *             newUserName: string value containing user's userName
         *             newPassword: string value containing user's password
         *             newAddress: string value containing user's address
         *             newCity: string value containing user's city
         *             newProvince: string value containing user's province
         *             newSecQues: string value containing user's security question
         *             newSecAns: string value containing user's security answer
         * @returns User object
         */
        User(string newFirstName, string newLastName, string newUserName, string newPassword, string newAddress, string newCity, string newProvince, string newSecQues, string newSecAns) {
            firstName = newFirstName;
            lastName = newLastName;
            userName = newUserName;
            password = newPassword;
            address = newAddress;
            city = newCity;
            province = newProvince;
            secQues = newSecQues;
            secAns = newSecAns;
        };

        /**
         * @brief getter method for firstName;
         *
         * Getter method that returns the first name of the user object.
         * @parameters none
         * @returns firstName: string value containing user's first name
         */
        string getFirstName() {
            return firstName;
        };

        /**
         * @brief getter method for lastName;
         *
         * Getter method that returns the last name of the user object.
         * @parameters none
         * @returns lastName: string value containing user's last name
         */
        string getLastName() {
            return lastName;
        };

        /**
         * @brief setter method for firstName and lastName
         *
         * Setter methods that declares new first name and last name
         * @parameters newFirstName: string value containing user's new first name
         *             newLastName: string value containing user's new last name
         * @returns none
         */
        void setName(string newFName, string newLName) {        // 
            firstName = newFName;
            lastName = newLName;
        };

        /**
         * @brief getter method for userName;
         *
         * Getter method that returns the username of the user object
         * @parameters none
         * @returns userName: string balue containing user's username
         */
        string getUserName() {
            return userName;
        };
    
        /**
         * @brief getter method for address;
         *
         * Getter method that returns the address of the user object
         * @parameters none
         * @returns address: string balue containing user's address
         */
        string getAddress() {
            return address;
        };
    
        /**
         * @brief setter method for address
         *
         * Setter methods that declares new address
         * @parameters newAddress: string value containing user's new address
         * @returns none
         */
        void setAddress(string newAddress) {
            address = newAddress;
        };
    
        /**
         * @brief getter method for city;
         *
         * Getter method that returns the city of the user object
         * @parameters none
         * @returns city: string balue containing user's city
         */
        string getCity() {
            return city;
        };
    
        /**
         * @brief setter method for city
         *
         * Setter methods that declares new city
         * @parameters newCity: string value containing user's new city
         * @returns none
         */
        void setCity(string newCity) {
            city = newCity;
        };
    
        /**
         * @brief getter method for province;
         *
         * Getter method that returns the province of the user object
         * @parameters none
         * @returns province: string balue containing user's province
         */
        string getProvince() {
            return province;
        };
    
        /**
         * @brief setter method for province
         *
         * Setter methods that declares new province
         * @parameters newProvince: string value containing user's new province
         * @returns none
         */
        void setProvince(string newProvince) {
            province = newProvince;
        };
    
        /**
         * @brief getter method for secQues;
         *
         * Getter method that returns the security question of the user object
         * @parameters none
         * @returns province: string balue containing user's security question
         */
        string getSecQues() {
            return secQues;
        };
    
        /**
         * @brief setter method for secQues
         *
         * Setter methods that declares new security question
         * @parameters newSecQues: string value containing user's new security question
         * @returns none
         */
        void setSecQues(string newSecQues) {
            secQues = newSecQues;
        };
    
        /**
         * @brief getter method for secAns;
         *
         * Getter method that returns the security answer of the user object
         * @parameters none
         * @returns province: string balue containing user's security answer
         */
        string getSecAns() {
            return secAns;
        };
    
        /**
         * @brief setter method for secAns
         *
         * Setter methods that declares new security answer
         * @parameters newSecAns: string value containing user's new security answer
         * @returns none
         */
        void setSecAns(string newSecAns) {
            secAns = newSecAns;
        };
    
        /**
         * @brief deconstructor for User
         * Function that deletes the User Object
         */
        ~User() {
        };

};

#endif /* USER_H_ */
