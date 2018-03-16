int main()
{
	char a[1024*2014];
	unsigned index=0;
	while(1)
	{
		a[index++]=0;
		if(index == 1024*1024)
			break;	
	}
}
