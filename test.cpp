/*
 * 
 * Program to test the working of the EJ cryptosystem, as contained
 * in the file "ejcrypto.cpp" in the same directory as this file
 * 
 * This software is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1 (LGPL 2.1) .
 * A copy of it can be found at the URL https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 * Another copy of it is contained in the file "LICENSES" in the same directory as this file.
 * 
 */

#include <iostream>
#include <random>
#include <chrono>

#include "ejcrypto.h"

#define ull unsigned long long
#define u32 unsigned int

const ull no_of_iterations = 400000;

//using namespace std;

int main() {
std::cout << "\nStarting " << no_of_iterations << " iterations of the EJ cryptosystem\n";

//Initialize C++ MT19937 Mersenne twister based random number generator
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<ull> uni(0,0xffffffff) ;; // guaranteed unbiased

//The first 256 bits of the fractional part of the mathematical constant Pi is used as the base matrix ( ie. a nothing-up-my-sleeve-number )
u32 base[9] = { 0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344, 0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89, 0x452821E6 };

bool are_all_correct = 1;
auto t1 = std::chrono::high_resolution_clock::now();
ull one_fourth_no_of_iterations = no_of_iterations / 4;
u32 pubkey_A[9], pubkey_B[9], secret_A[9], secret_B[9], privkey_A[9], privkey_B[9], privkey[9], pubkey[9], hash[9], nonce[18];
u32 testing=0;
u32 mask = 0;
int IsTestingOn = 0;

privkey_A[0] =  uni(rng);
privkey_A[1] =  uni(rng);
privkey_A[2] =  uni(rng);
privkey_A[3] =  uni(rng);
privkey_A[4] =  uni(rng);
privkey_A[5] =  uni(rng);
privkey_A[6] =  uni(rng);
privkey_A[7] =  uni(rng);
privkey_A[8] =  uni(rng);

privkey_B[0] =  uni(rng);
privkey_B[1] =  uni(rng);
privkey_B[2] =  uni(rng);
privkey_B[3] =  uni(rng);
privkey_B[4] =  uni(rng);
privkey_B[5] =  uni(rng);
privkey_B[6] =  uni(rng);
privkey_B[7] =  uni(rng);
privkey_B[8] =  uni(rng);

for( ull i = 0 ; i < one_fourth_no_of_iterations ; i++) {
  // Do each loop only one-fourth the times of no_of_iterations
  // Because each pass through this loop has 4 calls to the ModMatrixExpon() function
  //That function is the main operation of EJ cryptosystem, as elliptic curve multiplication is to elliptic curve cryptosystems

  /*
  //Uncomment to generate new random numbers each iterations
  //But then, the speed measured will be less due to time taken by the random number generator
  privkey_A[0] =  uni(rng);
  privkey_A[1] =  uni(rng);
  privkey_A[2] =  uni(rng);
  privkey_A[3] =  uni(rng);
  privkey_A[4] =  uni(rng);
  privkey_A[5] =  uni(rng);
  privkey_A[6] =  uni(rng);
  privkey_A[7] =  uni(rng);
  privkey_A[8] =  uni(rng);
  
  privkey_B[0] =  uni(rng);
  privkey_B[1] =  uni(rng);
  privkey_B[2] =  uni(rng);
  privkey_B[3] =  uni(rng);
  privkey_B[4] =  uni(rng);
  privkey_B[5] =  uni(rng);
  privkey_B[6] =  uni(rng);
  privkey_B[7] =  uni(rng);
  privkey_B[8] =  uni(rng);
  */
  
  
  //***Alice generates her public key.***/
  ModMatrixExpon( pubkey_A, base, privkey_A );

  //***Bob generates his public key.***/
  ModMatrixExpon( pubkey_B, base, privkey_B);

  ModMatrixExpon( secret_B, pubkey_A, privkey_B); //Bob generates his secret_B , which should be equal to secret_A

  ModMatrixExpon( secret_A, pubkey_B, privkey_A); //Alice generates her secret_A , which should be equal to secret_B
  
  /*
  //Uncomment to test whether everything is working (obviously, testing is an overhead)
  mask = 0;
  //Compare A and B
  mask |= ( secret_A[0] ^ secret_B[0] ) | ( secret_A[1] ^ secret_B[1] ) | ( secret_A[2] ^ secret_B[2] ) | ( secret_A[3] ^ secret_B[3] ) | ( secret_A[4] ^ secret_B[4] ) | ( secret_A[5] ^ secret_B[5] ) | ( secret_A[6] ^ secret_B[6] ) | ( secret_A[7] ^ secret_B[7] ) | ( secret_A[8] ^ secret_B[8] );
  if ( ( (u32) (mask | (~mask + 1) ) >> 31) == 1 ) are_all_correct=0; 
  testing |= secret_A[0] | secret_A[1] | secret_A[2] | secret_A[3] | secret_A[4] | secret_A[5] | secret_A[6] | secret_A[7] | secret_A[8];
  IsTestingOn = 1;
  */
}

if ( IsTestingOn == 1 ) { //Print messages like "Failed", "Successful" only if testing was enabled, otherwise just print speed
	if ( (are_all_correct == 1) && (testing != 0) ) {
		std::cout << "Successful. \n";
	}
	else if (testing == 0) std::cout << "--------------Failed, all of the secrets are Zeroes (0s).----------------\n";
	else std::cout << "-------Failed---------- \n";
}

auto t2 = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
double TotalSeconds = (double) duration / 1000000;
std::cout << TotalSeconds << " seconds taken.\n";
double ops_per_sec = (double) no_of_iterations / TotalSeconds;
std::cout << ops_per_sec << " " << "operations per second.\n";
return 0;
}
