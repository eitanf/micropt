//By Monica Moniot
#include "converter.h"

using uint32 = uint32_t;

void convert_all(unsigned size, char* lines[], uint32 nums[]) {
	char** cur_str = lines;
	uint32* cur_num = nums;
	uint32* last_num = nums + size;
	while(cur_num + 3 < last_num) {
		char* cur_char0 = *cur_str;
		char byte0 = *cur_char0;
		uint32 n0 = (byte0 - '0');
		char* cur_char1 = *(cur_str + 1);
		char byte1 = *cur_char1;
		uint32 n1 = (byte1 - '0');
		char* cur_char2 = *(cur_str + 2);
		char byte2 = *cur_char2;
		uint32 n2 = (byte2 - '0');
		char* cur_char3 = *(cur_str + 3);
		char byte3 = *cur_char3;
		uint32 n3 = (byte3 - '0');

		cur_char0 += 1;
		byte0 = *cur_char0;
		n0 = 10*n0 + (byte0 - '0');
		cur_char0 += 1;
		byte0 = *cur_char0;
		n0 = 10*n0 + (byte0 - '0');
		cur_char0 += 1;
		byte0 = *cur_char0;
		cur_char1 += 1;
		byte1 = *cur_char1;
		n1 = 10*n1 + (byte1 - '0');
		cur_char1 += 1;
		byte1 = *cur_char1;
		n1 = 10*n1 + (byte1 - '0');
		cur_char1 += 1;
		byte1 = *cur_char1;
		cur_char2 += 1;
		byte2 = *cur_char2;
		n2 = 10*n2 + (byte2 - '0');
		cur_char2 += 1;
		byte2 = *cur_char2;
		n2 = 10*n2 + (byte2 - '0');
		cur_char2 += 1;
		byte2 = *cur_char2;
		cur_char3 += 1;
		byte3 = *cur_char3;
		n3 = 10*n3 + (byte3 - '0');
		cur_char3 += 1;
		byte3 = *cur_char3;
		n3 = 10*n3 + (byte3 - '0');
		cur_char3 += 1;
		byte3 = *cur_char3;

		if(byte0 != 0) {
			n0 = 10*n0 + (byte0 - '0');
			cur_char0 += 1;
			byte0 = *cur_char0;
			if(byte0 != 0) {
				n0 = 10*n0 + (byte0 - '0');
			}
		}
		if(byte1 != 0) {
			n1 = 10*n1 + (byte1 - '0');
			cur_char1 += 1;
			byte1 = *cur_char1;
			if(byte1 != 0) {
				n1 = 10*n1 + (byte1 - '0');
			}
		}
		if(byte2 != 0) {
			n2 = 10*n2 + (byte2 - '0');
			cur_char2 += 1;
			byte2 = *cur_char2;
			if(byte2 != 0) {
				n2 = 10*n2 + (byte2 - '0');
			}
		}
		if(byte3 != 0) {
			n3 = 10*n3 + (byte3 - '0');
			cur_char3 += 1;
			byte3 = *cur_char3;
			if(byte3 != 0) {
				n3 = 10*n3 + (byte3 - '0');
			}
		}

		*cur_num = n0;
		*(cur_num + 1) = n1;
		*(cur_num + 2) = n2;
		*(cur_num + 3) = n3;
		cur_num += 4;
		cur_str += 4;
	}
	while(cur_num != last_num) {
		char* cur_char = *cur_str;
		char byte = *cur_char;
		uint32 n = (byte - '0');
		cur_char += 1;
		byte = *cur_char;
		n = 10*n + (byte - '0');
		cur_char += 1;
		byte = *cur_char;
		n = 10*n + (byte - '0');
		cur_char += 1;
		byte = *cur_char;
		if(byte != 0) {
			n = 10*n + (byte - '0');
			cur_char += 1;
			byte = *cur_char;
			if(byte != 0) {
				n = 10*n + (byte - '0');
			}
		}
		*cur_num = n;
		cur_num += 1;
		cur_str += 1;
	}
}
