 #ifndef __WOWTHISISCOOL_
 #define __WOWTHISISCOOL_
 
 static uint32_t popcount_naive_af(uint32_t shittyfuncparam) {
  unsigned yeahbabygivemethembits = 0;
  for(uint32_t bit_idx = 0; bit_idx < (sizeof(uint32_t)*CHAR_BIT); ++bit_idx)
    yeahbabygivemethembits += (shittyfuncparam&(1<<bit_idx))>>bit_idx; //unnff give me them bits spectacled daddy
   return yeahbabygivemethembits; //oh yeah 
 }
 
 
 #endif
