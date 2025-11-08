#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100

typedef struct node
{
    char song[SIZE];
    char singer[SIZE];
    char lyricist[SIZE];
    char album[SIZE];
    char composer[SIZE];
    char genre[SIZE];
    int duration;
    struct node* next;
    struct node* prev;

}Node;

//-----Q1-----//
Node *InsertSong(Node *head) 
{
    Node *newSong = (Node *)malloc(sizeof(Node));
    
    printf("Enter the name of the song: ");
    getchar();
    scanf("%[^\n]", newSong->song);
    getchar();
    printf("Enter the name of the singer: ");
    scanf("%[^\n]", newSong->singer);
    getchar();
    printf("Enter the name of the lyricist: ");
    scanf("%[^\n]", newSong->lyricist);
    getchar();
    printf("Enter the name of the album/film: ");
    scanf("%[^\n]", newSong->album);
    getchar();
    printf("Enter the name of the composer: ");
    scanf("%[^\n]", newSong->composer);
    getchar();
    printf("Enter the genre: ");
    scanf("%[^\n]", newSong->genre);
    getchar();
    printf("Enter the duration (in seconds): ");
    scanf("%d", &(newSong->duration));
    
    newSong->next = NULL;
    newSong->prev=NULL;
    if (head == NULL)
    {
        head = newSong;
    } 
    else
    {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
        newSong->prev=temp;
    }
    printf("Song added successfully!\n");
    return head;
}

//-----Q2-----//
void remove_duplicates(Node* head) 
{
    Node *ptr1, *ptr2, *dup;
    ptr1 = head;
    while (ptr1 != NULL && ptr1->next != NULL) 
    {
        ptr2 = ptr1;
        while (ptr2->next != NULL) 
        {
            if (strcmp(ptr1->song, ptr2->next->song) == 0
                && strcmp(ptr1->singer, ptr2->next->singer) == 0
                && strcmp(ptr1->lyricist, ptr2->next->lyricist) == 0
                && strcmp(ptr1->album, ptr2->next->album) == 0
                && strcmp(ptr1->composer, ptr2->next->composer) == 0
                && strcmp(ptr1->genre, ptr2->next->genre) == 0
                && ptr1->duration == ptr2->next->duration) 
            {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free (dup);
            } 
            else
            {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

//-----Q3-----//
Node *split(Node *head)
{
    Node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

Node *merge(Node *first,Node *second)
{
    Node *ret_val;    
    if (first == NULL)
    {
        ret_val = second;
    } 
    else if (second == NULL)
    {
        ret_val = first;
    }    
    else if (first->duration < second->duration)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        ret_val = first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        ret_val = second;
    }

    return ret_val;
}

Node *mergeSort(Node *head)
{
    Node *ret_val;
    if (head == NULL || head->next == NULL)
    {
        ret_val = head;
    }
    else
    {
        Node *second = split(head);
        head = mergeSort(head);
        second = mergeSort(second);
        ret_val = merge(head,second);
    }

    return ret_val;
}

Node* printPlaylist(Node *head) 
{
    head = mergeSort(head);
    printf("Ascending order playlist:\n\n");
    Node *curr=head;
    Node *curr2;
    while (curr != NULL) {
        printf("Song: %s\n", curr->song);
        printf("Singer: %s\n", curr->singer);
        printf("Lyricist: %s\n", curr->lyricist);
        printf("Album/Film: %s\n", curr->album);
        printf("Composer: %s\n", curr->composer);
        printf("Genre: %s\n", curr->genre);
        printf("Duration: %d minutes\n", curr->duration);
        printf("\n");
        
        curr2=curr;
        curr=curr->next;
    }
    
    printf("Descending order playlist:\n\n");
   
    while (curr2 != NULL)
    {
        printf("Song: %s\n", curr2->song);
        printf("Singer: %s\n", curr2->singer);
        printf("Lyricist: %s\n", curr2->lyricist);
        printf("Album/Film: %s\n", curr2->album);
        printf("Composer: %s\n", curr2->composer);
        printf("Genre: %s\n", curr2->genre);
        printf("Duration: %d seconds\n", curr2->duration);
        printf("\n");
       
        curr2=curr2->prev;
    }

    return head;
}

//-----Q4-----//
Node* DeleteSong(Node *head, char* song_name, char* artist_name) 
{   
    if (head == NULL)
    {
        printf("The linked list is empty.\n");
    }
    else
    {

        Node* current = head;
        Node* previous = NULL;

        while (current != NULL) 
        {
            if (strcmp(current->song, song_name) == 0 && strcmp(current->singer, artist_name) == 0)
            {
                
                if (previous == NULL) 
                {
                    head = current->next;
                    free(current);
                    current = head;
                    head->prev=NULL;
                } 
                else 
                {
                    
                    previous->next = current->next;
                    free(current);
                    current = previous->next;
                }
            }
            else 
            {
            
                previous = current;
                current = current->next;
            }
        }
    }
   return head;
}

//-----Q5-----//
Node* create_song(char song[],char singer[], char lyricist[], char album[], char composer[], char genre[], int duration);
Node *createPlaylist(int argc,char argv[8][100], Node *head);
Node* helper(Node* head) //to create playlist
{
    int argc = 0;
    char attribute[8][100];
    char argv[8][100];
    printf("Enter the number of attributes you want to select for playlist\n");
    scanf("%d", &argc);
    getchar();
    for(int i = 0; i < argc; i++)
    {
        char temp[100];
        char att[100];
        printf("Enter attribute you choose: ");
        scanf("%[^\n]", att);
        getchar();
        strcpy(attribute[i], att);
        printf("Enter the value of this attribute: ");
        scanf("%[^\n]", temp);
        strcpy(argv[i], temp);
        getchar();
    }
    Node *temp=createPlaylist(argc,argv,head);
    return temp;
}

//-----Q6-----//
void displaySong(Node* head) {
    Node* current = head;
    int index = 1;
    while (current != NULL) 
    {
        printf("%d. %s\n", index, current->song);
        current = current->next;
        index++;
    }

    int selectedSong;
    printf("\nEnter the serial number of the song to play: ");
    scanf("%d", &selectedSong);

    current = head;
    index = 1;
    while (current != NULL && index < selectedSong) {
        current = current->next;
        index++;
    }

    if (current != NULL) 
    {
        printf("\nPlaying %s by %s from the album/film %s\n",
               current->song, current->singer, current->album);

        if (current->next != NULL) {
            printf("\nNext song is: %s\n", current->next->song);
        }

        if (current->prev!=NULL) 
        {
            Node* prev = current->prev;
           
            printf("Previous song is: %s\n", prev->song);
        }

        printf("\nSelect an option: (1) Next song, (2) Previous song, (3) Exit\n");

        int option;
        scanf("%d", &option);
        if (option == 1 && current->next != NULL)
        {
             printf("\nPlaying %s by %s from the album/film %s\n",
               current->next->song, current->next->singer, current->next->album);
        } 
        else if (option == 2 && current->prev !=NULL)
        {
            Node* pre = current->prev;
             printf("\nPlaying %s by %s from the album/film %s\n",
              pre->song, pre->singer, pre->album);
        }
        else 
        {
            printf("\nExiting music player...\n");
        }
    } 
    else
    {
        printf("\nInvalid serial number. Please try again.\n");
        displaySong(head);
    }
}

//-----Q7-----//
void display_song_details(Node* head, int serial_number) {
    Node* current_node = head;
    int index = 1,flag = 0;
    while(current_node != NULL && flag == 0) 
    {        
        if(index == serial_number) 
        {           
            printf("Song: %s\n",current_node->song);
            printf("Singer: %s\n", current_node->singer);
            printf("Lyricist: %s\n", current_node->lyricist);
            printf("Album/Film: %s\n", current_node->album);
            printf("Composer: %s\n", current_node->composer);
            printf("Genre: %s\n", current_node->genre);
            printf("Duration: %d\n", current_node->duration);
            
            flag=1;
        }
        index++;
        current_node = current_node->next;
    }
    if(flag==0)
    {
        printf("Entered Serial Number's Song does not exist!\n ");
    }
    else
    {
        int k;
        int t;
        char direction[10];
        printf("Enter direction 'up' or 'down' and position fron given song\n");
        scanf("%s%d",direction,&k);
        t = k;
        index--;
        current_node = current_node -> prev;
        if(strcmp(direction, "down") == 0) 
        {
            while(current_node != NULL && k > 0)
            {
                k--;
                current_node=current_node->next;
            }
            if(current_node == NULL)
            {
                printf("%d th song from index %d in downward direction does not exist\n",t,index);
            }
            else
            {
                printf("Song: %s\n",current_node->song);
                printf("Singer: %s\n", current_node->singer);
                printf("Lyricist: %s\n", current_node->lyricist);
                printf("Album/Film: %s\n", current_node->album);
                printf("Composer: %s\n", current_node->composer);
                printf("Genre: %s\n", current_node->genre);
                printf("Duration: %d\n", current_node->duration);
            }
        }
        else if(strcmp(direction,"up") == 0)
        {
            while(current_node != NULL && k > 0)
            {
                k--;
                current_node = current_node->prev;
            }
            if(current_node == NULL)
            {
                printf("%d th song from index %d in upward direction does not exist\n",t,index);
            }
            else
            {
                printf("Song: %s\n",current_node->song);
                printf("Singer: %s\n", current_node->singer);
                printf("Lyricist: %s\n", current_node->lyricist);
                printf("Album/Film: %s\n", current_node->album);
                printf("Composer: %s\n", current_node->composer);
                printf("Genre: %s\n", current_node->genre);
                printf("Duration: %d\n", current_node->duration);
            }
            
        }
        else
        {
            printf("Entered Direction is Invalid!!\n");
        }
    }
}

//Printing the entire original ll
void printList(Node *head)
{
    if(head != NULL)
    {
        Node* curr = head;
        while(curr != NULL)
        {
            printf("Song: %s\n",curr->song);
            printf("Singer: %s\n", curr->singer);
            printf("Lyricist: %s\n", curr->lyricist);
            printf("Album/Film: %s\n", curr->album);
            printf("Composer: %s\n", curr->composer);
            printf("Genre: %s\n", curr->genre);
            printf("Duration: %d\n", curr->duration);
            printf("------------------------\n\n");
            curr = curr -> next;
        }
        printf("\n\n");
    }    
}

int str_to_int(char str[]);

//-----Q8-----//
Node* create_song(char song[],char singer[], char lyricist[], char album[], char composer[], char genre[], int duration)
{
    Node* new_song = (Node*) malloc(sizeof(Node));
    strcpy(new_song->song, song);
    strcpy(new_song->singer, singer);
    strcpy(new_song->lyricist, lyricist);
    strcpy(new_song->album, album);
    strcpy(new_song->composer, composer);
    strcpy(new_song->genre, genre);
    new_song->duration = duration;
    new_song->next = NULL;
    new_song->prev=NULL;
    return new_song;
}

Node *createPlaylist(int argc,char argv[8][100], Node *head)
{
    Node *head1=(Node *)malloc(sizeof(Node));
    head1 = NULL;
    Node *tail = head1;
    Node *curr = head;
    while(curr != NULL)
    {
        int flag=1;
        for(int i = 0; i < argc && flag==1; i++)
        {
            if (strcmp(curr->song,argv[i])==0 ||
                strcmp(curr->singer, argv[i])== 0 ||
                strcmp(curr->lyricist, argv[i]) == 0 ||
                strcmp(curr->album, argv[i]) == 0 ||
                strcmp(curr->composer,argv[i]) == 0 ||
                strcmp(curr->genre,argv[i]) == 0 ||
                curr->duration == str_to_int(argv[i]))
            {
                flag=1;
            }
            else
            {
                flag=0;
            }

        }
        if(flag==1)
        {
            Node* new_song = create_song(curr->song,curr->singer, curr->lyricist, curr->album, curr->composer, curr->genre, curr->duration);
            if (head1 == NULL) 
            {
                head1 = tail = new_song;
            }
            else
            {
                tail -> next = new_song;
                new_song -> prev = tail;
                tail = tail -> next;
            }
        }
        curr=curr->next;
    }
    return head1;
}

Node *display_song(Node *head, int serial_number) {
    Node* current_song = head;
    int index = 1;
    while (current_song != NULL && index != serial_number)
    {
        current_song = current_song->next;
        index++;
    }
    if (current_song != NULL)
    {
        printf("Song: %s\n", current_song->song);
        printf("Singer: %s\n", current_song->singer);
        printf("Lyricist: %s\n", current_song->lyricist);
        printf("Album/Film: %s\n", current_song->album);
        printf("Composer: %s\n", current_song->composer);
        printf("Genre: %s\n", current_song->genre);
        printf("Duration: %d seconds\n", current_song->duration);
        printf("------------------------\n\n");
    } 
    else 
    {
        printf("Invalid serial number.\n");
    }
    int argc = 0;
    char argv[8][100];
    printf("Enter the number of attributes you want to select for playlist\n");
    scanf("%d", &argc);
    getchar();
    for(int i = 0; i < argc; i++)
    {
        char temp[50];
        scanf("%[^\n]", temp);
        strcpy(argv[i], temp);
        getchar();
    }
    Node *temp=createPlaylist(argc,argv,head);
    return temp;
}

//-----Q9-----//
int str_to_int(char str[])
{
    int num=0;
    int i=0;
    while(str[i]!='\0')
    {
        num=num*10+(str[i]-'0');
        i++;
    }
    return num;
}

void filter_by_attribute(Node *head,char att[])
{
    Node *current_node = head;

    while (current_node != NULL)
    {       
        if( strcmp(current_node->song,att)==0 ||
            strcmp(current_node->singer,att) == 0 ||
            strcmp(current_node->lyricist, att) == 0 ||
            strcmp(current_node->album, att) == 0 ||
            strcmp(current_node->composer, att) == 0 ||
            strcmp(current_node->genre,att) == 0 ||
            current_node->duration == str_to_int(att)) 
        {
            printf("Song: %s\n",current_node->song);
            printf("Singer: %s\n", current_node->singer);
            printf("Lyricist: %s\n", current_node->lyricist);
            printf("Album/Film: %s\n", current_node->album);
            printf("Composer: %s\n", current_node->composer);
            printf("Genre: %s\n", current_node->genre);
            printf("Duration: %d\n", current_node->duration);
            printf("------------------------\n\n");
        }
        current_node = current_node->next;
    }    
}

//-----Q10-----//
void play_in_loop(Node *head) 
{
    if (head == NULL)
    {
        printf("Error: Music database is empty.\n");
    }
    else
    {
        int k;
        printf("Enter number of times you want to play the playlist : ");
        scanf("%d", &k);
        for (int i = 0; i < k; i++)
        {
           Node *curr = head;
            while (curr != NULL)
            {
                printf("Song: %s\n",curr->song);
                printf("Singer: %s\n", curr->singer);
                printf("Lyricist: %s\n", curr->lyricist);
                printf("Album/Film: %s\n", curr->album);
                printf("Composer: %s\n", curr->composer);
                printf("Genre: %s\n", curr->genre);
                printf("Duration: %d\n", curr->duration);
                printf("------------------------\n\n");
                curr = curr->next;
            }
        }
    }
}

//-----Q11-----//
void shuffle(Node* head) 
{
    Node *temp = helper(head);
    Node* curr = temp;
    int size = 0;
    while(curr != NULL)
    {
        size++;
        curr = curr -> next;
    }

    int flag[100] = {0};
    time_t t;
    
    int idx = size;
    Node* current;
    while(idx > 0)
    {
        srand((unsigned) time(&t));     //Intializes random number generator        
        int random_index = rand() % size;    //generates random numbers from 0 to size-1
        current = temp;
        if(flag[random_index] == 0)
        {
            for (int i = 0; i < random_index; i++) 
            {
                   current = current->next;
            }
            printf("\n");
            printf("Song: %s\n", current->song);
            printf("Singer: %s\n", current->singer);
            printf("Lyricist: %s\n", current->lyricist);
            printf("Album/Film: %s\n", current->album);
            printf("Composer: %s\n", current->composer);
            printf("Genre: %s\n", current->genre);
            printf("Duration: %d seconds\n", current->duration);
            
            flag[random_index] = 1;
            idx--;
        }        
    }
    printf("Printed all songs of Playlist randomly!!\n");
}

int main()
{
    Node *head = NULL;

    FILE* fp;
    char line[200];
    fp = fopen("list.txt", "r");
    if (fp == NULL)  
    {
        printf("Error opening file.");
        exit(1);
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        Node *newSong = (Node *)malloc(sizeof(Node));
        sscanf(line, "%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %d", newSong -> song, newSong -> singer, newSong -> lyricist, newSong -> album, newSong -> composer, newSong -> genre, &(newSong -> duration));

        newSong->next = NULL;
        newSong->prev=NULL;
        if (head == NULL)
        {
            head = newSong;
        } 
        else
        {
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newSong;
            newSong->prev=temp;
        }
    }

    fclose(fp);

    printf("Hello :) !!!....\n");
    printf("Welcome to our Music Player\n");
    int flag=1;
    while(flag == 1)
    {
        printf("1.Insert a song at the end\n");
        printf("2.Remove duplicate entries from Records\n");
        printf("3.Play playlist in ascending as well as in descending order\n");
        printf("4.Delete all songs from playlist with given song name and singer\n");
        printf("5.Create a play-list based on the attribute and its value\n");
        printf("6.Play a song in playlist as per serial number and play next or previous song\n");
        printf("7.Play a song in playlist as per serial number and play kth next or kth previous song\n");
        printf("8.Play a given song from Playlist and create a new Playlist selecting one or more attributes from this song\n");
        printf("9.Play only songs in Playlist matching given attribute value\n");
        printf("10.Play the Playlist k times\n");
        printf("11.Randomly play songs from Database matching given attributes value\n");
        printf("------------------------\n");
        int t;
        printf("Enter any negative number to exit our music player\n");
        scanf("%d",&t);
        Node *temp;
        if(t>=0)
        {
            switch(t)
            {
                case 1: head = InsertSong(head);
                        printList(head);
                        break;
                case 2: remove_duplicates(head);
                        printList(head);
                        break;
                case 3: head = printPlaylist(head);
                        break;
                case 4:; char str1[100],str2[100];
                        printf("Enter song name to delete\n");
                        getchar();
                        scanf("%[^\n]", str1);
                        printf("%s",str1);
                        getchar();
                        printf("Enter Singer's name to delete Song\n");
                        scanf("%[^\n]", str2);
                        printf("%s",str2);
                        getchar();
                        temp=DeleteSong(head,str1,str2);
                        printf("Successfully deleted songs with given artist and song\n");
                        printf("Displaying modified Playlist\n");
                        printList(temp);
                        break;
                case 5: temp=helper(head);
                        printf("Displaying new Playlist\n\n");
                        printList(temp);
                        break;
                case 6: displaySong(head);
                        break;
                case 7:; int k;
                        printf("Enter serial number of song to play\n");
                        scanf("%d",&k);
                        display_song_details(head,k);
                        break;
                case 8:; int l;
                        printf("Enter serial number of song to play\n");
                        scanf("%d",&l);
                        temp=display_song(head,l);
                        printf("Displaying new Playlist as per given attributes\n");
                        printList(temp);
                        break;
                case 9:; char str3[50];
                        printf("Enter the attribute's value : ");
                        getchar();
                        scanf("%[^\n]", str3);
                        getchar();
                        filter_by_attribute(head,str3);
                        break;
                case 10: play_in_loop(head);
                        break;
                case 11: shuffle(head);
                        break;
                default:printf("Invalid number entered\n");
                        break;
            }
        }
        else
        {
            flag=0;
        }
    }
    printf("Thanks for visiting our Music Player\n");
    printf("------------------------\n\n");
    printf("------------------------\n\n");

    return 0;
}

