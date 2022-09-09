#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 20

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// enums
typedef enum Boolean
{ false, true } bool;

// club member structs
typedef struct member
{
	int id;
	char name[50 + 1];
	int age;
	int phoneNumber;
	int postCode;
	bool active;
	char debugInfo[100 + 1];
	
} Member;

// constants
const Member EMPTY_MEMBER;

// initialize hashtable array
void initialize(Member *members, int n)
{
	// variables
	int i;
	
	// initialize all elements in the array
	for (i = 0; i < n; i++)
	{
		members[i] = EMPTY_MEMBER;
		members[i].id = 0;
		members[i].active = false;
	}
}

// hash of x
int h(int x)
{
	return x % HASH_TABLE_SIZE;
}

// show the hash table with all the members
void showHashtableMap(Member *members, int n)
{
	// variables
	int i;
	
	// show all members with hash table
	for (i = 0; i < n; i++)
	{
		if (members[i].active)
		{
			printf("===========================================================================\n");
			printf("[%02d] ID: %d | Name: %s | age: %d | Phone Number: %d | Post Code: %d\n",
					i, members[i].id, members[i].name, members[i].age, members[i].phoneNumber, members[i].postCode);
			
			printf("\t> %s\n", members[i].debugInfo);
		}
		else if (members[i].active == false && members[i].id != 0)
		{
			printf("===========================================================================\n");
			printf("[%02d] (for recycling)\n", i);
		}
		else
		{
			printf("===========================================================================");
			printf("\n[%02d] (free)\n", i);
		}
	}
}

// add a new club member to the hash table
void newMember(Member *members, int n, int memberId, char *memberName, int memberAge, int memberPhoneNumber, int memberPostCode)
{
	// varaibles
	Member newMember;
	int hash;
	int i;
	int attempt = 0;	
	
	// add a new member
	newMember.id = memberId;
	strcpy(newMember.name, memberName);
	newMember.phoneNumber = memberPhoneNumber;
	newMember.postCode = memberPostCode;
	newMember.age = memberAge;
	newMember.active = true;
	
	// compute hash of members id
	hash = h(newMember.id);
	
	// linear probing // first element to be inserted is the hash element
	i = hash;
	
	// Find a open spot to save the member profile
	while (members[i].active && attempt < n)
	{
		// set teh new element index to test
		i = (i % n) + 1;
		
		// attempt must be less then n
		attempt++;
	}
	
	// number of attempts must be under n
	if (attempt == n)
	{
		printf("hash table is full, can't store more members");
		return;
	}
	
	// debug only
	sprintf(newMember.debugInfo, "h(x) = h(\"%d\") = %d; used index; %d; %d colisions.",
			newMember.id, hash, i, attempt);
			
	// save the player in the array
	members[i] = newMember;
}

// get index of the club member id position in the array
int searchMember(Member *members, int n, int memberId)
{
	//variables
	int hash;
	int i;
	int attempt = 0;
	
	// compute hash of x
	hash = h(memberId);
	
	// try to find the elemnt in the natural hash of x position
	i = hash;
	
	// find the club member beginning in the origina hash of x position
	while ((members[i].id != memberId && members[i].active) && attempt < n)
	{
		// set the new element index to test it in a circular array
		i = (i % n) + 1;
		
		// attempts must be less then n
		attempt++;
	}
	
	// number attempts must be less then n
	if (attempt == n)
		return -1;
		
	//return found position
	return i;	
}

// show club members
void showMembers(Member *members, int n)
{
	// varaibles
	int i;
	
	// show all players
	for(i = 0; i < n; i++)
	{
		if (members[i].active)
			printf("ID: %d | Name: %s | age: %d | Phone Number: %d | Post Code: %d\n\n",
					members[i].id, members[i].name, members[i].age, members[i].phoneNumber, members[i].postCode);
	}
}

// remove a club member
void removeMember(Member *members, int n, int memberId)
{
	// variables
	int index;
	
	// search the player
	index = searchMember(members, n, memberId);
	
	// special case when player does not exists
	if (index == -1)
	{
		printf("removing a not exisitng member\n");
		return;
	}
	
	// remove the player
	members[index].active = false;
}

// update the club member
void updateMember(Member *members, int n, int memberId, char *memberName, int memberAge, int memberPhoneNumber, int memberPostCode)
{
	// variables
	int indexId;
	
	indexId = searchMember(members, n, memberId);
	
	// special case when player does not exists
	if (indexId == -1)
	{
		printf("the member you're trying to update does not exist'\n");
		return;
	}
	
	// remove the player
	members[indexId].id = memberId;
	strcpy(members[indexId].name, memberName);
	members[indexId].age = memberAge;
	members[indexId].phoneNumber = memberPhoneNumber;
	members[indexId].postCode = memberPostCode;

}


int main(int argc, char *argv[]) {
	
	// variables
	Member members[HASH_TABLE_SIZE];
	
	// initialize array
	initialize(members, HASH_TABLE_SIZE);
	
	// add some players
	newMember(members, HASH_TABLE_SIZE, 67, "Antonio Saramago", 77, 910348597, 29834);
	newMember(members, HASH_TABLE_SIZE, 43, "Maria Mariana", 31, 913959878, 39284);
	newMember(members, HASH_TABLE_SIZE, 12, "Eugenio Camarao", 18, 912349850, 98342);
	newMember(members, HASH_TABLE_SIZE, 24, "Candido Faisca", 25, 910387548, 12983);
	newMember(members, HASH_TABLE_SIZE, 48, "Antonio Godofredo", 32, 91045876, 54367);
	newMember(members, HASH_TABLE_SIZE, 50, "Albertina Cairo", 64, 913832743, 34546);
	newMember(members, HASH_TABLE_SIZE, 9, "Rosario Estacionancio", 88, 91223456, 87435);
	newMember(members, HASH_TABLE_SIZE, 24, "Rogerio Monteiro", 37, 910876456, 23467);
	
	// show hashtable map
	printf("\n Hash Table Map \n\n");
	showHashtableMap(members, HASH_TABLE_SIZE);
	printf("=======================================\n");
	puts(" ");
	puts(" ");
	
	// remove a club member
	printf(" ======================================");
	printf("\n || Removing club member number 12 ||\n");
	printf(" ======================================\n");
	removeMember(members, HASH_TABLE_SIZE, 12);
	puts(" ");
	puts(" ");
	printf("=======================================\n");
	
	// show the hash table after removing a club member
	printf("\n Hash Table Map \n");
	printf(" After removing member 12 \n");
	showHashtableMap(members, HASH_TABLE_SIZE);
	puts(" ");
	puts(" ");
	printf("=======================================\n");
	
	// show all the club members after removing a club member
	printf("\n\n List of Active Members \n\n");
	showMembers(members, HASH_TABLE_SIZE);
	
	printf(" ======================================");
	printf("\n || Updating club member number 67 ||\n");
	printf(" ======================================\n");
	// update a club member
	updateMember(members, HASH_TABLE_SIZE, 67, "Antonio Saramago", 77, 913948576, 77777);
	
	puts(" ");
	puts(" ");
	printf("=======================================\n");
	// show hash table after the updated member
	printf("\n\n List of Active Members after updating \n\n");
	showHashtableMap(members, HASH_TABLE_SIZE);
	puts(" ");
	puts(" ");
	printf("=======================================\n");
	
	// show the member list after the updated member
	printf("\n\n List of Active Members after updating \n\n");
	showMembers(members, HASH_TABLE_SIZE);
	
	return 0;
}


