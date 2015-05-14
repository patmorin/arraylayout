#include <cstdint>

// http://xorshift.di.unimi.it/xorshift128plus.c

struct xs_gen_base {
        uint64_t s[2];

        xs_gen_base()
        {
                /* Random numbers. */
                s[0] = 15028999435905310454ULL;
                s[1] = 16708911996216745849ULL;
        }

        xs_gen_base(uint64_t a, uint64_t b)
        {
                s[0] = a;
                s[1] = b;
                gen();
        }

        uint64_t gen()
        {
                uint64_t ret = s[1];
                uint64_t s1 = s[0];
                const uint64_t s0 = s[1];

                s[0] = s0;
                s1 ^= s1 << 23;
                s1 = (s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26)) + s0;

                s[1] = s1;
                return ret;
        }
};

struct xs_gen_int : public xs_gen_base
{
        xs_gen_int() {}

        xs_gen_int(uint64_t a, uint64_t b)
                : xs_gen_base(a, b)
        {}

        uint64_t operator()(void)
        {
                return gen();
        }

        uint64_t operator()(uint64_t limit)
        {
                unsigned __int128 rnd = gen();
                rnd *= limit;

                return rnd >> 64;
        }
};

struct xs_gen_real : public xs_gen_base
{
        xs_gen_real() {}

        xs_gen_real(uint64_t a, uint64_t b)
                : xs_gen_base(a, b)
        {}

        double operator()()
        {
                return gen() * 5.421010862427522e-20;
        }

        template <typename T>
        T operator()(T limit)
        {
                return limit * (gen() * (T)5.421010862427522e-20);
        }
};
