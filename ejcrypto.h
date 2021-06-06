/*
 * 
 * The core of the EJ cryptosystem.
 * 
 * Implements matrix multiplication and exponentiation, with all matrix elements reduced modulo a prime (here, the mersenne prime 2^31 - 1)
 * 
 * This software is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1 (LGPL 2.1) .
 * A copy of it can be found at the URL https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 * Another copy of it is contained in the file "LICENSE" in the same directory as this file.
 * 
 */

#define ull unsigned long long
#define u32 unsigned int

void ModMatrixExpon(u32* res , const u32* base , const u32* expon);
void MatrixMul(u32 *r , const u32 *a , const u32 *b);

const ull MODM31 = 0x7FFFFFFF;

//Copy array "in" to array "out"
inline void Copy ( u32 *out , const u32 *in ) {
out[0] = in[0] ;
out[1] = in[1] ;
out[2] = in[2] ;
out[3] = in[3] ;
out[4] = in[4] ;
out[5] = in[5] ;
out[6] = in[6] ;
out[7] = in[7] ;
out[8] = in[8] ;
}

 /**
  * @brief Matrix multiplication with all elements reduced modulo a prime (here, 2^31 - 1)
  * @param[out] Resulting matrix R = A * B , with all elements reduced modulo 0x7FFFFFFF
  * @param[in] 3x3 matrix A , with all elements reduced modulo 0x7FFFFFFF
  * @param[in] 3x3 matrix B , with all elements reduced modulo 0x7FFFFFFF
  **/
inline void MatrixMul(u32 *r , const u32 *a , const u32 *b)
{
	
 register ull t = 0;
 
 t = (ull) a[0]*b[0] ;
 t += (ull) a[1]*b[3] ;
 t += (ull) a[2]*b[6] ;
 t = (t & MODM31) + (t>>31); 
 r[0] = (t & MODM31) + (t>>31);
 
 t = (ull) a[0]*b[1] ;
 t += (ull) a[1]*b[4] ;
 t += (ull) a[2]*b[7] ;
 t = (t & MODM31) + (t>>31); 
 r[1] = (t & MODM31) + (t>>31);
 
 t = (ull) a[0]*b[2] ;
 t += (ull) a[1]*b[5] ;
 t += (ull) a[2]*b[8] ;
 t = (t & MODM31) + (t>>31); 
 r[2] = (t & MODM31) + (t>>31);
 
 t = (ull) a[3]*b[0] ;
 t += (ull) a[4]*b[3] ;
 t += (ull) a[5]*b[6] ;
 t = (t & MODM31) + (t>>31); 
 r[3] = (t & MODM31) + (t>>31);
 
 t = (ull) a[3]*b[1] ;
 t += (ull) a[4]*b[4] ;
 t += (ull) a[5]*b[7] ;
 t = (t & MODM31) + (t>>31); 
 r[4] = (t & MODM31) + (t>>31);
 
 t = (ull) a[3]*b[2] ;
 t += (ull) a[4]*b[5] ;
 t += (ull) a[5]*b[8] ;
 t = (t & MODM31) + (t>>31); 
 r[5] = (t & MODM31) + (t>>31);
 
 t = (ull) a[6]*b[0] ;
 t += (ull) a[7]*b[3] ;
 t += (ull) a[8]*b[6] ;
 t = (t & MODM31) + (t>>31); 
 r[6] = (t & MODM31) + (t>>31);
 
 t = (ull) a[6]*b[1] ;
 t += (ull) a[7]*b[4] ;
 t += (ull) a[8]*b[7] ;
 t = (t & MODM31) + (t>>31);
 r[7] = (t & MODM31) + (t>>31);
 
 t = (ull) a[6]*b[2] ;
 t += (ull) a[7]*b[5] ;
 t += (ull) a[8]*b[8] ;
 t = (t & MODM31) + (t>>31);
 r[8] = (t & MODM31) + (t>>31);
 
}

 /**
  * @brief Modular Matrix exponentiation
  * @param[out] Resulting matrix res = base * base * ....... * base ( "expon" times ie. "base" to the power of "expon" )
  * @param[in] 3x3 matrix "base" , with all elements reduced modulo 0x7FFFFFFF
  * @param[in] Array "expon" , containing the exponent ( a positive integer with array[0] = Least Significant 32 bits ) to which "base" must be exponentiated .
  **/
void ModMatrixExpon(u32* res , const u32* base , const u32* expon)
{

 // Initialize result
 u32 r[9] = { 1,0,0, 0,1,0, 0,0,1 };
 
 u32 t[9] ;
 u32 b[9];
 Copy(b, base);
 
 int i = 0;
 ull y;
 
 int SizeOfExpon = 7 ; //sizeof(expon);
 
 while ( i < SizeOfExpon ) {
	 
 y = expon[i] ;
 y += (ull) expon[i + 1] << 32;
 
 while (y > 0) {

  // If y is odd, r = r * b
  if (y & 1) {
   MatrixMul(t, r, b);
   Copy(r, t);
   }
   
  // y must be even now
  
  y = y >> 1; // y = y/2
  
  // Change b to b*b
  MatrixMul(t, b, b);
  Copy(b, t);

  }
  
 i += 2;
 }
Copy(res, r);
}

