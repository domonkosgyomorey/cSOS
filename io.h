#ifdef IO_H

unsigned char io_byte_in(unsigned short port){
	unsigned char result;
	__asm__("in %%dx, %%al":"=a"(result):"d"(port));
	return result;
}

unsigned char io_byte_out(unsigned short port, unsigned short data){
	__asm__("out %%al, %%dx"::"a"(data),"d"(port));
}

#endif // IO_H