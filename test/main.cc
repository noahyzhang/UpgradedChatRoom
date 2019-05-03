#include<unistd.h>
#include"Window.hpp"


int main()
{
	Window w;
	w.DrawHeader();
	w.DrawOutput();
	w.DrawOnline();
	w.DrawInput();

	std::string message;
	while(1)
	{
		w.GetStringFromInput(message);
		w.PutMessageToOutput(message);
	}

	//w.Welcome();
	return 0;
}
