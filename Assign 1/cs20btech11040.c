#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAXSIZE 30

typedef struct _songs{
	char name[MAXSIZE];
	struct _songs* next;
}song;

typedef struct library
{
	song* head;
	unsigned size;
}library;

library* create_library()
{
	library* collection =(library*)malloc(sizeof(library));
	collection->head=NULL;
	collection->size=0;
	return collection;
}

void add_song(library* collection,const char name[])
{
	song* new_song = (song*)malloc(sizeof(song));
	strcpy(new_song->name,name);
	new_song->next=collection->head;
	collection->head=new_song;
	collection->size++;
}

song* searchsong(library* collection,const char name[])
{
	song* search_variable = collection->head;
	for(unsigned i=0;i<collection->size;i++)
	{
		if(strcmp(search_variable->name,name)==0)
			break;
		else
			search_variable=search_variable->next;
	}
	return search_variable;
}

void free_library(library* collection)
{
	song* tmp;
	while(collection->head!=NULL)
	{
		tmp=collection->head;
		collection->head=collection->head->next;
		free(tmp);
	}
	free(collection);
}

typedef struct queue
{
	song* front;
	unsigned size;
	song* rear;
}queue;

queue* create_queue()
{
	queue* playlist=(queue*)malloc(sizeof(queue));
	playlist->front=NULL;
	playlist->rear=NULL;
	playlist->size=0;
	return playlist;
}

void enqueue(queue* playlist,const char name[])
{
	song* node=(song*)malloc(sizeof(song));
	strcpy(node->name,name);
	node->next=playlist->front;
	playlist->front=node;
	if(playlist->size==0)
		playlist->rear=playlist->front;
	playlist->size++;
}

song* dequeue(queue* playlist)
{
	if(playlist->size==0)
	{
		printf("no songs left");
		return NULL;
	}
	song* dequeued =playlist->rear;
	playlist->size--;
	song* shift_variable=playlist->front;
	for(unsigned i=1;i<playlist->size;i++)
	{
		shift_variable=shift_variable->next;
	}
	playlist->rear=shift_variable;
	return dequeued;
}

void free_queue(queue* playlist)
{
	song* tmp;
	while(playlist->front!=NULL)
	{
		tmp=playlist->front;
		playlist->front=playlist->front->next;
		free(tmp);
	}
	free(playlist);
}

typedef struct stack
{
	song* bottom;
	unsigned size;
}stack;

stack* create_stack()
{
	stack* recent_songs=(stack*)malloc(sizeof(stack));
	recent_songs->size=0;
	recent_songs->bottom=NULL;
	return recent_songs;
}

void push(stack* recent_songs,const char name[])
{
	song* last_played = (song*)malloc(sizeof(song));
	strcpy(last_played->name,name);
	last_played->next=recent_songs->bottom;
	recent_songs->bottom=last_played;
	recent_songs->size++;
}

song* pop(stack* recent_songs)
{
	if(recent_songs->size==0)
	{
		printf("no recent songs left\n");
		return NULL;
	}
	song* popped;
	popped=recent_songs->bottom;
	recent_songs->bottom=popped->next;
	popped->next=NULL;
	recent_songs->size--;
	return popped;
}

void free_stack(stack* recent_songs)
{
	song* tmp;
	while(recent_songs->bottom!=NULL)
	{
		tmp=recent_songs->bottom;
		recent_songs->bottom=recent_songs->bottom->next;
		free(tmp);
	}
	free(recent_songs);
}

int main()
{
	library* collection=create_library();
	queue* playlist=create_queue();
	queue* temporary_queue=create_queue();
	stack* recent_songs=create_stack();
   printf("Enter all songs as strings,End with -1 \n");
   char input[MAXSIZE];
   while(true)
   {
	   scanf("%s",input);
	   if(strcmp(input,"-1")==0)
		   break;
	   add_song(collection,input);
   }
   printf("made your collection\n");
  printf("create a playlist, end with -1 \n");
  while(true)
  {
	  scanf("%s",input);
	  if(strcmp(input,"-1")==0)
		  break;
	  if(searchsong(collection,input)==NULL)
	  {
		  printf("unable to add\n not found in collection\n");
		  continue;
	  }
	  enqueue(playlist,searchsong(collection,input)->name);
	  printf("Found ,added\n");
  }
  while(true)
  {
	  char choice[3];
	  printf("play next song,previous song or end n/p:k/e ?\n give your choice\n");
	  printf("k is the no. of songs\n");
	  scanf("%s",choice);
	  if(choice[0]!='n'&&choice[0]!='p'&&choice[0]!='e')
	  {
		  printf("invalid choice\n");
		  continue;
	  }
	  if(choice[0]=='e')
		  break;
	  if(choice[0]=='n')
	  {
		  if(playlist->size==0)
		  {
			  printf("sorry, no songs left to play\n");
			  continue;
		  }
		  song* played_song=dequeue(playlist);
		  push(recent_songs,played_song->name);
		  printf("playing %s\n",played_song->name);
	  }
	  if(choice[0]=='p')
	  {
		  int num=atoi(choice+2);
		  for(int i=0;i<num;i++)
		  {
			  if(recent_songs->size==0)
				  printf("sorry, no more previous songs left\n");
			  else
			  {
				  song* played_song=pop(recent_songs);
				  enqueue(temporary_queue,played_song->name);
				  printf("playing %s\n",played_song->name);
			  }
		  }
	  }

  }
  printf("Thank you, listen again\n");



  free_library(collection);
  free_queue(playlist);
  free_queue(temporary_queue);
  free_stack(recent_songs);

  return EXIT_SUCCESS;
}
