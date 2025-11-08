# Music-Player-in-C

We need to design a data structure for music player. A linked list can store the database of all music listings. Each music listing will have attributes like singer, lyricist, album/film, composer, genre, duration of the song and any other you may choose. We need to define following operations:

1. Write a function, InsertSong(), which reads a song from user and insert into a linked list of structures. Add a new song at the end in the list.

2. Write a function removeDuplicates() to remove the duplicate entries from the records.

3. Write a function to printPlaylist() which prints the records in the linked list in ascending as well as in descending order.

4. Write a function to DeleteSong() to delete the particular song details from the linked list as per the song_name and also as per the name of the artist provided by the user and deletes all the entries with that artist.

5. Create a play-list based on the attribute and its value given. For example, if “singer” attribute is provided and “Kishor Kumar” is the name of the singer, then a new play-list is created containing all the songs belonging to Kishore Kumar. The songs for the same singer to be sorted based on lexicographic order of the songs. Multiple attributes and their values can also be provided to create the play-list. For example if attributes given are “singer” and “film” and corresponding values provided are “Kishor Kumar” and “Sholay”, then all songs belonging to Kishore Kumar in Sholay are added into the play-list and likewise.

6. (Dis)Play a song in a play-list. In our setting this will mean, given a play-list as input, show/print all songs in the play-list indexed with serial numbers. User can select a serial number of the song, and data corresponding to the selected song is required to be displayed. At the same time, name of the previous as well as next song is also displayed. User is provided an option to select “Next” or “Prev” song. By selecting one of the options either “Next” or “Prev”, respectively data for next and previous song is displayed.

7. Given a play-list and the serial number of the song, display details of the song. At this point, given an integer offset “k” and direction “up” or “down”, display the details of kth previous or kth next song, from the current song, respectively, in the play-list.

8. Given a play-list and the serial number of the song, display details of the song. Provide an option to the user to select one or many attributes of this “current” song and create a play-list for these attribute values from the original database.

9. Filter the playlist. Given a play-list and an attribute value, filter all songs in the playlist matching the attribute value. For example, if play-list is for “Kishore Kumar” and attribute value is given for genre as “comedy”, all songs in the current playlist with genre as “comedy” will be chosen.

10. Play-in-loop. Of the available play-lists, select a play-list and take an integer k as input. Display details of play-list in a loop k times, as if the play-list is being played k times in loop.

11. Shuffle to something else. Take a set of attributes and their values as inputs. Randomly select any song from the original database matching all the attribute values provided. Mark it using FLAG so that it doesn’t get a chance again till all other songs in the playlist are played randomly.

For database as well as play-list, you are free to choose specific type of linked list, whether singly linked-list, circular linked list or doubly linked list. Make the decision appropriately that helps the most in the ease of operations and efficiency.
