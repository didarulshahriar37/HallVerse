#include "Hasher.h"
#include <cstring>
#include <sstream>
#include <iomanip>
 
using namespace std;
Hasher::Hasher() : id("HASHER_001") {}

// Minimal SHA-256 implementation (public-domain style)
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned long long uint64;

static inline uint32 rotr(uint32 x, uint32 n) { return (x >> n) | (x << (32 - n)); }

static const uint32 k[64] = {
    0x428a2f98ul,0x71374491ul,0xb5c0fbcful,0xe9b5dba5ul,0x3956c25bul,0x59f111f1ul,0x923f82a4ul,0xab1c5ed5ul,
    0xd807aa98ul,0x12835b01ul,0x243185beul,0x550c7dc3ul,0x72be5d74ul,0x80deb1feul,0x9bdc06a7ul,0xc19bf174ul,
    0xe49b69c1ul,0xefbe4786ul,0x0fc19dc6ul,0x240ca1ccul,0x2de92c6ful,0x4a7484aaul,0x5cb0a9dcul,0x76f988daul,
    0x983e5152ul,0xa831c66dul,0xb00327c8ul,0xbf597fc7ul,0xc6e00bf3ul,0xd5a79147ul,0x06ca6351ul,0x14292967ul,
    0x27b70a85ul,0x2e1b2138ul,0x4d2c6dfcul,0x53380d13ul,0x650a7354ul,0x766a0abbul,0x81c2c92eul,0x92722c85ul,
    0xa2bfe8a1ul,0xa81a664bul,0xc24b8b70ul,0xc76c51a3ul,0xd192e819ul,0xd6990624ul,0xf40e3585ul,0x106aa070ul,
    0x19a4c116ul,0x1e376c08ul,0x2748774cul,0x34b0bcb5ul,0x391c0cb3ul,0x4ed8aa4aul,0x5b9cca4ful,0x682e6ff3ul,
    0x748f82eeul,0x78a5636ful,0x84c87814ul,0x8cc70208ul,0x90befffaul,0xa4506cebul,0xbef9a3f7ul,0xc67178f2ul
};

static void sha256(const uint8* data, size_t len, uint8* out) {
    uint64 bitlen = (uint64)len * 8ULL;
    // initialize state
    uint32 h[8] = {
        0x6a09e667ul,0xbb67ae85ul,0x3c6ef372ul,0xa54ff53aul,
        0x510e527ful,0x9b05688cul,0x1f83d9abul,0x5be0cd19ul
    };

    // process each 512-bit chunk
    size_t rem = len;
    size_t pos = 0;
    uint8 chunk[64];

    while (rem >= 64) {
        const uint8* p = data + pos;
        uint32 w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = (uint32)p[i*4] << 24 | (uint32)p[i*4+1] << 16 | (uint32)p[i*4+2] << 8 | (uint32)p[i*4+3];
        }
        for (int i = 16; i < 64; ++i) {
            uint32 s0 = rotr(w[i-15],7) ^ rotr(w[i-15],18) ^ (w[i-15] >> 3);
            uint32 s1 = rotr(w[i-2],17) ^ rotr(w[i-2],19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }

        uint32 a=h[0], b=h[1], c=h[2], d=h[3], e=h[4], f=h[5], g=h[6], h0=h[7];
        for (int i = 0; i < 64; ++i) {
            uint32 S1 = rotr(e,6) ^ rotr(e,11) ^ rotr(e,25);
            uint32 ch = (e & f) ^ ((~e) & g);
            uint32 temp1 = h0 + S1 + ch + k[i] + w[i];
            uint32 S0 = rotr(a,2) ^ rotr(a,13) ^ rotr(a,22);
            uint32 maj = (a & b) ^ (a & c) ^ (b & c);
            uint32 temp2 = S0 + maj;

            h0 = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += h0;

        pos += 64;
        rem -= 64;
    }

    // copy remaining
    size_t i = 0;
    for (; i < rem; ++i) chunk[i] = data[pos + i];

    // append 0x80
    chunk[i++] = 0x80;

    if (i > 56) {
        // pad with zeros and process
        while (i < 64) chunk[i++] = 0x00;
        // process this chunk
        uint32 w[64];
        for (int t = 0; t < 16; ++t) {
            w[t] = (uint32)chunk[t*4] << 24 | (uint32)chunk[t*4+1] << 16 | (uint32)chunk[t*4+2] << 8 | (uint32)chunk[t*4+3];
        }
        for (int t = 16; t < 64; ++t) {
            uint32 s0 = rotr(w[t-15],7) ^ rotr(w[t-15],18) ^ (w[t-15] >> 3);
            uint32 s1 = rotr(w[t-2],17) ^ rotr(w[t-2],19) ^ (w[t-2] >> 10);
            w[t] = w[t-16] + s0 + w[t-7] + s1;
        }
        uint32 a=h[0], b=h[1], c=h[2], d=h[3], e=h[4], f=h[5], g=h[6], h0=h[7];
        for (int t = 0; t < 64; ++t) {
            uint32 S1 = rotr(e,6) ^ rotr(e,11) ^ rotr(e,25);
            uint32 ch = (e & f) ^ ((~e) & g);
            uint32 temp1 = h0 + S1 + ch + k[t] + w[t];
            uint32 S0 = rotr(a,2) ^ rotr(a,13) ^ rotr(a,22);
            uint32 maj = (a & b) ^ (a & c) ^ (b & c);
            uint32 temp2 = S0 + maj;

            h0 = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += h0;

        // new chunk
        i = 0;
    }

    // pad zeros until 56
    while (i < 56) chunk[i++] = 0x00;

    // append length in bits
    chunk[56] = (uint8)(bitlen >> 56);
    chunk[57] = (uint8)(bitlen >> 48);
    chunk[58] = (uint8)(bitlen >> 40);
    chunk[59] = (uint8)(bitlen >> 32);
    chunk[60] = (uint8)(bitlen >> 24);
    chunk[61] = (uint8)(bitlen >> 16);
    chunk[62] = (uint8)(bitlen >> 8);
    chunk[63] = (uint8)(bitlen);

    // process final chunk
    uint32 w2[64];
    for (int t = 0; t < 16; ++t) {
        w2[t] = (uint32)chunk[t*4] << 24 | (uint32)chunk[t*4+1] << 16 | (uint32)chunk[t*4+2] << 8 | (uint32)chunk[t*4+3];
    }
    for (int t = 16; t < 64; ++t) {
        uint32 s0 = rotr(w2[t-15],7) ^ rotr(w2[t-15],18) ^ (w2[t-15] >> 3);
        uint32 s1 = rotr(w2[t-2],17) ^ rotr(w2[t-2],19) ^ (w2[t-2] >> 10);
        w2[t] = w2[t-16] + s0 + w2[t-7] + s1;
    }
    uint32 a2=h[0], b2=h[1], c2=h[2], d2=h[3], e2=h[4], f2=h[5], g2=h[6], h2=h[7];
    for (int t = 0; t < 64; ++t) {
        uint32 S1 = rotr(e2,6) ^ rotr(e2,11) ^ rotr(e2,25);
        uint32 ch = (e2 & f2) ^ ((~e2) & g2);
        uint32 temp1 = h2 + S1 + ch + k[t] + w2[t];
        uint32 S0 = rotr(a2,2) ^ rotr(a2,13) ^ rotr(a2,22);
        uint32 maj = (a2 & b2) ^ (a2 & c2) ^ (b2 & c2);
        uint32 temp2 = S0 + maj;

        h2 = g2;
        g2 = f2;
        f2 = e2;
        e2 = d2 + temp1;
        d2 = c2;
        c2 = b2;
        b2 = a2;
        a2 = temp1 + temp2;
    }
    h[0] += a2; h[1] += b2; h[2] += c2; h[3] += d2;
    h[4] += e2; h[5] += f2; h[6] += g2; h[7] += h2;

    // produce output
    for (int t = 0; t < 8; ++t) {
        out[t*4]   = (uint8)(h[t] >> 24);
        out[t*4+1] = (uint8)(h[t] >> 16);
        out[t*4+2] = (uint8)(h[t] >> 8);
        out[t*4+3] = (uint8)(h[t]);
    }
}

std::string Hasher::hash(const std::string& input) {
    uint8 digest[32];
    sha256(reinterpret_cast<const uint8*>(input.data()), input.size(), digest);
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 32; ++i) ss << std::setw(2) << (int)digest[i];
    return ss.str();
}