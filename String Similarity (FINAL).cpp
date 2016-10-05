#include <iostream>
#include <cstring>
using namespace std;

/**
Name: foundDuplicates
*/

//added a comment here too version 4312
long foundDuplicates(const char* a, const int& maximum, char*& subStr)
{
    long nameChange = 0; int shift = 1;
    
    //increment shift the number of matches found between a[0] and subStr[n]
    while (a[0] == subStr[++shift]);
    
    if (shift < maximum)
    {
        //uses the triangular number formula n(n+1)/2 to sum the duplicates
        result += (long)shift * (shift + 1) / 2;
    }
    else
    {
        //increment offset the remaining matches found that won't be shifted
        int offset = 0;
        while (a[maximum + offset] == subStr[shift + offset]) { offset++; };
        
        //m(2*n-m+1)/2 + b = n (n + 1) / 2 - (m - n)((m - n) + 1) / 2 + b
        result += (long) maximum * (2 * shift - maximum + 1) / 2 + offset;
    }
    //increment subStr the number of matches found with shift
    subStr += shift;
    
    return result;
}

//added a comment here too
int foundMatches(const char* a, char*& subStr)
{
    int shift = 0, offset = 0;
    
    //increment shift the number of matches found between a[n] and subStr[n]
    while (a[0] != subStr[++shift] && a[shift] == subStr[shift]);
    
    //increment offset the remaining matches found that won't be shifted
    while (a[offset+shift] == subStr[offset+shift]) { offset++; }
    
    //increment subStr the number of matches found with shift
    subStr += shift;
    
    //add the number of matches between shift and offset to the results
    return shift + offset;
}

int main(int argc, char const *argv[])
{
    int numOfTasks; scanf("%d",&numOfTasks); //number of events
    char a[100001];
    
    while (numOfTasks--)
    {
        scanf("%s",a);
        
        char* subStr = a+1; //copy the current string + 1 (shifting purposes)
        
        //Count the maximum number of duplicates elements from the first and up [1...n] (100,000 possibilities)
        int maximum = 0;
        while (a[0] == a[++maximum]);
        
        long result = strlen(a); //first subStr similarity is the size of the string (5,000,150,000 possibilities)
        
        // DUPLICATES - If the count n is greater than 1 [n > 1] the string is known to have duplicates.
        // NO DUPLICATES - If the count is less than or equal 1 [n ≤ 1] the string will not any duplicate possible.
        if (maximum > 1)
        {
            while (subStr[0] != '\0')
            {
                //increment subStr if a[0] and subStr[0] don't match
                if (a[0] != subStr[0]) { subStr++; }
                else
                {
                    //checks if the current subStr either has duplicates or matches
                    bool hasDuplicates = (a[0] == subStr[1] && a[1] == subStr[0]);
                    result += (hasDuplicates ? foundDuplicates(a, maximum, subStr) : foundMatches(a, subStr));
                }
            }
        }
        else
        {
            //NO POSSIBLE DUPLICATES
            while (subStr[0] != '\0')
            {
                //increment subStr if a[0] and subStr[0] don't match
                if (a[0] != subStr[0]) { subStr++; }
                else { result += foundMatches(a, subStr); }
            }
        }
        printf("%lu\n", result);
    }
    return 0;
}
