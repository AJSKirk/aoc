#include <stdio.h>
#include <string.h>
#include <math.h>

#include <CommonCrypto/CommonDigest.h> // MacOS library

int main()
{
    unsigned char hash[CC_MD5_DIGEST_LENGTH];
    const char input[] = "abcdef609043"; // Test case taken from 2015 Day 4
	char result[5];
	int dest = 0;

    CC_MD5_CTX context;
    CC_MD5_Init(&context);
    CC_MD5_Update(&context, input, (CC_LONG)strlen(input));
    CC_MD5_Final(hash, &context);

    for (int i=0; i<CC_MD5_DIGEST_LENGTH; ++i) {
		sprintf(&result[dest], "%.2x", hash[i]);
		dest += 2; // One hex digit takes two chars to represent
	}
	printf("%s\n", result);
    return 0;
}
