import "io"

manifest {
	link_data = 0,
	link_next = 1,
	link_size = 2,

	list_head = 0,
	list_tail = 1,
	list_size = 2
}

manifest {
	cFreePFree = 3;
	cFreeNFree = 2;
	//cFreeSize1 = 1;
	freeCode = 0x12121212; 
	manFreeSize = 5; //Mandatory size for a free chunk, includes zero

	cUseData = 2;
	useCode = 0x98989898;
	manUseSize = 3; //Mandatory size for a in use chunk, includes zero

	chunkSize = 1;
	chunkCode = 0
}

static {
	heap, firstFree = nil, endFF = -1
}

static {
	links = 0
}

let printHeap(size) be {
	for i = 0 to (size - 1) do {
		out("%x| heap[%x]: %x \n", @(heap ! i), i, heap ! i);
	}
	out("\n");
}

let setHeap(h, size) be {
	heap := h;

	//from the bottom of the heap
	heap ! chunkCode := freeCode;
	heap ! chunkSize := size; 

	heap ! cFreeNFree := endFF; //no next
	firstFree := 0;//points to whole heap
	heap ! cFreePFree := endFF; //technically no previous

	heap ! (size - chunkSize) := size; 
}

let findFree(size, currChunk) be {
	let nextChunk, currChunkSize = heap ! (chunkSize + currChunk);

	//in the rare case it bumps into an in use
	if (heap ! currChunk) = useCode then {
		nextChunk := currChunk + currChunkSize;
		findFree(size, nextChunk)
	}

	//finds a chunk that is free
	if (heap ! currChunk) = freeCode then {
		if currChunkSize = size then {
			//size of current free chunk is what is needed
			resultis currChunk;
		}
		if (currChunkSize - size) >= manFreeSize then {
			//enough space to have a free chunk if portion is removed for use
			resultis currChunk;
		}
		if (currChunkSize - size) < manFreeSize then {
			//not enough space when in use portion is removed therfore move on to next chunk
			nextChunk := heap ! (currChunk + cFreeNFree);
			findFree(size, nextChunk);
		}
	}
}

let removeFromFL(chunk) be {
	let nextChunk, prevChunk;
	if (heap ! chunk) = useCode then {
		out("Asked to remove a used chunk from free list\n");
		return; 
	}

	nextChunk := heap ! (chunk + cFreeNFree);
	prevChunk := heap ! (chunk + cFreePFree);
	if nextChunk = endFF then {
		heap ! (prevChunk + cFreeNFree) := endFF;
	}
	if not(nextChunk = endFF) then {
		heap ! (nextChunk + cFreePFree) := heap ! (chunk + cFreePFree);
	}
	if prevChunk = endFF then {
		heap ! (nextChunk + cFreePFree) := endFF;
		firstFree := nextChunk;
	}
	if not(prevChunk = endFF) then{
		heap ! (prevChunk + cFreeNFree) := heap ! (chunk + cFreeNFree);
	} 

}

let new_vec(size) be {
	let adjustedSize, freeSize, freeChunk, freeLink, useChunk;

	if size = 0 then {
		out("there is vec of size 0, removed from heap");
		return;
	}

	//size is adjusted to find enough space for data required, size, and 
	//the mandatory three lines
	adjustedSize := size + manUseSize;
	if size = 1 then {
		adjustedSize := adjustedSize + 1;
	}
	
	freeChunk := findfree(adjustedSize, firstFree);
	freeSize := heap ! (freeChunk + chunkSize);
	useChunk := freeChunk;

	//check the status of free chunk 
	if freeSize = adjustedSize then {
		//Just enough for needed data therfore need to remove free from list
		removeFromFL(freeChunk);
	}
	if freeSize > adjustedSize then {
		//since have enough size for free on top, simply push up the next and prev free
		heap ! (freeChunk + adjustedSize + cFreeNFree) := heap ! (freeChunk + cFreeNFree); 
		heap ! (freeChunk + adjustedSize + cFreePFree) := heap ! (freeChunk + cFreePFree);

		//set up leftover free chunk
		freeChunk := freeChunk + adjustedSize;
		freeSize := freeSize - adjustedSize;
		heap ! freeChunk := freeCode;
		heap ! (freeChunk + chunkSize) := freeSize; 
		heap ! (freeChunk + freeSize - chunkSize) := freeSize; 

		if (firstFree = useChunk) then {
			firstFree := freeChunk;
		}
	}
		
	//set up in use chunk
	heap ! useChunk := useCode;
	heap ! (useChunk + chunkSize) := adjustedSize; 
	heap ! (useChunk + adjustedSize - chunkSize) := adjustedSize;

	//give access to the data portion, not the code
	useChunk := useChunk + cUseData; 

	resultis @(heap ! useChunk);
}

//make sure that chunk2 is on top
let mergeAndFree(chunk1, chunk2, sel) be {
	let chunk2Size, chunk1Size, totalSize, transfer;

	chunk2Size := heap ! (chunk2 + chunkSize);
	chunk1Size := heap ! (chunk1 + chunkSize);
	totalSize := chunk2Size + chunk1Size;

	if sel = 0 then { //remove top and merge with bottom
		removeFromFL(chunk2);
		heap ! (chunk1 + chunkSize) := totalSize;
		heap ! (chunk1 + totalSize - chunkSize) := totalSize;
	}
	
	if sel = 1 then { //remove bottom and merge with top
		removeFromFL(chunk1);

		//transfer pointers from top to bottom since bottom removed
		transfer := heap ! (chunk2 + cFreeNFree);
		if not(transfer = endFF) then
			heap ! (transfer + cFreePFree) := chunk1;

		transfer := heap ! (chunk2 + cFreePFree);

		if not(transfer = endFF) then
			heap ! (transfer + cFreeNFree) := chunk1;

		heap ! (chunk1 + cFreeNFree) := heap ! (chunk2 + cFreeNFree);
		heap ! (chunk1 + cFreePFree) := heap ! (chunk2 + cFreePFree);

		heap ! (chunk1 + chunkSize) := totalSize;
		heap ! (chunk2 + chunk2Size - chunkSize) := totalSize;
	}

	return;
}

let free_vec(chunk) be {
	let heapNum, currChunkSize, currChunk; 

	//find the number of the chunk on the heap
	heapNum := @(chunk ! 0) - @(heap ! 0) - cUseData;

	heap ! heapNum := freeCode;

	// add chunk to free chunk list
	heap ! (firstFree + cFreePFree) := heapNum;
	heap ! (heapNum + cFreeNFree) := firstFree;
	heap ! (heapNum + cFreePFree) := endFF;
	firstFree := heapNum;

	//merge possible chunks:

	//first check the chunk on top
	currChunkSize := heap ! (heapNum + chunkSize);
	currChunk := heapNum + currChunkSize;
	if (heap ! currChunk) = freeCode then {
		//merge
		mergeAndFree(heapNum, currChunk, 1);
	}

	//current now checks at the bottom
	currChunkSize := heap ! (heapNum - chunkSize);
	currChunk := heapNum - currChunkSize;
	if (heap ! currChunk) = freeCode then {
		//merge
		mergeandFree(currChunk, heapNum, 0);
	}

	return;
}

////////////////////////////
/* LINKED LIST CODE BELOW */

let new_link(data) be {
	let current = new_vec(link_size);
	current ! link_data := data;
	current ! link_next := nil;
	resultis current;
}

let add_to_list(link, list) be {
	test list ! list_head = list ! list_tail /\ list ! list_head = nil then {
		list ! list_head := link;
		list ! list_tail := link;
		links +:= 1;
	} else {
		list ! list_tail ! link_next := link;
		list ! list_tail := link;
		links +:= 1;
	}
}

let print_data(data) be {
	let i = 0;
	while byte i of data /= 0 do {
		out("%c", byte i of data);
		i +:= 1;
	}
}

let print_link(ptr) be {
	out("Link = %x  Data = %x = %s", ptr, ptr ! link_data, ptr ! link_data);
	//print_data(ptr ! link_data);
}

let print_list(list) be {
	let ptr = list ! list_head;
	let i;
	out("Printing linked list. . .\n");
	while ptr /= nil do {
		out("->");
		print_link(ptr);
		ptr := ptr ! link_next;
	}
	out("\n");
}

let strcmp(str1, str2) be {
	let i = 0;
	let char1 = byte i of str1;
	let char2 = byte i of str2;
	while (char1 /= 0 /\ char2 /= 0) /\ (char1 = char2) do {
		i +:= 1;
		char1 := byte i of str1;
		char2 := byte i of str2;
	}
	test char1 = char2 then
		resultis 0
	else
		resultis (char1 - char2);
}

let strdup(str, size) be {
	let count;
	let newstr = new_vec(size);
	for count = 0 to size do {
		byte count of newstr := byte count of str;
	}
	resultis newstr;
}

let instring() be {
	let currstr = vec(100);
	let i = 0;
	let currch;
	let string;
	let size;
	while true do {
		currch := inch();
		if currch = '\n' then 
			break;
		byte i of currstr := currch;
		i := i + 1;
	}
	byte i of currstr := 0;
	string := strdup(currstr, i);
	free_vec(currstr);
	resultis string;
}

let delete_link(input, list) be {
	let currlink = list ! list_head;
	let templink = currlink;
	if strcmp((currlink ! link_data), input) = 0 then {
		list ! list_head := currlink ! link_next;
		free_vec(templink);
		links -:= 1;
		resultis 0;
	}
	while currlink /= nil do {
		test strcmp((currlink ! link_next ! link_data), input) = 0 then {
			templink := currlink;
			currlink ! link_next := currlink ! link_next ! link_next;
			if currlink ! link_next = nil then
				list ! list_tail := currlink;
			free_vec(templink);
			links -:= 1;
			resultis 0;
		} else test (currlink ! link_next) = nil then {
			resultis -1;
		} else {
			currlink := currlink ! link_next;
		}
	}
	resultis -1;
}

let start() be {
	let input, tmp;
	let linkedlist, mylink;
	let theheap = vec(10000);
	setHeap(theheap, 10000);
	//init(heap, 10000);

	out("Please enter a string and then click enter.\n");
	out("To delete an entry, please only type DELETE in all caps.\n");
	out("To view the linked list as it currently is, please only type ALL in all caps.\n");
	out("To end the program, please only type END in all caps.\n");
	while true do {
		input := instring();
		mylink := new_link(input);
		if strcmp(input, "END") = 0 then
			break;
		if strcmp(input, "DELETE") = 0 then {
			out("Which entry do you want to delete: ");
			input := instring();
			out("Deleting ");
			print_data(input);
			out(" . . .\n");
			tmp := delete_link(input, linkedlist);
			test tmp = 0 then {
				out("Successfully deleted ");
				print_data(input);
				out(".\nContinuing the program. . .\n");
			} else {
				out("Could not find entry ");
				print_data(input);
				out(" to delete.\nContinuing the program. . .\n");
			}
			loop;
		}
		if strcmp(input, "ALL") = 0 then {
			print_list(linkedlist);
			loop;
		}
		add_to_list(mylink, linkedlist);
		out("Link = %x, str = %x = %s\n", mylink, mylink ! link_data, mylink ! link_data);
	}
	print_list(linkedlist);
}
