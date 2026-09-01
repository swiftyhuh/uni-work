#include "Song.h"
#include <crtdbg.h>
#include <iostream>

#include "DynmicArr.h"
#include "Repository.h"
#include "Services.h"

int main() {
	{
		Song song(
			"Ed Sheeran",
			"The Shape of You",
			Duration(3, 50),
			"https://youtube.com"
		);
		//std::cout << song.get_artist() << std::endl;
		//DynamicArr arr(1);
		//arr.addElem(1);
		//arr.addElem(2);
		//arr.addElem(3);
		//std::cout << arr.getSize();
		//DynamicArr arr2{ arr };
		//
		//DynamicArr arr3(1);
		//arr.addElem(4);
		//arr.addElem(5);
		//arr3 = arr2 = arr;
		////arr3.operator=(arr2.operator=(arr));

		//arr = arr;
		
		Repository repo{};
		repo.add(song);
		int s = repo.getSize();

		Services services{repo};
		std::cout << services.getSize() << std::endl;

		services.add("t", "a", 3, 40, "y");
		std::cout << services.getSize() << std::endl;

		std::cout << repo.getSize() << std::endl;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}