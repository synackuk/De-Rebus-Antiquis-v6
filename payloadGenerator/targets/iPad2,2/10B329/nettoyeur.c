#include <stdint.h>

#define BASE_ADDRESS 0x0

void _start() {
	*(uint32_t*)(BASE_ADDRESS + 0x43394) = 0x9ff372ae; /* 0x8402a340 -> 0x9ff372ae */
	*(uint32_t*)(BASE_ADDRESS + 0x43398) = 0x80000000; /* 0x84002ef5 -> 0x80000000 */
	*(uint32_t*)(BASE_ADDRESS + 0x46198) = 0xe000000; /* 0xe000011 -> 0xe000000 */
	*(uint32_t*)(BASE_ADDRESS + 0x461a0) = 0xe000001; /* 0xe00000a -> 0xe000001 */
	*(uint32_t*)(BASE_ADDRESS + 0x46320) = 0xffffffff; /* 0xe28 -> 0xffffffff */
	*(uint32_t*)(BASE_ADDRESS + 0x4633c) = 0x0; /* 0x9ff52a60 -> 0x0 */
	*(uint32_t*)(BASE_ADDRESS + 0x46340) = 0xffffffff; /* 0x2 -> 0xffffffff */
	*(uint32_t*)(BASE_ADDRESS + 0x46344) = 0x0; /* 0x1 -> 0x0 */
	*(uint32_t*)(BASE_ADDRESS + 0x4634c) = 0x0; /* 0x9ff555c0 -> 0x0 */
	*(uint32_t*)(BASE_ADDRESS + 0x46350) = 0x1; /* 0x10 -> 0x1 */
	*(uint32_t*)(BASE_ADDRESS + 0x46354) = 0x9ff46354; /* 0x9ffcc740 -> 0x9ff46354 */
	*(uint32_t*)(BASE_ADDRESS + 0x46358) = 0x9ff46354; /* 0x9ff4cac0 -> 0x9ff46354 */
	*(uint32_t*)(BASE_ADDRESS + 0x4638c) = 0x9ff4638c; /* 0x9ff577c0 -> 0x9ff4638c */
	*(uint32_t*)(BASE_ADDRESS + 0x46390) = 0x9ff4638c; /* 0x9ff57240 -> 0x9ff4638c */
	*(uint32_t*)(BASE_ADDRESS + 0x46394) = 0x9ff46394; /* 0x9ff557c0 -> 0x9ff46394 */
	*(uint32_t*)(BASE_ADDRESS + 0x46398) = 0x9ff46394; /* 0x9ff557c0 -> 0x9ff46394 */
	*(uint32_t*)(BASE_ADDRESS + 0x46470) = 0xffffffff; /* 0x9ff4ca74 -> 0xffffffff */
	*(uint32_t*)(BASE_ADDRESS + 0x46474) = 0xffffffff; /* 0xaa58c -> 0xffffffff */
	*(uint32_t*)(BASE_ADDRESS + 0x46478) = 0x0; /* 0x1 -> 0x0 */
	*(uint32_t*)(BASE_ADDRESS + 0x46490) = 0x9ff464b0; /* 0x9ffb5d80 -> 0x9ff464b0 */
	*(uint32_t*)(BASE_ADDRESS + 0x464a0) = 0x9ff464a0; /* 0x9ffc9e2c -> 0x9ff464a0 */
	*(uint32_t*)(BASE_ADDRESS + 0x464a4) = 0x9ff464a0; /* 0x9ffc9e2c -> 0x9ff464a0 */
	*(uint32_t*)(BASE_ADDRESS + 0x464a8) = 0x9ff464a8; /* 0x9ff4ac14 -> 0x9ff464a8 */
	*(uint32_t*)(BASE_ADDRESS + 0x464ac) = 0x9ff464a8; /* 0x9ffcdaa4 -> 0x9ff464a8 */
	*(uint32_t*)(BASE_ADDRESS + 0x464c4) = 0x2; /* 0x5 -> 0x2 */
	for(uint32_t i = 0x464cc; i <= 0x46620; i += 4) {
		*(uint32_t*)(BASE_ADDRESS + i) = 0x0;
	}
	*(uint32_t*)(BASE_ADDRESS + 0x46650) = 0xffffffff; /* 0x9fff8000 -> 0xffffffff */
	*(uint32_t*)(BASE_ADDRESS + 0x46d20) = 0x4000; /* 0x5ac4000 -> 0x4000 */
	*(uint32_t*)(BASE_ADDRESS + 0x46d24) = 0x0; /* 0x1281 -> 0x0 */
	*(uint32_t*)(BASE_ADDRESS + 0x46d28) = 0x1000000; /* 0x1040302 -> 0x1000000 */
}