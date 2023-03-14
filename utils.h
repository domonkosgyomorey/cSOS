#ifdef UTILS_H

void memncpy(char *src, char *dst, int nbytes){
	for(int i = 0; i < nbytes; ++i){
		*(dst+i) = *(src+i);
	}
}

#endif // UTILS_H