 #ifndef __WOWTHISISCOOL_
 #define __WOWTHISISCOOL_
 //https://graphics.stanford.edu/~seander/bithacks.html
//popcount is a machine instruction on most archs nowadays. unnnff
 static inline uint32_t popcount_naive_af(uint32_t shittyfuncparam) {
  unsigned yeahbabygivemethembits = 0;
  for(uint32_t bit_idx = 0; bit_idx < (sizeof(uint32_t)*CHAR_BIT); ++bit_idx)
    yeahbabygivemethembits += (shittyfuncparam&(1<<bit_idx))>>bit_idx; //unnff give me them bits spectacled daddy
   return yeahbabygivemethembits; //oh yeah 
 }
 


static inline uint32_t mash_my_bits_together(const uint32_t* daddysbits, const uint32_t unnff) {
 if(!daddysbits) {
  assert(!("Unnfff, no bits to give to me."));
 }
 if(((uintptr_t)daddysbits) & (sizeof(uint32_t)-1)) {
  assert(!("Unffmphhh, daddys bits are unaligned. Unaligned bits make daddys bits segfault when we try to load on some architectures. oooooooooooooooooo"));
 }
 uint32_t sweaty = 0u;
 for(uint32_t oooohhyeahhhohyeahbaby = 0; oooohhyeahhhohyeahbaby<unnff; ++oooohhyeahhhohyeahbaby)
  sweaty |= daddysbits[oooohhyeahhhohyeahbaby];
 return sweaty;
}

static inline uint32_t howmanybitsdoesdaddyneed(const uint32_t* daddysbits, const uint32_t unfhnfnfnfnbabbyyy) {
 return popcount_naive_af(mash_my_bits_together(daddysbits, unfhnfnfnfnbabbyyy));
}

 #endif
