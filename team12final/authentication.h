/**
 * @file doxygen.config
 * @authoer Jisoo Lee
 * @date Nov 28th, 2017
 * @brief Contains methods that deals with basic logins, sign ups, retrival of user password.
 *
 * Uses dbo.h to do methods such as logins, sign ups, and retriving password for users who would forget their password.
 *
 */

#ifndef AUTHENTICATION_H_
#define AUTHENTICATION_H_
#include "user.h"
#include "dbo.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

/**
 * @brief Class that create Authentication object
 *
 * All methods that deals with the authentication side of the project. Such as login, sign up, password retrieval.
 */
class Authentication {
    
public:
    
    /**
     * @brief basic constructor for a Authentication object
     *
     * This constructor initilizes a Authentication object with no parameters and returns empty Authentication
     * object that can handle various methods for user authentication.
     * @parameters none
     * @returns empty Authentication object
     */
    Authentication() {
        
    };
    
    /**
     * @brief a function that hashes the password.
     *
     * Function that returns a hashed value of the password so user's password is kept private from others.
     * @parameters password: string value which will be user's input password.
     * @returns Hash: an unsigned integer which is going to be converted from string password.
     */
    unsigned int simple_hash(string password) {
        unsigned int Init = 5674356; // Random value
        unsigned int Hash = 0; // Initial value that will contain he password value
        
        for (int i = 0; i < password.length(); i++) {
            Hash = Hash ^ (password[i]);
            Hash = Hash * Init;
        }
        return Hash;
    };
    
    /**
     * @brief a function that converts unsigned integer to hexadecimal string value.
     *
     * Function that converts unsigned integer to hexadecimal string value, which will be used often for
     * converting hashed value for password back to string.
     * @parameters hash: unsigned integer which will be hashed value of user input for password.
     * @returns hexHash: a string which is converted from unsigned integer to string with hexadecimal value.
     */
    string ToHex(unsigned int hash) {
        string hexHash;
        stringstream hexstream;
        hexstream << hex << hash;
        hexHash = hexstream.str();
        std::transform(hexHash.begin(), hexHash.end(), hexHash.begin(), ::toupper);
        return hexHash;
    };
    
    /**
     * @brief a function that applies function simple_hash and ToHex function to a string value.
     *
     * Function that converts a string to a hashed hexadecimal string value.
     * @parameters password: string value which will be user's input password.
     * @returns a string which is converted from unsigned integer to string with hexadecimal value.
     */
    string hashPassword(string password) {
        return ToHex(simple_hash(password));
    };
    
    /**
     * @brief a function that creates account.
     *
     * Function that uses dbo.h to create a new account that contains basic information about user.
     * @parameters firstName: string value with user's first name.
     *             lastName: string value with user's last name.
     *             userName: string value with user's username, which will be the name of directory created through dbo.h
     *             password: string value with user's password.
     *             secQues: string value with user's security question.
     *             secAns: string value with user's security answer.
     * @returns none.
     */
    void createAccount(string firstName, string lastName, string userName, string password, string secQues, string secAns) {
        string hashedPW = hashPassword(password);
        DatabaseObject *db;
        db->createAccount(firstName, lastName, userName, hashedPW, secQues, secAns);
    };
    
    /**
     * @brief a function that checks if username already exists
     *
     * Function that uses dbo.h to traverse through the database to see is username is already in use.
     * @parameters userName: string value which contains user's username.
     * @returns bool value with indication if username is already in use or not.
     */
    bool findUser(string userName) {
        DatabaseObject *db;
        return db->findUser(userName);
    };
    
    /**
     * @brief  a function that checks if the password user inputed to log in matches the password associated
     *         with user account.
     * Function that uses dbo.h to traverse to user account and checks if the password associated with that
     * user account matches the input password.
     * @parameters userName: string value which contains user's username.
     *             password: string value of input password which will be compared to password associated with account.
     * @returns  bool value with indication if password matches or not.
     */
    bool checkPassword(string userName, string password) {
        string hashedPW = hashPassword(password);
        DatabaseObject *db;
        return db->checkPW(userName, hashedPW);
    };
    
    /**
     * @brief a function that gets the security question associated with user account.
     * Function that uses dbo.h to traverse to user account and gets the security question associated with it.
     * @parameters userName: string value which contains user's username.
     * @returns string value with the user account's security question.
     */
    string getSecQues(string userName) {
        DatabaseObject *db;
        return db->getSecQues(userName);
    };
    
    /**
     * @brief a function that gets the security answer associated with user account.
     * Function that uses dbo.h to traverse to user account and gets the security answer associated with it.
     * @parameters userName: string value which contains user's username.
     * @returns string value with the user account's security answer.
     */
    string getSecAns(string userName) {
        DatabaseObject *db;
        return db->getSecAns(userName);
    };
    
    /**
     * @brief a function that resets the password associated with user account.
     * Function that uses dbo.h to traverse to user account and changed the password associated with it with
     * input password.
     * @parameters userName: string value which contains user's username.
     *             password: string value of input password which will replace the user account's associated password.
     * @returns none.
     */
    void resetPassword(string userName, string newPassword) {
        string hashedPW = hashPassword(newPassword);
        DatabaseObject *db;
        db->resetPassword(userName, hashedPW);
    };
    
    /**
     * @brief a function that resets the user account profile.
     * Function that uses dbo.h to traverse to user account and change the profile associated with it with new
     * input values.
     * @parameters userName: string value which contains user's username.
     *             newFirstName: string value which will replace first name of user profile.
     *             newLastName: string value which will replace last name of user profile.
     *             newAddress: string value which will replace address of user profile.
     *             newCity: string value which will replace city of user profile.
     *             newProvince: string value which will replace province of user profile.
     * @returns none.
     */
    void resetProfile(string userName, string newFirstName, string newLastName, string newAddress, string newCity, string newProvince) {
        DatabaseObject *db;
        db->resetProfile(userName, newFirstName, newLastName, newAddress, newCity, newProvince);
    };
    
    /**
     * @brief a function that access in to user account in database to create user object
     * Function that uses dbo.h to traverse to user aacount, access into profile, and create a user object off of
     * those information.
     * @parameters userName: string value which contains user's username.
     * @returns user object with user account's information associated with it.
     */
    User login(string userName) {
        DatabaseObject *db;
        return db->login(userName);
    };
    
    /**
     * @brief deconstructor for Authentication
     * Function that deletes the Authentication Object
     */
    ~Authentication() {
    };
    
};

#endif //AUTHENTICATION_H_

