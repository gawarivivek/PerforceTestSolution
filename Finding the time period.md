Steps:
1. Data Preparation:
It creates two empty vectors - viz.
	- entry and exit.
It iterates through the visitorData (vector of pairs representing entry and exit times).
For each visitor entry, it extracts the entry time and exit time and adds them to the respective entry and exit vectors.

2. Sorting Entry and Exit Times:
The function sorts both entry and exit vectors in ascending order using std::sort.
Sorting the entry times ensures that visitors are "entering" the park in chronological order.
Sorting the exit times ensures that visitors are "leaving" the park in chronological order (not strictly necessary, but might improve efficiency).

3. Tracking Peak Period and Visitors:
It initializes variables:
in_guests: Counts the number of visitors currently present in the park. Starts at 1 (assuming at least one visitor entered).
res_time: A pair to store the start and end time of the peak period (initially set to the first entry and exit time).
max_person: Tracks the maximum number of visitors present at any given moment (initially set to 1).
It uses two indices:
i: Index iterating through the entry vector.
j: Index iterating through the exit vector.

4. Iterating Through Visitors:
It enters a loop that continues as long as both i and j are within the bounds of their respective vectors.
Inside the loop, it compares the current entry time (entry[i]) and exit time (exit[j]).

5. Visitor Enters (Entry Time <= Exit Time):
If the current entry time (entry[i]) is less than or equal to the current exit time (exit[j]), it signifies a visitor entering the park.
Increase in_guests by 1 to reflect the additional visitor.
Check if the current in_guests is greater than the max_person tracked so far.
If it's greater, update max_person with the new maximum number of visitors.
Also, update the res_time pair with the current entry time (entry[i]) as the start time and the current exit time (exit[j]) as the end time of the potential peak period. This captures the time window where the maximum number of visitors were present.
Increment i to move to the next entry time for comparison in the next iteration.

6. Visitor Leaves (Entry Time > Exit Time):
If the current entry time (entry[i]) is greater than the current exit time (exit[j]), it signifies a visitor leaving the park.
Decrease in_guests by 1 to reflect the visitor leaving.
Increment j to move to the next exit time for comparison in the next iteration.

7. Returning the Peak Period:
After iterating through all entries and exits, the function returns the res_time pair, which represents the start and end time of the peak period (the time window with the maximum number of visitors). The max_person variable is passed to the calling function through reference and holds the maximum number of visitors encountered during that time period.
