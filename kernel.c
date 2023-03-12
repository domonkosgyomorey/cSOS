void entry(){

}

void main(){
	char* video_memory = (char*)0xb8000;
	*(video_memory+0) = 'c';
	*(video_memory+2) = 'S';
	*(video_memory+4) = 'O';
	*(video_memory+6) = 'S';

}