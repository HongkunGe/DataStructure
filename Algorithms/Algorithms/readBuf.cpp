/*
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

1. The read function will only be called once for each test case.
2. The read function may be called multiple times.

////////////////////////////////////////////////////////////////////////
//1.  The read function will only be called once for each test case.
////////////////////////////////////////////////////////////////////////


/**
* @param buf Destination buffer
* @param n   Maximum number of characters to read
* @return    The number of characters read
*/

/*
testCase:
"ab",1 => min(res, n);  "",0 => TLE, add batch break;
*/

/*

// Forward declaration of the read4 API.

int read4(char *buf);
int read(char *buf, int n) {
	int res = 0, batch = 0;
	while (res < n) {
		batch = read4(buf + res);
		res += batch;
		if (batch == 0)
			break;
	}
	return min(res, n);
}

*/

////////////////////////////////////////////////////////////////////////
//2. The read function may be called multiple times.
////////////////////////////////////////////////////////////////////////

// TODO: Forward declaration of the read4 API.
int read4(char *buf)
{
	return 0;
}

class Solution {
	char *buffer4;
	int buf4Ptr, buf4Len;
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	Solution() {
		buffer4 = new char[4];
		buf4Ptr = buf4Len = 4;
	}
	int read(char *buf, int n) {
		int ptr = 0;
		while (ptr < n) {
			// only when buf4Ptr is 0, we read new data, which means buf4Ptr 
			// is changed from 4 to 0 or initialized. buffer4 is consumed by buf.
			if (buf4Ptr == 0)
				buf4Len = read4(buffer4);
			// read nothing.
			if (buf4Len == 0)
				break;
			// consume one whole buffer4 or part of buffer4. 
			while (ptr < n && buf4Ptr < buf4Len)
				buf[ptr++] = buffer4[buf4Ptr++];
			if (buf4Ptr == buf4Len)
				buf4Ptr = 0;
		}
		return ptr;
	}
};