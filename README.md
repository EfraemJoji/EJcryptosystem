# EJcryptosystem
The EJ (Efraem Joji’s) cryptosystem is a public-key cryptosystem with key exchange, asymmetric encryption and digital signature. It is based on the associative binary relation of square matrix multiplication, with all matrix elements reduced modulo a prime number (here, chosen to be the mersenne prime  ).
	It currently gives about 256 bits security for a 288 bit key , that is, double the bits of security of Elliptic Curve Cryptography and about 14 times that of RSA(Rivest-Shamir-Adleman) . It is about 24 times faster than the RSA and about 9 times faster than ECDH (Elliptic Curve Diffie Hellman)  .
  → RSA 4096 bits is almost comparable in bits of security to EJ cryptosystem 288 bits
	$ openssl speed rsa4096 
	sign/s = 59.6   verify/s = 3825.3

→ ECDH - 521 bit is almost comparable in bits of security to EJ cryptosystem 288 bits
 	$ openssl speed ecdh
	Doing 521 bits  ecdh's for 10s: 10994 521-bits ECDH ops in 10.00s

→ EJ cryptosystem 288 bits
	$ g++ -O2 -m64 test.cpp ; ./a.out
	100368 operations per second.
  
