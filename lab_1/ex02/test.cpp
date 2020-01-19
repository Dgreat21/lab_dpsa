#include "list.h"
#include <stdio.h>

int main(void) {
	List	list_1(2);
	List	list_2;
	List	list_3;

	list_1[(u32_t)0]->polis_id = 1;
	//set pid
	list_1[1]->polis_id = 2;
	//set pid

	list_1.push_back(new List_Node(3,0, 20200101));
	list_1.push_back(new List_Node(4,0, 19700101));
	list_1.push_back(new List_Node(5,0, 20190219));
	list_1.push_back(new List_Node(11,0, 20210509));
	list_1.push_back(new List_Node(12,0, 20200101));
	list_1.push_back(new List_Node(13,0, 10000101));
	list_1.push_back(new List_Node(21,0, 19421225));
	list_1.push_back(new List_Node(22,0, 19421225));
	list_1.push_back(new List_Node(23,0, 19421225));
	list_1.push_back(new List_Node(31,0, 19421225));
	list_1.push_back(new List_Node(32,0, 19421225));

	list_2 = list_1.sublist([](const List_Node &node){
		if (node.polis_id < 10 || node.polis_id > 30)
			return (true);
		return (false);
	});

	list_3 = list_1.sublist_cut([](const List_Node &node){
		if (node.polis_id > 10 && node.polis_id < 20)
			return (true);
		return (false);
	});

	list_3.push_front(new List_Node(101, 0, 20121212),
		[](const List_Node &n) {
			if (n.polis_id == 12)
				return (true);
			return (false);
		});
	list_3.push_back(new List_Node(14, 0, 20121212));
	list_3.push_back(new List_Node(15, 0, 20121212));

	list_1.print("l1_new");
	list_2.print("l2_cut");
	list_3.print("l3_sub");
	list_1.empty();
	list_2.empty();
	list_3.empty();
}