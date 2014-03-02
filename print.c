#define VIDEO_BUFF_BASE	(0xb8000)
#define VIDEO_BUFF_END	(0xb8000 + 80 * 24 * 2)

void putc_k(char c){
	static unsigned short* index = (unsigned short*)VIDEO_BUFF_BASE;
	if(c == '\n')
		//index = ((((unsigned int)(index) - VIDEO_BUFF_BASE) / 160) + 1) * 160 + VIDEO_BUFF_BASE;
		index +=80;
	else
		*(index++) = 0x0c00 | c;
	if(index >= (unsigned short*)VIDEO_BUFF_END)
		index = (unsigned short*)VIDEO_BUFF_BASE;
}

void puts_k(char* str){
	while(*str)
		putc_k(*str++);
	putc_k('\n');
}

void ltox(unsigned int value,char* str){
	int i = 0;
	char tab[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(i = 0;i < 8;i++){
		str[9-i] = tab[value & 0xf];
		value >>= 4;
	}
	str[0] = '0';
	str[1] = 'x';
	str[10] = '\0';
}

void putl_k(int value){
	char buff[12];
	ltox(value,buff);
	puts_k(buff);
}
