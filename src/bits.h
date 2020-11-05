#ifndef FBS_BITS_H_
#define FBS_BITS_H_

namespace fbs {
// Inline overloads for the builtins

constexpr inline int ffs(unsigned int x) {
	return __builtin_ffs(x);
}
constexpr inline int ffs(unsigned long x) {
	return __builtin_ffsl(x);
}
constexpr inline int ffs(unsigned long long x) {
	return __builtin_ffsll(x);
}

constexpr int clz(unsigned int x) {
	return __builtin_clz(x);
}
constexpr int clz(unsigned long x) {
	return __builtin_clzl(x);
}
constexpr int clz(unsigned long long x) {
	return __builtin_clzll(x);
}

constexpr int ctz(unsigned int x) {
	return __builtin_ctz(x);
}
constexpr int ctz(unsigned long x) {
	return __builtin_ctzl(x);
}
constexpr int ctz(unsigned long long x) {
	return __builtin_ctzll(x);
}

} // namespace fbs

#endif /* FBS_BITS_H_ */
